#pragma once
#include "net_utility.h"
#include "net_queue.h"
#include "net_message.h"


namespace rav
{
    namespace net
    {
        //forward decl
        template<typename T>
        class IServer;
        
        template <typename T>
        class TConnection : std::enable_shared_from_this<TConnection<T>>
        {
        public:
            enum class EOwner
            {
                server,
                client
            };

            TConnection(
                EOwner owner, 
                InOutContext& context, 
                SocketType socket, 
                TThrSafeQueue<TOwnedMessage<T>>& qIn) :
                m_context(context), m_socket(std::move(socket)), m_queueMessagesIn(qIn)
            {
                m_owner = owner;

                // Validation
                if (m_owner == EOwner::server)
                {
                    m_keyOut = static_cast<uint64_t>(
                        std::chrono::system_clock::now().time_since_epoch().count());

                    m_keyCheck = scramble(m_keyOut);
                }
                else
                {
                    //client
                    m_keyOut = 0;
                    m_keyIn = 0;
                }
            }
            
            ~TConnection() {}

        public:
            uint32_t getID() const { return m_id; }

            void connectToClient(IServer<T>* server, uint32_t id = 0)
            {
                if (m_owner != EOwner::server) return;

                if (m_socket.is_open())
                {
                    m_id = id;
                    //readHeader();

                    writeValidation();
                    readValidation(server);
                }
            }

            void connectToServer(const ResolverType::results_type& endpoints)
            { 
                if (m_owner == EOwner::client)
                {
                    asio::async_connect(m_socket, endpoints,
                        [this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
                        {
                            if (!ec)
                            {
                                //readHeader();
                                readValidation();
                            }
                        });
                }
            };

            void disconnect() 
            {
                if (isConnected())
                    asio::post(m_context, [this]() { m_socket.close(); });
            };

            bool isConnected() const
            { 
                return m_socket.is_open(); 
            };

        public:
            void send(const TMessage<T> message) 
            { 
                asio::post(m_context,
                    [this, message]()
                    {
                        bool bWritingMessage = !m_queueMessagesOut.empty();
                        m_queueMessagesOut.puch_back(message);
                        if (!bWritingMessage)
                        {
                            writeHeader();
                        }
                    });
            };
            
        private:
            // ASYNC
            void readHeader()
            {
                asio::async_read(m_socket, asio::buffer(&m_messageTempIn.header, sizeof(TMessageHeader<T>)),
                    [this](std::error_code ec, std::size_t length) 
                    {
                        if (!ec)
                        {
                            if (m_messageTempIn.header.size > 0)
                            {
                                m_messageTempIn.body.resize(m_messageTempIn.header.size);
                                readBody();
                            }
                            else
                            {
                                addToIncomingMessagesQueue();
                            }
                        }
                        else
                        {
                            std::cout << "[" << m_id << "] Read Header fail!\n";
                            m_socket.close();
                        }

                    });
            }

            // ASYNC
            void readBody()
            {
                asio::async_read(m_socket, asio::buffer(m_messageTempIn.body.data(), m_messageTempIn.header.size),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            addToIncomingMessagesQueue();
                        }
                        else
                        {
                            std::cout << "[" << m_id << "] Read Body fail!\n";
                            m_socket.close();
                        }

                    });
            }

            void addToIncomingMessagesQueue()
            {
                if (m_owner == EOwner::server)
                    m_queueMessagesIn.puch_back({ this->shared_from_this(), m_messageTempIn });
                else
                    m_queueMessagesIn.puch_back({ nullptr, m_messageTempIn });

                readHeader();
            }

            // ASYNC
            void writeHeader()
            {
                asio::async_write(m_socket, asio::buffer(&m_queueMessagesOut.front().header, sizeof(TMessageHeader<T>)),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            if (m_queueMessagesOut.front().body.size() > 0)
                            {
                                writeBody();
                            }
                            else
                            {
                                m_queueMessagesOut.pop_front();

                                if (!m_queueMessagesOut.empty())
                                    writeHeader();
                            }

                        }
                        else
                        {
                            std::cout << "[" << m_id << "] Write Header fail!\n";
                            m_socket.close();
                        }
                    });
            }

            // ASYNC
            void writeBody()
            {
                asio::async_write(m_socket, asio::buffer(&m_queueMessagesOut.front().body.data(), m_queueMessagesOut.front().body.size()),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            m_queueMessagesOut.pop_front();

                            if (!m_queueMessagesOut.empty())
                                writeHeader();
                        }
                        else
                        {
                            std::cout << "[" << m_id << "] Write Body fail!\n";
                            m_socket.close();
                        }
                    });
            }

            // Validation func.
            uint64_t scramble(uint64_t in)
            {
                uint64_t out = in ^ 0xDEADBEEFC0DECAFE;
                return out;
            }

            // ASYNC Validation func.
            void writeValidation()
            {
                asio::async_write(m_socket, asio::buffer(&m_keyOut, sizeof(uint64_t)),
                    [this](std::error_code ec, std::size_t length) 
                    {
                        if (!ec)
                        {
                            if (m_owner == EOwner::client)
                                readHeader();
                        }
                        else
                        {
                            m_socket.close();
                        }
                    });
            }

            // ASYNC Validation func.
            void readValidation(IServer<T>* server = nullptr)
            {
                asio::async_read(m_socket, asio::buffer(&m_keyIn, sizeof(uint64_t)),
                    [this, server](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            if (m_owner == EOwner::server)
                            {
                                if (m_keyIn == m_keyCheck)
                                {
                                    std::cout << "Client validated. \n";
                                    server->onClientValidation(this->shared_from_this());

                                    readHeader();
                                }
                                else
                                {
                                    std::cout << "Client disconnected (Fail Validation) \n";
                                    m_socket.close();
                                }
                            }
                            else
                            {
                                //client
                                m_keyOut = scramble(m_keyIn);
                                writeValidation();
                            }
                        }
                        else
                        {
                            std::cout << "Client disconnected (Read Validation) \n";
                            m_socket.close();
                        }
                    });
            }



        protected:
            uint32_t m_id = 0;
            EOwner m_owner = EOwner::server;
            SocketType m_socket;
            InOutContext& m_context;

            TThrSafeQueue<TMessage<T>> m_queueMessagesOut;
            TThrSafeQueue<TOwnedMessage<T>>& m_queueMessagesIn;
            TMessage<T> m_messageTempIn;

            // Validation
            uint64_t m_keyOut = 0;
            uint64_t m_keyIn = 0;
            uint64_t m_keyCheck = 0;
        };

    } // namespace net

} // namespace rav
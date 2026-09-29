#pragma once
#include "net_utility.h"
#include "net_queue.h"
#include "net_message.h"
#include "net_connection.h"

namespace rav
{
    namespace net
    {
        template <typename T>
        class IServer
        {
        public:
            IServer(uint16_t port) 
                : m_acceptor(   m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
            {

            }

            virtual ~IServer()
            {
                stop();
            }

            bool start()
            {
                try
                {
                    waitForClientConection();

                    m_threadContext = std::thread([this]() { m_context.run(); });
                }
                catch (std::exception& e)
                {
                    std::cout << "[Server] Exception: " << e.what() << "\n";
                    return false;
                }

                std::cout << "[Server] Started!\n";
                return true;
            }

            void stop()
            {
                m_context.stop();

                if (m_threadContext.joinable()) m_threadContext.join();
                std::cout << "[Server] Stopped!\n";
            }

            // ASYNC
            void waitForClientConection()
            {
                m_acceptor.async_accept(
                    [this](std::error_code ec, SocketType socket)
                    {
                        if (!ec)
                        {
                            std::cout << "[Server] New connection: " << socket.remote_endpoint() << "\n";

                            TShared_Ptr newConnection =
                                std::make_shared<TConnection<T>>(
                                    TConnection<T>::EOwner::server,
                                    m_context,
                                    std::move(socket),
                                    m_queueMessagesIn);

                            if (onClientConnect(newConnection))
                            {
                                m_dequeConnections.push_back(std::move(newConnection));
                                m_dequeConnections.back()->connectToClient(this, m_idCounter++);

                                std::cout << "[" << m_dequeConnections.back()->getID() << "] Connection Approved.\n";
                            }
                            else
                            {
                                std::cout << "Connection denird! \n";
                            }
                        }
                        else
                        {
                            std::cout << "[Server] New connection error: " << ec.message() << "\n";
                        }
                        waitForClientConection();
                    });
            }

            // Send message to clients.
            void messageToClient(TShared_Ptr<TConnection<T>> client, const TMessage<T>& msg)
            {
                if (client && client->isConnected())
                {
                    client->send(msg);
                }
                else
                {
                    onClientDisconnect(client);
                    client.reset();

                    m_dequeConnections.erase(
                        std::remove(m_dequeConnections.begin(), m_dequeConnections.end(), client), 
                        m_dequeConnections.end());
                }
            }

            // Send message to all clients.
            void messageToAllClient(const TMessage<T>& msg, TShared_Ptr<TConnection<T>> ignoreClient)
            {
                bool bInvalidClientExists = false;
                
                for (auto& client : m_dequeConnections)
                {
                    if (client && client->isConnected())
                    {
                        if (client != ignoreClient) client->send(msg);
                    }
                    else
                    {
                        onClientDisconnect(client);
                        client.reset();
                        bInvalidClientExists = true;
                    }
                }

                if(bInvalidClientExists)
                    m_dequeConnections.erase(
                        std::remove(m_dequeConnections.begin(), m_dequeConnections.end(), nullptr),
                        m_dequeConnections.end());
            }

            void update(size_t maxMessages = -1, bool bWait = false)
            {
                if (bWait) m_queueMessagesIn.wait();
                
                size_t messageCount = 0;

                while (messageCount < maxMessages && !m_queueMessagesIn.empty())
                {
                    auto msg = m_queueMessagesIn.pop_front();
                    onMessage(msg.remote, msg.message);

                    messageCount++;
                }
            }

        protected:
            virtual bool  onClientConnect(TShared_Ptr<TConnection<T>> client)
            {
                return false;
            }

            virtual void  onClientDisconnect(TShared_Ptr<TConnection<T>> client)
            {
            
            }

            virtual void onMessage(TShared_Ptr<TConnection<T>> client, TMessage<T>& message)
            {

            }

        public:

            // Validation
            virtual void onClientValidation(TShared_Ptr<TConnection<T>> client)
            {

            }

        protected:
            InOutContext m_context;
            Thread m_threadContext;
            AcceptorType m_acceptor;

            uint32_t m_idCounter = 10000;

        private:
            TDeque<TShared_Ptr<TConnection<T>>> m_dequeConnections;
            TThrSafeQueue<TOwnedMessage<T>> m_queueMessagesIn;
        };

    } // namespace net

} // namespace rav
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
        class IClient
        {
        public:
            IClient() : m_socket(m_context) {}
            virtual ~IClient() { disconnect(); }

        public:
            bool connect(const String& host, const uint16_t port)
            {
                try
                {
                    ResolverType resolver(m_context);
                    ResolverType::results_type endpoints = resolver.resolve(host, std::to_string(port));
                    
                    m_connection = std::make_unique<TConnection<T>>(
                        TConnection<T>::EOwner::client, 
                        m_context,
                        SocketType(m_context), 
                        m_queueMessagesIn);

                    m_connection->connectToServer(endpoints);

                    m_threadContext = std::thread([this]() { m_context.run(); });
                }
                catch (std::exception& e)
                {
                    std::cerr << "[Client] Exception: " << e.what() << "\n";
                    return false;
                }
                
                return true;
            }

            void disconnect()
            {
                if (isConnected()) m_connection->disconnect();

                m_context.stop();

                if (m_threadContext.joinable()) m_threadContext.join();

                m_connection.release();
            }

            bool isConnected()
            {
                if (!m_connection) return false;

                m_connection->isConnected();
            }

            TThrSafeQueue<TOwnedMessage<T>>& incoming()
            {
                return m_queueMessagesIn;
            }

        protected:
            InOutContext m_context;
            Thread m_threadContext;
            SocketType m_socket;
            TUnique_Ptr<TConnection<T>> m_connection;

        private:
            TThrSafeQueue<TOwnedMessage<T>> m_queueMessagesIn;
        };

    } // namespace net

} // namespace rav
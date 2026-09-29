#pragma once
#include "net_utility.h"

namespace rav
{
    namespace net
    {
        // Thread-safe queue.
        template <typename T>
        class TThrSafeQueue
        {
        public:
            TThrSafeQueue() = default;
            TThrSafeQueue(const TThrSafeQueue<T>&) = delete;
            virtual ~TThrSafeQueue() { clear(); }

        public:
            const T& front()
            {
                std::scoped_lock lock(m_mutexQueue);
                return m_dequeQueue.front();
            }

            const T& back()
            {
                std::scoped_lock lock(m_mutexQueue);
                return m_dequeQueue.back();
            }

            void puch_front(const T& item)
            {
                std::scoped_lock lock(m_mutexQueue);
                m_dequeQueue.emplace_front(std::move(item));

                std::unique_lock<Mutex> ul(m_mutexBlocking);
                m_blocking.notify_one();
            }

            void puch_back(const T& item)
            {
                std::scoped_lock lock(m_mutexQueue);
                m_dequeQueue.emplace_back(std::move(item));

                std::unique_lock<Mutex> ul(m_mutexBlocking);
                m_blocking.notify_one();
            }

            bool empty()
            {
                std::scoped_lock lock(m_mutexQueue);
                return m_dequeQueue.empty();
            }

            size_t size()
            {
                std::scoped_lock lock(m_mutexQueue);
                return m_dequeQueue.size();
            }

            void clear()
            {
                std::scoped_lock lock(m_mutexQueue);
                m_dequeQueue.clear();
            }

            T pop_front()
            {
                std::scoped_lock lock(m_mutexQueue);

                auto item = std::move(m_dequeQueue.front());
                m_dequeQueue.pop_front();

                return item;
            }

            T pop_back()
            {
                std::scoped_lock lock(m_mutexQueue);

                auto item = std::move(m_dequeQueue.back());
                m_dequeQueue.pop_back();

                return item;
            }

            void wait()
            {
                while (empty())
                {
                    std::unique_lock<Mutex> ul(m_mutexBlocking);
                    m_blocking.wait(ul);
                }
            }

        protected:
            Mutex m_mutexQueue;
            TDeque<T> m_dequeQueue;

            Mutex m_mutexBlocking;
            ConditionVariable m_blocking;
        };

    } // namespace net

} // namespace rav


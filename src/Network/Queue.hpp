/*
** EPITECH PROJECT, 2022
** Queue
** File description:
** Queue
*/

#pragma once
#include <deque>
#include <mutex>
#include <string>
#include <condition_variable>

namespace network
{
    template <class T> class Queue {
      public:
        /**
         * @brief Construct a new Queue object
         *
         */
        Queue() = default;
        /**
         * @brief Destroy the Queue object
         *
         */
        ~Queue()
        {
            clear();
        };
        /**
         * @brief
         *
         * @param msg
         */
        void push_front(const T &msg)
        {
            std::scoped_lock lock(mtx);
            queue.push_front(msg);
            std::unique_lock<std::mutex> ulock(mtxBlock);
            cvBlock.notify_one();
        }
        /**
         * @brief
         *
         * @return T
         */
        T pop_front()
        {
            std::scoped_lock lock(mtx);
            auto msg = std::move(queue.front());
            queue.pop_front();
            return msg;
        }
        /**
         * @brief
         *
         * @return const T&
         */
        const T &front()
        {
            std::scoped_lock lock(mtx);
            return (queue.front());
        }
        /**
         * @brief
         *
         * @param msg
         */
        void push_back(const T &msg)
        {
            std::scoped_lock lock(mtx);
            queue.push_back(msg);
            std::unique_lock<std::mutex> ulock(mtxBlock);
            cvBlock.notify_one();
        }
        /**
         * @brief
         *
         * @return T
         */
        T pop_back()
        {
            std::scoped_lock lock(mtx);
            auto msg = std::move(queue.back());
            queue.pop_back();
            return msg;
        }
        /**
         * @brief
         *
         * @return const T&
         */
        const T &back()
        {
            std::scoped_lock lock(mtx);
            return (queue.back());
        }
        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool empty()
        {
            std::scoped_lock lock(mtx);
            return (queue.empty());
        }
        /**
         * @brief
         *
         * @return std::size_t
         */
        std::size_t size()
        {
            std::scoped_lock lock(mtx);
            return (queue.size());
        }
        /**
         * @brief
         *
         */
        void clear()
        {
            std::scoped_lock lock(mtx);
            queue.clear();
        }
        /**
         * @brief
         *
         */
        void wait()
        {
            while (empty()) {
                std::unique_lock<std::mutex> ulock(mtxBlock);
                cvBlock.wait(ulock);
            }
        }

      protected:
      private:
        std::mutex mtx;
        std::deque<T> queue;
        std::condition_variable cvBlock;
        std::mutex mtxBlock;
    };
} // namespace network

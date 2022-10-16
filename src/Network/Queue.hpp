/*
** EPITECH PROJECT, 2022
** Queue
** File description:
** Queue
*/

#pragma once
#include <mutex>
#include <deque>
#include <string>
#include <condition_variable>

namespace network
{
    template <class T>
    class Queue {
        public:
            Queue() = default;
            ~Queue()
            {
                clear();
            };

            void push_front(const T &msg)
            {
                std::scoped_lock lock(mtx);
                queue.push_front(msg);
                std::unique_lock<std::mutex> ulock(mtxBlock);
				cvBlock.notify_one();
            }
            T pop_front()
            {
                std::scoped_lock lock(mtx);
                auto msg = std::move(queue.front());
                queue.pop_front();
                return msg;
            }
            const T &front()
            {
                std::scoped_lock lock(mtx);
                return (queue.front());
            }
            void push_back(const T &msg)
            {
                std::scoped_lock lock(mtx);
                queue.push_back(msg);
                std::unique_lock<std::mutex> ulock(mtxBlock);
				cvBlock.notify_one();
            }
            T pop_back()
            {
                std::scoped_lock lock(mtx);
                auto msg = std::move(queue.back());
                queue.pop_back();
                return msg;
            }
            const T &back()
            {
                std::scoped_lock lock(mtx);
                return (queue.back());
            }
            bool empty()
            {
                std::scoped_lock lock(mtx);
                return (queue.empty());
            }
            std::size_t size()
            {
                std::scoped_lock lock(mtx);
                return (queue.size());
            }
            void clear()
            {
                std::scoped_lock lock(mtx);
                queue.clear();
            }
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
}

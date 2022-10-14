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
            }
            T pop_front()
            {
                std::scoped_lock lock(mtx);
                auto msg = std::move(front());
                queue.pop_front();
                return msg;
            }
            const T &front()
            {
                std::scoped_lock lock(mtx);
                return (queue.front());
            }
            T pop_back()
            {
                std::scoped_lock lock(mtx);
                auto msg = std::move(back());
                queue.pop_back();
                return msg;
            }
            void push_back(const T &msg)
            {
                std::scoped_lock lock(mtx);
                queue.push_back(msg);
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
            std::size_t count()
            {
                std::scoped_lock lock(mtx);
                return (queue.size());
            }
            void clear()
            {
                std::scoped_lock lock(mtx);
                queue.clear();
            }
        protected:
        private:
            std::mutex mtx;
            std::deque<T> queue;
    };
}

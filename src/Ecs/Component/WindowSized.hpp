/*
** EPITECH PROJECT, 2022
** WindowSized
** File description:
** WindowSized
*/

#pragma once
#include "AComponent.hpp"

namespace ecs
{
    class WindowSized : public AComponent {
        public:
        /**
         * @brief Construct a new WindowSized object
         * 
         */
            WindowSized() = default;
            /**
             * @brief Construct a new WindowSized object
             * 
             * @param other 
             */
            WindowSized(const WindowSized &other) = default;
            /**
             * @brief Destroy the WindowSized object
             * 
             */
            ~WindowSized() = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return WindowSized& 
             */
            WindowSized &operator=(const WindowSized &other) = default;

            friend bool operator==(const WindowSized &lhs, const WindowSized &rhs)
            {
                static_cast<void>(lhs);
                static_cast<void>(rhs);
                return true;
            }
        protected:
        private:
    };
}

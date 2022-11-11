/*
** EPITECH PROJECT, 2022
** Animation
** File description:
** Animation
*/

#pragma once
#include "AComponent.hpp"

namespace ecs
{
    class Animation : public AComponent {
        public:
            /**
             * @brief Construct a new Animation object
             * 
             */
            Animation() = default;
            /**
             * @brief Construct a new Animation object
             * 
             * @param other 
             */
            Animation(const Animation &other) = default;
            /**
             * @brief Destroy the Animation object
             * 
             */
            ~Animation() = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Animation& 
             */
            Animation &operator=(const Animation &other) = default;

            friend bool operator==(const Animation &lhs, const Animation &rhs)
            {
                static_cast<void>(lhs);
                static_cast<void>(rhs);
                return true;
            }
        protected:
        private:
    };
}

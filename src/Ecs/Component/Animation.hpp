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
            Animation() = default;
            Animation(const Animation &other) = default;
            ~Animation() = default;
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

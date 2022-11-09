/*
** EPITECH PROJECT, 2022
** Pressed
** File description:
** Pressed
*/

#pragma once
#include "AComponent.hpp"

namespace ecs
{
    class Pressed : public AComponent {
        public:
            Pressed() = default;
            Pressed(const Pressed &other) = default;
            ~Pressed() = default;
            Pressed &operator=(const Pressed &other) = default;

        protected:
        private:
    };
}

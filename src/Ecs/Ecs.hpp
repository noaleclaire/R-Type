/*
** EPITECH PROJECT, 2022
** Ecs
** File description:
** Ecs
*/

#pragma once

#include "Registry.hpp"

namespace ecs
{
    class Ecs {
        public:
            Ecs();
            ~Ecs();
        private:
            Registry _registry;
    };
}

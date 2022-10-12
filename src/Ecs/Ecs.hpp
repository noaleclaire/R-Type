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
    enum EntityTypes { SPACESHIP, MONSTER, SHOT, BUTTON, WALL, BACKGROUND };

    class Ecs {
      public:
        Ecs();
        ~Ecs();

      private:
        Registry _registry;
    };
} // namespace ecs

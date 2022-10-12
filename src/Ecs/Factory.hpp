/*
** EPITECH PROJECT, 2022
** Factory.hpp
** File description:
** Factory.hpp
*/

#pragma once

#include "Ecs.hpp"

namespace ecs
{
    class Factory {
      public:
        static Registry &createEntity(Registry &registry, EntityTypes entityType);

      private:
        static Registry &createSpaceship(Registry &registry);
        static Registry &createMonster(Registry &registry);
        static Registry &createShot(Registry &registry);
        static Registry &createButton(Registry &registry);
        static Registry &createWall(Registry &registry);
        static Registry &createBackground(Registry &registry);
    };
} // namespace ecs

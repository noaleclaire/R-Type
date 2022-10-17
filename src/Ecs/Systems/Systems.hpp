/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#pragma once
#include "../../client/Sfml/Graphical.hpp"
#include "../Component/SparseArray.hpp"
#include "../Registry.hpp"

namespace ecs
{
    class Systems {
      public:
        /**
         * @brief
         *
         * @param registry
         * @param drawable
         */
        static void Drawable(Registry &registry, SparseArray<ecs::Drawable> const &drawable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param clickable
         * @param graphical
         */
        static void Clickable(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param position
         * @param graphical
         */
        static void Position(Registry &registry, SparseArray<ecs::Position> const &position, graphics::Graphical &graphical);
    };
} // namespace ecs

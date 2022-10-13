/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#pragma once
#include "../Component/Drawable.hpp"
#include "../Component/SparseArray.hpp"
#include "../Registry.hpp"
#include "../../client/Sfml/Graphical.hpp"

namespace ecs
{
    class Systems {
      public:
        static void Drawable(Registry &registry, SparseArray<component::Drawable> const &drawable, graphics::Graphical &graphical);
    };
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#pragma once
#include "../Registry.hpp"
#include "../Component/SparseArray.hpp"
#include "../Component/Drawable.hpp"

namespace ecs
{
    class Systems {
        public:
            static void SystemDrawable(Registry &registry, SparseArray<component::Drawable> const &drawable);
    };
}

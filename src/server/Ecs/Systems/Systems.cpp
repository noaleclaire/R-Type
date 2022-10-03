/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#include "Systems.hpp"

namespace ecs
{
    void Systems::Drawable(Registry &registry, SparseArray<component::Drawable> const &drawable)
    {
        for (auto &it : registry.getEntities()) {
            if (drawable.at(it))
                ; // dessine entity
        }
    }
} // namespace ecs

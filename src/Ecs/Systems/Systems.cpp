/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#include "Systems.hpp"
#include "../Exceptions/ExceptionIndexComponent.hpp"

namespace ecs
{
    void Systems::Drawable(Registry &registry, SparseArray<component::Drawable> const &drawable, graphics::Graphical &graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (drawable.at(it))
                    graphical.getWindow().draw(graphical.getAllSprites().at(it));
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
} // namespace ecs

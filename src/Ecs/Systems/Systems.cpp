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
    void Systems::Clickable(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical &graphical)
    {
        auto mouse_pos = sf::Mouse::getPosition(graphical.getWindow());          // Mouse position relative to the window
        auto translated_pos = graphical.getWindow().mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates

        for (auto &it : registry.getEntities()) {
            try {
                if (clickable.at(it)) { // probleme a ce .at de merde
                    if (graphical.getAllSprites().at(it).getGlobalBounds().contains(translated_pos)) {
                        switch (clickable.at(it).value().getFunction()) {
                            case ecs::Clickable::Function::EXIT: graphical.getWindow().close(); break;
                            default: break;
                        }
                    }
                }
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

    void Systems::Drawable(Registry &registry, SparseArray<ecs::Drawable> const &drawable, graphics::Graphical &graphical)
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

    void Systems::Position(Registry &registry, SparseArray<ecs::Position> const &position, graphics::Graphical &graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (position.at(it))
                    graphical.setSpritePosition(it, position.at(it).value().getXPosition(), position.at(it).value().getYPosition());
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
} // namespace ecs

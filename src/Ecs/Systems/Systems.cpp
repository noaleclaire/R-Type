/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#include "Systems.hpp"
#include "../Exceptions/ExceptionIndexComponent.hpp"
#include "../Exceptions/ExceptionComponentNull.hpp"

namespace ecs
{
    void Systems::Clickable(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                clickable.at(it);
                if (graphical->getAllSprites().at(it).getGlobalBounds().contains(graphical->getEvent().mouseButton.x, graphical->getEvent().mouseButton.y)) {
                    switch (clickable.at(it).value().getFunction()) {
                        case Clickable::Function::EXIT: graphical->getWindow().close(); break;
                        default: break;
                    }
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

    void Systems::Drawable(Registry &registry, SparseArray<ecs::Drawable> const &drawable, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                drawable.at(it);
                graphical->getWindow().draw(graphical->getAllSprites().at(it));
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

    void Systems::Position(Registry &registry, SparseArray<ecs::Position> const &position, graphics::Graphical &graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                position.at(it);
                graphical.setSpritePosition(it, position.at(it).value().getXPosition(), position.at(it).value().getYPosition());
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
} // namespace ecs

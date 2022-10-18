/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#include "Systems.hpp"
#include "../../client/Core.hpp"
#include "../Exceptions/ExceptionComponentNull.hpp"
#include "../Exceptions/ExceptionIndexComponent.hpp"

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
                        case Clickable::Function::TOGAME: Core::actual_scene = ecs::Scenes::GAME; break;
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
                graphical.setSpritePosition(it, position.at(it).value().getXPosition(), position.at(it).value().getYPosition());
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::Controllable(Registry &registry, SparseArray<ecs::Controllable> const &controllable, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                controllable.at(it);
                if (graphical->getEvent().key.code == sf::Keyboard::Key::Z) {
                    auto pos = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                    registry.getComponents<ecs::Position>().at(it).value().setYPosition(
                        pos - registry.getComponents<ecs::Position>().at(it).value().getYVelocity());
                }
                if (graphical->getEvent().key.code == sf::Keyboard::Key::Q) {
                    auto pos = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                    registry.getComponents<ecs::Position>().at(it).value().setXPosition(
                        pos - registry.getComponents<ecs::Position>().at(it).value().getXVelocity());
                }
                if (graphical->getEvent().key.code == sf::Keyboard::Key::S) {
                    auto pos = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                    registry.getComponents<ecs::Position>().at(it).value().setYPosition(
                        pos + registry.getComponents<ecs::Position>().at(it).value().getYVelocity());
                }
                if (graphical->getEvent().key.code == sf::Keyboard::Key::D) {
                    auto pos = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                    registry.getComponents<ecs::Position>().at(it).value().setXPosition(
                        pos + registry.getComponents<ecs::Position>().at(it).value().getXVelocity());
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::Parallaxe(Registry &registry, SparseArray<ecs::Type> const &type)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (type.at(it).value().getEntityType() == ecs::EntityTypes::BACKGROUND || type.at(it).value().getEntityType() == ecs::EntityTypes::WALL) {
                    auto posX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                    registry.getComponents<ecs::Position>().at(it).value().setXPosition(
                        posX - registry.getComponents<ecs::Position>().at(it).value().getXVelocity());
                    // auto posY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                    // registry.getComponents<ecs::Position>().at(it).value().setYPosition(posY -
                    // registry.getComponents<ecs::Position>().at(it).value().getYVelocity());
                    if (registry.getComponents<ecs::Position>().at(it).value().getXPosition()
                        <= -registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle()) {
                        registry.getComponents<ecs::Position>().at(it).value().setXPosition(
                            registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle());
                    }
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
} // namespace ecs

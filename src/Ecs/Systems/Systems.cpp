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
        for (std::size_t i = 0; i < registry.getEntities().size(); i++) {
            for (auto &it : registry.getEntities()) {
                try {
                    drawable.at(it);
                    registry.getComponents<ecs::Layer>().at(it);
                    if (registry.getComponents<ecs::Layer>().at(it).value().getLayer() == i) {
                        try {
                            graphical->getWindow().draw(graphical->getAllSprites().at(it));
                        } catch (const std::out_of_range &e) {}
                    }
                } catch (const ExceptionComponentNull &e) {
                    continue;
                } catch (const ExceptionIndexComponent &e) {
                    continue;
                }
            }
        }
    }

    void Systems::Position(Registry &registry, SparseArray<ecs::Position> const &position, graphics::Graphical &graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                float posX = position.at(it).value().getXPosition();
                float posY = position.at(it).value().getYPosition();
                float veloX = position.at(it).value().getXVelocity();
                float veloY = position.at(it).value().getYVelocity();
                try {
                    registry.getComponents<ecs::Controllable>().at(it);
                    veloX = 0;
                    veloY = 0;
                    if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("z") == true)
                        veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity();
                    if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("q") == true)
                        veloX -= registry.getComponents<ecs::Position>().at(it).value().getXVelocity();
                    if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("s") == true)
                        veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity();
                    if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("d") == true)
                        veloX += registry.getComponents<ecs::Position>().at(it).value().getXVelocity();
                } catch (const ExceptionComponentNull &e) {}
                catch (const ExceptionIndexComponent &e) {}
                posX += veloX * graphics::Graphical::world_current_time;
                posY += veloY * graphics::Graphical::world_current_time;
                registry.getComponents<ecs::Position>().at(it).value().setXPosition(posX);
                registry.getComponents<ecs::Position>().at(it).value().setYPosition(posY);
                graphical.setSpritePosition(it, posX, posY);
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::Controllable(Registry &registry, SparseArray<ecs::Controllable> &controllable, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                controllable.at(it);
                if (graphical->getEvent().type == sf::Event::KeyPressed) {
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Z)
                        controllable.at(it).value().setKey("z", true);
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Q)
                        controllable.at(it).value().setKey("q", true);
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::S)
                        controllable.at(it).value().setKey("s", true);
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::D)
                        controllable.at(it).value().setKey("d", true);
                }
                if (graphical->getEvent().type == sf::Event::KeyReleased) {
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Z)
                        controllable.at(it).value().setKey("z", false);
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Q)
                        controllable.at(it).value().setKey("q", false);
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::S)
                        controllable.at(it).value().setKey("s", false);
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::D)
                        controllable.at(it).value().setKey("d", false);
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

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
#include <cmath>

namespace ecs
{
    void Systems::ClickableReleased(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical)
    {
        unselectAllTextBoxes(registry, registry.getComponents<ecs::TextBox>());
        for (auto &it : registry.getEntities()) {
            try {
                clickable.at(it);
                try {
                    if (graphical->getAllSprites().at(it).getGlobalBounds().contains(graphical->getEvent().mouseButton.x, graphical->getEvent().mouseButton.y)) {
                        switch (clickable.at(it).value().getFunction()) {
                            case Clickable::Function::EXIT: graphical->getWindow().close(); break;
                            case Clickable::Function::TOGAME: Core::actual_scene = ecs::Scenes::GAME; break;
                            case Clickable::Function::TOSETTINGS: Core::actual_scene = ecs::Scenes::SETTINGS; break;
                            case Clickable::Function::TOMENU: Core::actual_scene = ecs::Scenes::MENU; break;
                            default: break;
                        }
                    }
                } catch (const std::out_of_range &e) {}
                try {
                    if (graphical->getAllRectangleShapes().at(it).getGlobalBounds().contains(graphical->getEvent().mouseButton.x, graphical->getEvent().mouseButton.y)) {
                        switch (clickable.at(it).value().getFunction()) {
                            case Clickable::Function::TEST2:
                                registry.getComponents<ecs::TextBox>().at(it).value().select();
                                break;
                            default: break;
                        }
                    }
                } catch (const std::out_of_range &e) {}
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::unselectAllTextBoxes(Registry &registry, SparseArray<ecs::TextBox> &textBox)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (textBox.at(it).value().isSelected())
                    textBox.at(it).value().unselect();
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::ClickableHeld(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                clickable.at(it);
                try {
                    if (graphical->getAllRectangleShapes().at(it).getGlobalBounds().contains(graphical->getEvent().mouseMove.x, graphical->getEvent().mouseMove.y)) {
                        switch (clickable.at(it).value().getFunction()) {
                            case Clickable::Function::TEST: changeVolume(registry, it, graphical); break;
                            default: break;
                        }
                    }
                } catch (const std::out_of_range &e) {}
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

    void Systems::changeVolume(Registry &registry, std::size_t entity, graphics::Graphical *graphical)
    {
        std::size_t linked_entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
        std::size_t linked_text = registry.getComponents<ecs::Link>().at(linked_entity).value().getLink();
        float entity_posX = registry.getComponents<ecs::Position>().at(entity).value().getXPosition();
        float volume = 0.0f;

        registry.getComponents<ecs::Rectangle>().at(linked_entity).value().setWidthRectangle(graphical->getEvent().mouseMove.x - entity_posX);
        graphical->setRectangleShapeRect(linked_entity, registry.getComponents<ecs::Rectangle>().at(linked_entity).value().getWidthRectangle(), 80);
        volume = std::ceil((registry.getComponents<ecs::Rectangle>().at(linked_entity).value().getWidthRectangle() * 100)/registry.getComponents<ecs::Rectangle>().at(entity).value().getWidthRectangle());
        graphical->setTextString(linked_text, std::to_string(static_cast<int>(volume)) + "%");
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
                        try {
                            graphical->getWindow().draw(graphical->getAllRectangleShapes().at(it));
                        } catch (const std::out_of_range &e) {}
                        try {
                            graphical->getWindow().draw(graphical->getAllTexts().at(it));
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
                try {
                    graphical.setSpritePosition(it, posX, posY);
                } catch (const std::out_of_range &e) {}
                try {
                    graphical.setRectangleShapePosition(it, posX, posY);
                } catch (const std::out_of_range &e) {}
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
    void Systems::TextBox(Registry &registry, SparseArray<ecs::TextBox> &textBox, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (textBox.at(it).value().isSelected()) {
                    std::size_t linked_text = registry.getComponents<ecs::Link>().at(it).value().getLink();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        textBox.at(it).value().unselect();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                        graphical->setTextString(linked_text, graphical->getTextString(linked_text).substr(0, graphical->getTextString(linked_text).size() - 1));
                    }
                    if ((graphical->getEvent().text.unicode >= '0' && graphical->getEvent().text.unicode <= '9') ||
                        (graphical->getEvent().text.unicode >= 'a' && graphical->getEvent().text.unicode <= 'z') ||
                        (graphical->getEvent().text.unicode >= 'A' && graphical->getEvent().text.unicode <= 'Z')){
                        graphical->setTextString(linked_text, graphical->getTextString(linked_text) + static_cast<char>(graphical->getEvent().text.unicode));
                    }
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::Hover(Registry &registry, SparseArray<ecs::Hover> &hover, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                hover.at(it);
                try {
                    if (graphical->getAllSprites().at(it).getGlobalBounds().contains(graphical->getEvent().mouseMove.x, graphical->getEvent().mouseMove.y)) {
                        graphical->setHoverSprite(it);
                    } else {
                        graphical->setBasicSprite(it);
                    }
                } catch (const ExceptionComponentNull &e) {
                    continue;
                } catch (const ExceptionIndexComponent &e) {
                    continue;
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#include <cmath>
#include "Systems.hpp"
#include "../../client/Core.hpp"
#include "../../client/Exceptions/Exception.hpp"
#include "../Exceptions/ExceptionComponentNull.hpp"
#include "../Exceptions/ExceptionIndexComponent.hpp"
#include "../Factory.hpp"

namespace ecs
{
    void Systems::ClickableReleased(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical)
    {
        _unselectAllTextBoxes(registry, registry.getComponents<ecs::TextBox>());
        for (auto &it : registry.getEntities()) {
            try {
                clickable.at(it);
                try {
                    if (graphical->getAllSprites().at(it).getGlobalBounds().contains(graphical->getEvent().mouseButton.x, graphical->getEvent().mouseButton.y)
                    && registry.getComponents<ecs::Drawable>().at(it)) {
                        switch (clickable.at(it).value().getFunction()) {
                            case Clickable::Function::EXIT: graphical->getWindow().close(); break;
                            case Clickable::Function::TOGAME: Core::actual_scene = ecs::Scenes::GAME; break;
                            case Clickable::Function::TOSETTINGS: Core::actual_scene = ecs::Scenes::SETTINGS; break;
                            case Clickable::Function::TOMENU: Core::actual_scene = ecs::Scenes::MENU; break;
                            case Clickable::Function::TOHTP: Core::actual_scene = ecs::Scenes::HOWTOPLAY; break;
                            case Clickable::Function::TOACHIEVEMENTS: Core::actual_scene = ecs::Scenes::ACHIEVEMENTS; break;
                            case Clickable::Function::CREATEPUBLICROOM: Core::actual_scene = ecs::Scenes::PUBLICROOM; break;
                            case Clickable::Function::CREATEPRIVATEROOM: Core::actual_scene = ecs::Scenes::PRIVATEROOM; break;
                            case Clickable::Function::LISTROOM: Core::actual_scene = ecs::Scenes::LISTROOM; break;
                            case Clickable::Function::FILTERBYROOMMODECOOP:
                                graphical->client->filterByRoomModeCoop();
                                std::this_thread::sleep_for(std::chrono::milliseconds(ecs::Enum::ping_latency_ms)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
                                break;
                            case Clickable::Function::FILTERBYROOMMODEVERSUS:
                                graphical->client->filterByRoomModeVersus();
                                std::this_thread::sleep_for(std::chrono::milliseconds(ecs::Enum::ping_latency_ms)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
                                break;
                            case Clickable::Function::REFRESHFILTERSROOM:
                                graphical->client->initListRoom();
                                std::this_thread::sleep_for(std::chrono::milliseconds(ecs::Enum::ping_latency_ms)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
                                break;
                            case Clickable::Function::JOINROOM: Core::actual_scene = registry.getComponents<ecs::CompoScene>().at(it).value().getScene(); break;
                            case Clickable::Function::JOINROOMBYID:
                                if (graphical->getTextString(registry.getComponents<ecs::Link>().at(it).value().getLink()).size() > 0) {
                                    Core::room_id = graphical->getTextString(registry.getComponents<ecs::Link>().at(it).value().getLink());
                                    Core::actual_scene = ecs::Scenes::JOINROOMBYID;
                                }
                                break;
                            case Clickable::Function::QUITROOM: Core::actual_scene = ecs::Scenes::QUITROOM; break;
                            case Clickable::Function::SWITCHROOMMODE:
                                graphical->client->switchRoomMode();
                                std::this_thread::sleep_for(std::chrono::milliseconds(ecs::Enum::ping_latency_ms)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
                                break;
                            case Clickable::Function::CONFIRMPSEUDO:
                                if (graphical->getTextString(registry.getComponents<ecs::Link>().at(it).value().getLink()).size() > 0)
                                    Core::new_pseudo = graphical->getTextString(registry.getComponents<ecs::Link>().at(it).value().getLink());
                                break;
                            case Clickable::Function::SELECTTEXTBOX:
                                registry.getComponents<ecs::TextBox>().at(it).value().select();
                                break;
                            case Clickable::Function::SELECTPLANET:
                                _unselectAllPlanet(registry, registry.getComponents<ecs::Planet>(), graphical);
                                registry.getComponents<ecs::Planet>().at(it).value().select();
                                graphical->getAllSprites().at(it).setScale(sf::Vector2f(1.25, 1.25));
                                registry.getComponents<ecs::Position>().at(it).value().setXPosition(registry.getComponents<ecs::Position>().at(it).value().getXPosition() - registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle()/5);
                                Core::level_id = registry.getComponents<ecs::Planet>().at(it).value().getLevelID() - 1;
                                break;
                            default: break;
                        }
                        if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::BUTTON)
                            graphical->setBasicSprite(it);
                    }
                } catch (const std::out_of_range &e) {}
                try {
                    if (graphical->getAllRectangleShapes().at(it).getGlobalBounds().contains(graphical->getEvent().mouseButton.x, graphical->getEvent().mouseButton.y)) {
                        switch (clickable.at(it).value().getFunction()) {
                            case Clickable::Function::SELECTTEXTBOX:
                                registry.getComponents<ecs::TextBox>().at(it).value().select();
                                break;
                            case Clickable::Function::XITING:
                                Core::xiting_times++;
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

    void Systems::_unselectAllPlanet(Registry &registry, SparseArray<ecs::Planet> &planet, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (planet.at(it).value().isSelected() == true) {
                    planet.at(it).value().unselect();
                    graphical->getAllSprites().at(it).setScale(sf::Vector2f(1, 1));
                    registry.getComponents<ecs::Position>().at(it).value().setXPosition(registry.getComponents<ecs::Position>().at(it).value().getXPosition() + registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle()/5);
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

    void Systems::ClickablePressed(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                clickable.at(it);
                registry.getComponents<ecs::Pressed>().at(it);
                registry.getComponents<ecs::Type>().at(it);
                try {
                    if (graphical->getAllSprites().at(it).getGlobalBounds().contains(graphical->getEvent().mouseButton.x, graphical->getEvent().mouseButton.y)
                    && registry.getComponents<ecs::Drawable>().at(it)) {
                        if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::BUTTON
                        && graphical->sprites_manager->getNbAnimation(registry.getComponents<ecs::Type>().at(it).value().getEntityType(), registry.getComponents<ecs::Type>().at(it).value().getEntityID()) == 3) {
                            graphical->setPressedSprite(it);
                        } else {
                            graphical->setBasicSprite(it);
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
    void Systems::_unselectAllTextBoxes(Registry &registry, SparseArray<ecs::TextBox> &textBox)
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
                            case Clickable::Function::CHANGEMUSICVOLUME: Core::new_music_volume = _changeVolume(registry, it, graphical); graphical->getActualMusic().setVolume(Core::new_music_volume); break;
                            case Clickable::Function::CHANGESFXVOLUME: Core::new_sfx_volume = _changeVolume(registry, it, graphical); break;
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

    int Systems::_changeVolume(Registry &registry, std::size_t entity, graphics::Graphical *graphical)
    {
        std::size_t linked_entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
        std::size_t linked_text = registry.getComponents<ecs::Link>().at(linked_entity).value().getLink();
        float entity_posX = registry.getComponents<ecs::Position>().at(entity).value().getXPosition();
        float volume = 0.0f;

        registry.getComponents<ecs::Rectangle>().at(linked_entity).value().setWidthRectangle(graphical->getEvent().mouseMove.x - entity_posX);
        graphical->setRectangleShapeRect(linked_entity, registry.getComponents<ecs::Rectangle>().at(linked_entity).value().getWidthRectangle(), registry.getComponents<ecs::Rectangle>().at(linked_entity).value().getHeightRectangle());
        volume = std::ceil((registry.getComponents<ecs::Rectangle>().at(linked_entity).value().getWidthRectangle() * 100)/registry.getComponents<ecs::Rectangle>().at(entity).value().getWidthRectangle());
        graphical->setTextString(linked_text, std::to_string(static_cast<int>(volume)) + "%");
        return (volume);
    }

    void Systems::Drawable(Registry &registry, SparseArray<ecs::Drawable> const &drawable, graphics::Graphical *graphical)
    {
        for (std::size_t i = 0; i <= 15; i++) {
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
                    if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("z") == true) {
                        veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity();
                    }
                    if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("q") == true) {
                        veloX -= registry.getComponents<ecs::Position>().at(it).value().getXVelocity();
                    }
                    if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("s") == true) {
                        veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity();
                    }
                    if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("d") == true) {
                        veloX += registry.getComponents<ecs::Position>().at(it).value().getXVelocity();
                    }
                    if (veloX != 0 || veloY != 0)
                        registry.addComponent<ecs::Animation>(registry.getEntityById(it), ecs::Animation());
                    else {
                        registry.removeComponent<ecs::Animation>(registry.getEntityById(it));
                        auto rect = graphical.sprites_manager->get_Animations_rect(registry.getComponents<ecs::Type>().at(it).value().getEntityType(), registry.getComponents<ecs::Type>().at(it).value().getEntityID());
                        graphical.setTextureRectSprite(it, rect.at(0), rect.at(1), rect.at(2), rect.at(3));
                    }
                } catch (const Exception &e) {}
                // posX += veloX * graphics::Graphical::world_current_time * graphics::Graphical::window_factor.first;
                // posY += veloY * graphics::Graphical::world_current_time * graphics::Graphical::window_factor.second;
                posX += veloX * graphics::Graphical::world_current_time;
                posY += veloY * graphics::Graphical::world_current_time;
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::SPACESHIP) {
                    if (posX < 0)
                        posX = 0;
                    if (posX > graphical.getWindow().getSize().x - registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle())
                        posX = graphical.getWindow().getSize().x - registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle();
                    if (posY < 0)
                        posY = 0;
                    if (posY > graphical.getWindow().getSize().y - registry.getComponents<ecs::Rectangle>().at(it).value().getHeightRectangle())
                        posY = graphical.getWindow().getSize().y - registry.getComponents<ecs::Rectangle>().at(it).value().getHeightRectangle();
                }
                registry.getComponents<ecs::Position>().at(it).value().setXPosition(posX);
                registry.getComponents<ecs::Position>().at(it).value().setYPosition(posY);
                try {
                    graphical.setSpritePosition(it, posX, posY);
                    // graphical.getAllSprites().at(it).setScale(graphics::Graphical::window_factor.first, graphics::Graphical::window_factor.second);
                } catch (const std::out_of_range &e) {}
                try {
                    graphical.setRectangleShapePosition(it, posX, posY);
                    // graphical.getAllRectangleShapes().at(it).setScale(graphics::Graphical::window_factor.first, graphics::Graphical::window_factor.second);
                } catch (const std::out_of_range &e) {}
                try {
                    graphical.getAllTexts().at(it).setPosition(posX, posY);
                    // graphical.getAllTexts().at(it).setScale(graphics::Graphical::window_factor.first, graphics::Graphical::window_factor.second);
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
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Z) {
                        controllable.at(it).value().setKey("z", true);
                        graphical->client->sendPlayerPos(0, true, it, registry.getComponents<ecs::Position>().at(it).value(), registry.getComponents<ecs::Rectangle>().at(it).value());
                    }
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Q) {
                        controllable.at(it).value().setKey("q", true);
                        graphical->client->sendPlayerPos(1, true, it, registry.getComponents<ecs::Position>().at(it).value(), registry.getComponents<ecs::Rectangle>().at(it).value());
                    }
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::S) {
                        controllable.at(it).value().setKey("s", true);
                        graphical->client->sendPlayerPos(2, true, it, registry.getComponents<ecs::Position>().at(it).value(), registry.getComponents<ecs::Rectangle>().at(it).value());
                    }
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::D) {
                        controllable.at(it).value().setKey("d", true);
                        graphical->client->sendPlayerPos(3, true, it, registry.getComponents<ecs::Position>().at(it).value(), registry.getComponents<ecs::Rectangle>().at(it).value());
                    }
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Space)
                        controllable.at(it).value().setKey("space", true);
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::LShift)
                        controllable.at(it).value().setKey("shift", true);
                }
                if (graphical->getEvent().type == sf::Event::KeyReleased) {
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Z) {
                        controllable.at(it).value().setKey("z", false);
                        graphical->client->sendPlayerPos(0, false, it, registry.getComponents<ecs::Position>().at(it).value(), registry.getComponents<ecs::Rectangle>().at(it).value());
                    }
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Q) {
                        controllable.at(it).value().setKey("q", false);
                        graphical->client->sendPlayerPos(1, false, it, registry.getComponents<ecs::Position>().at(it).value(), registry.getComponents<ecs::Rectangle>().at(it).value());
                    }
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::S) {
                        controllable.at(it).value().setKey("s", false);
                        graphical->client->sendPlayerPos(2, false, it, registry.getComponents<ecs::Position>().at(it).value(), registry.getComponents<ecs::Rectangle>().at(it).value());
                    }
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::D) {
                        controllable.at(it).value().setKey("d", false);
                        graphical->client->sendPlayerPos(3, false, it, registry.getComponents<ecs::Position>().at(it).value(), registry.getComponents<ecs::Rectangle>().at(it).value());
                    }
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Space)
                        controllable.at(it).value().setKey("space", false);
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::Shot(Registry &registry, SparseArray<ecs::Controllable> &controllable, CustomClient *client)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (controllable.at(it).value().getKey("space") == true)
                    _createShot(registry, it, client);
                if (controllable.at(it).value().getKey("shift") == true) {
                    controllable.at(it).value().setKey("shift", false);
                    if (registry.getComponents<ecs::Shooter>().at(it).value().getAmmoType() == ecs::Ammo::AmmoType::CLASSIC) {
                        registry.getComponents<ecs::Shooter>().at(it).value().setAmmoType(ecs::Ammo::AmmoType::BEAM);
                        std::cout << "BEAM" << std::endl;
                    } else if (registry.getComponents<ecs::Shooter>().at(it).value().getAmmoType() == ecs::Ammo::AmmoType::BEAM) {
                        registry.getComponents<ecs::Shooter>().at(it).value().setAmmoType(ecs::Ammo::AmmoType::CLASSIC);
                        std::cout << "CLASSIC" << std::endl;
                    }
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

    void Systems::_createShot(Registry &registry, std::size_t linked_entity, CustomClient *client)
    {
        ecs::Ammo::AmmoType ammoType = registry.getComponents<ecs::Shooter>().at(linked_entity).value().getAmmoType();

        if ((std::chrono::system_clock::now() - registry.getComponents<ecs::Shooter>().at(linked_entity).value().getLastShot()) >= std::chrono::milliseconds(ecs::Ammo::ammoAttributesByType.at(ammoType).shot_rate)) {
            registry.getComponents<ecs::Shooter>().at(linked_entity).value().setLastShot();
            client->createShot(linked_entity, registry.getActualScene());
        }
    }

    void Systems::Parallaxe(Registry &registry, SparseArray<ecs::Type> const &type)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (type.at(it).value().getEntityType() == ecs::EntityTypes::BACKGROUND
                || type.at(it).value().getEntityType() == ecs::EntityTypes::PARALLAX
                || type.at(it).value().getEntityType() == ecs::EntityTypes::WALL) {
                    if (registry.getComponents<ecs::Position>().at(it).value().getXPosition()
                    + registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle() < 1) {
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
                    if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::TEXTBOXNUMBER) {
                        if (graphical->getEvent().text.unicode >= '0' && graphical->getEvent().text.unicode <= '9') {
                            if (graphical->getTextString(linked_text).size() < textBox.at(it).value().getMaxSize())
                                graphical->setTextString(linked_text, graphical->getTextString(linked_text) + static_cast<char>(graphical->getEvent().text.unicode));
                        }
                    } else if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::TEXTBOX) {
                        if ((graphical->getEvent().text.unicode >= '0' && graphical->getEvent().text.unicode <= '9') ||
                            (graphical->getEvent().text.unicode >= 'a' && graphical->getEvent().text.unicode <= 'z') ||
                            (graphical->getEvent().text.unicode >= 'A' && graphical->getEvent().text.unicode <= 'Z')){
                            if (graphical->getTextString(linked_text).size() < textBox.at(it).value().getMaxSize())
                                graphical->setTextString(linked_text, graphical->getTextString(linked_text) + static_cast<char>(graphical->getEvent().text.unicode));
                        }
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
                registry.getComponents<ecs::Type>().at(it);
                try {
                    graphical->setBasicSprite(it);
                    if (graphical->getAllSprites().at(it).getGlobalBounds().contains(graphical->getEvent().mouseMove.x, graphical->getEvent().mouseMove.y)
                    && registry.getComponents<ecs::Drawable>().at(it)) {
                        if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::BUTTON
                        && graphical->sprites_manager->getNbAnimation(registry.getComponents<ecs::Type>().at(it).value().getEntityType(), registry.getComponents<ecs::Type>().at(it).value().getEntityID()) == 3)
                            graphical->setHoverSprite(it);
                    }
                } catch (const std::out_of_range &e) {}
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::setUserInfoInSettings(Registry &registry, graphics::Graphical &graphical, std::string pseudo, int music_volume, int sfx_volume)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::PSEUDO)
                    graphical.setTextString(it, pseudo);
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::MUSIC)
                    graphical.setTextString(it, std::to_string(music_volume).append("%"));
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::SFX)
                    graphical.setTextString(it, std::to_string(sfx_volume).append("%"));
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::Animation(Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical)
    {
        ecs::EntityTypes entity_type;
        std::size_t entity_id = 0;
        std::vector<float> rect;
        for (auto &it : registry.getEntities()) {
            try {
                registry.getComponents<ecs::Animation>().at(it);
                registry.getComponents<ecs::Type>().at(it);
                registry.getComponents<ecs::Rectangle>().at(it);
                entity_type = registry.getComponents<ecs::Type>().at(it).value().getEntityType();
                entity_id = registry.getComponents<ecs::Type>().at(it).value().getEntityID();

                if (registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle() != 0 && registry.getComponents<ecs::Rectangle>().at(it).value().getHeightRectangle() != 0) {
                    sprites_manager.setAnimationCurrentFrame(entity_type, entity_id,
                        sprites_manager.getAnimationCurrentFrame(entity_type, entity_id) +
                        graphics::Graphical::world_current_time *
                        sprites_manager.getSpeedAnimation(entity_type, entity_id,
                            sprites_manager.getIndexCurrentAnimation(entity_type, entity_id))
                    );

                    if (sprites_manager.getAnimationCurrentFrame(entity_type, entity_id) >=
                    sprites_manager.getNbAnimation(entity_type, entity_id,
                    sprites_manager.getIndexCurrentAnimation(entity_type, entity_id))) {
                        if (sprites_manager.getNextAnimation(entity_type, entity_id,
                        sprites_manager.getIndexCurrentAnimation(entity_type, entity_id)) != -1) {
                            sprites_manager.setIndexCurrentAnimation(entity_type, entity_id,
                            sprites_manager.getNextAnimation(entity_type, entity_id,
                            sprites_manager.getIndexCurrentAnimation(entity_type, entity_id)));
                            rect = sprites_manager.get_Animations_rect(entity_type, entity_id, sprites_manager.getIndexCurrentAnimation(entity_type, entity_id));
                            registry.getComponents<ecs::Rectangle>().at(it).value().setXRectangle(rect.at(rect_x));
                            registry.getComponents<ecs::Rectangle>().at(it).value().setYRectangle(rect.at(rect_y));
                            registry.getComponents<ecs::Rectangle>().at(it).value().setWidthRectangle(rect.at(rect_width));
                            registry.getComponents<ecs::Rectangle>().at(it).value().setHeightRectangle(rect.at(rect_height));
                            sprites_manager.setDoNextAnimation(entity_type, entity_id, false);
                        }
                        sprites_manager.setAnimationCurrentFrame(entity_type, entity_id, 0);
                        sprites_manager.setLastCurrentFrame(entity_type, entity_id, -1);
                    }
                    if (std::floor(sprites_manager.getAnimationCurrentFrame(entity_type, entity_id)) != sprites_manager.getLastCurrentFrame(entity_type, entity_id)) {
                            registry.getComponents<ecs::Rectangle>().at(it).value().setXRectangle(
                                registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle() *
                                static_cast<int>(sprites_manager.getAnimationCurrentFrame(entity_type, entity_id))
                            );
                            graphical.setTextureRectSprite(it, registry.getComponents<ecs::Rectangle>().at(it).value().getXRectangle(), registry.getComponents<ecs::Rectangle>().at(it).value().getYRectangle(),
                                registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle(), registry.getComponents<ecs::Rectangle>().at(it).value().getHeightRectangle());
                            sprites_manager.setLastCurrentFrame(entity_type, entity_id, sprites_manager.getLastCurrentFrame(entity_type, entity_id) + 1);
                    }
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            } catch (const ::Exception &e) {
                continue;
            }
        }
    }
    void Systems::Collider(Registry &registry, SparseArray<ecs::Collider> &collider, graphics::Graphical &graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                collider.at(it);
                for (auto &it_in : registry.getEntities()) {
                    try {
                        collider.at(it_in);
                        if (it == it_in)
                            continue;
                        if (graphical.getAllSprites().at(it).getGlobalBounds().intersects(graphical.getAllSprites().at(it_in).getGlobalBounds())) {
                            if (registry.getComponents<ecs::Killable>().at(it_in).value().getLife() > 0) {
                                if ((registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::MONSTER && registry.getComponents<ecs::Type>().at(it_in).value().getEntityType() == ecs::EntityTypes::SPACESHIP) ||
                                    (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::WALL && registry.getComponents<ecs::Type>().at(it_in).value().getEntityType() == ecs::EntityTypes::SPACESHIP)) {
                                    registry.killEntity(registry.getEntityById(it_in));
                                    std::cout << "kill1" << std::endl;
                                    // registry.getComponents<ecs::Killable>().at(it_in).value().setLife(0);
                                    // if (graphical.client->is_host == true)
                                    //     graphical.client->sendNetworkComponents<network::CustomMessage>(it_in, network::CustomMessage::SendComponent);
                                }
                                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::SHOT && registry.getComponents<ecs::Type>().at(it_in).value().getEntityType() == ecs::EntityTypes::MONSTER) {
                                    registry.getComponents<ecs::Killable>().at(it_in).value().substractLife(registry.getComponents<ecs::Ammo>().at(it).value().getDamage());
                                    registry.killEntity(registry.getEntityById(it));
                                    registry.killEntity(registry.getEntityById(it_in));
                                    std::cout << "kill2" << std::endl;
                                    // registry.getComponents<ecs::Killable>().at(it).value().setLife(0);
                                    // if (graphical.client->is_host == true) {
                                    //     graphical.client->sendNetworkComponents<network::CustomMessage>(it_in, network::CustomMessage::SendComponent);
                                    //     graphical.client->sendNetworkComponents<network::CustomMessage>(it, network::CustomMessage::SendComponent);
                                    // }
                                }
                                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::WALL && registry.getComponents<ecs::Type>().at(it_in).value().getEntityType() == ecs::EntityTypes::SHOT) {
                                    registry.killEntity(registry.getEntityById(it_in));
                                    std::cout << "kill3" << std::endl;
                                    // registry.getComponents<ecs::Killable>().at(it_in).value().setLife(0);
                                    // if (graphical.client->is_host == true)
                                    //     graphical.client->sendNetworkComponents<network::CustomMessage>(it_in, network::CustomMessage::SendComponent);
                                }
                            }
                        }
                    } catch (const ExceptionComponentNull &e) {
                        continue;
                    } catch (const ExceptionIndexComponent &e) {
                        continue;
                    } catch (const std::out_of_range &e) {
                        continue;
                    }
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::Achievement(UserInfo *user_info)
    {
        if (Core::xiting_times >= 50)
            user_info->achievements.at(ecs::AchievementTypes::XITING) = static_cast<int>(true);
        if (std::strcmp("FuckMarvin", user_info->pseudo) == 0)
            user_info->achievements.at(ecs::AchievementTypes::MARVIN) = static_cast<int>(true);
    }
    void Systems::Achievement(Registry &registry, SparseArray<ecs::Achievement> &achievement, graphics::Graphical &graphical)
    {
        if (graphical.getEvent().type == sf::Event::KeyPressed) {
            for (auto &it : registry.getEntities()) {
                try {
                    achievement.at(it);
                    if (graphical.getEvent().key.code == sf::Keyboard::Key::Down) {
                        registry.getComponents<ecs::Position>().at(it).value().setYPosition(registry.getComponents<ecs::Position>().at(it).value().getYPosition() - 50);
                    }
                    if (graphical.getEvent().key.code == sf::Keyboard::Key::Up) {
                        registry.getComponents<ecs::Position>().at(it).value().setYPosition(registry.getComponents<ecs::Position>().at(it).value().getYPosition() + 50);
                    }
                } catch (const ExceptionComponentNull &e) {
                    continue;
                } catch (const ExceptionIndexComponent &e) {
                    continue;
                }
            }
        }
    }

    void Systems::setUserInfoInAchievements(Registry &registry, graphics::Graphical &graphical, UserInfo *user_info)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (user_info->achievements.at(registry.getComponents<ecs::Achievement>().at(it).value().getID()) == true) {
                    registry.addComponent<ecs::Drawable>(registry.getEntityById(registry.getComponents<ecs::Link>().at(it).value().getLink()), ecs::Drawable());
                    auto rect = graphical.sprites_manager->get_Animations_rect(ecs::EntityTypes::BACKGROUND, 20, 0);
                    registry.getComponents<ecs::Type>().at(it).value().setEntityID(20);
                    graphical.addSprite(it, graphical.sprites_manager->get_Spritesheet(ecs::EntityTypes::BACKGROUND, 20), rect);
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::_sendKillEntity(Registry &registry, std::size_t entity, graphics::Graphical &graphical, ecs::EntityTypes type)
    {
        if (registry.getComponents<ecs::Type>().at(entity).value().getEntityType() == type) {
            std::cout << "kill" << std::endl;
            registry.killEntity(registry.getEntityById(entity));
            // registry.getComponents<ecs::Killable>().at(entity).value().setLife(0);
            // if (graphical.client->is_host == true)
            //     graphical.client->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent);
        }
    }
    void Systems::Killable(ecs::Registry &registry, graphics::Graphical &graphical)
    {
        for (auto &it : registry.getEntities()) {
            try {
                registry.getComponents<ecs::Killable>().at(it);
                if (registry.getComponents<ecs::Position>().at(it).value().getXPosition() < -registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle()) {
                    _sendKillEntity(registry, it, graphical, ecs::EntityTypes::SHOT);
                    _sendKillEntity(registry, it, graphical, ecs::EntityTypes::MONSTER);
                }
                if (registry.getComponents<ecs::Position>().at(it).value().getXPosition() > graphical.getWindow().getSize().x) {
                    _sendKillEntity(registry, it, graphical, ecs::EntityTypes::SHOT);
                }
                if (registry.getComponents<ecs::Position>().at(it).value().getYPosition() < -registry.getComponents<ecs::Rectangle>().at(it).value().getHeightRectangle()) {
                    _sendKillEntity(registry, it, graphical, ecs::EntityTypes::SHOT);
                }
                if (registry.getComponents<ecs::Position>().at(it).value().getYPosition() > graphical.getWindow().getSize().y) {
                    _sendKillEntity(registry, it, graphical, ecs::EntityTypes::SHOT);
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    void Systems::updateWindowSize(Registry &registry, std::pair<float, float> new_factor)
    {
        graphics::Graphical::window_factor = new_factor;
        for (auto &it : registry.getEntities()) {
            try {
                registry.getComponents<ecs::WindowSized>().at(it);
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                try {
                    registry.getComponents<ecs::Position>().at(it).value().setXPosition(registry.getComponents<ecs::Position>().at(it).value().getXPosition() * graphics::Graphical::window_factor.first);
                    registry.getComponents<ecs::Position>().at(it).value().setYPosition(registry.getComponents<ecs::Position>().at(it).value().getYPosition() * graphics::Graphical::window_factor.second);
                    registry.addComponent<ecs::WindowSized>(registry.getEntityById(it), ecs::WindowSized());
                    continue;
                } catch (const ExceptionComponentNull &err) {
                    continue;
                } catch (const ExceptionIndexComponent &err) {
                    continue;
                }
            }
        }
    }
} // namespace ecs

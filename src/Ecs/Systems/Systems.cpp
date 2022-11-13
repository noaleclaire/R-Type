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
                            case Clickable::Function::CREATEPUBLICROOM: Core::actual_scene = ecs::Scenes::PUBLICROOM; break;
                            case Clickable::Function::CREATEPRIVATEROOM: Core::actual_scene = ecs::Scenes::PRIVATEROOM; break;
                            case Clickable::Function::LISTROOM: Core::actual_scene = ecs::Scenes::LISTROOM; break;
                            case Clickable::Function::FILTERBYROOMMODECOOP:
                                graphical->client->filterByRoomModeCoop();
                                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
                                break;
                            case Clickable::Function::FILTERBYROOMMODEVERSUS:
                                graphical->client->filterByRoomModeVersus();
                                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
                                break;
                            case Clickable::Function::REFRESHFILTERSROOM:
                                graphical->client->initListRoom();
                                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
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
                                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
                                break;
                            case Clickable::Function::CONFIRMPSEUDO:
                                if (graphical->getTextString(registry.getComponents<ecs::Link>().at(it).value().getLink()).size() > 0)
                                    Core::new_pseudo = graphical->getTextString(registry.getComponents<ecs::Link>().at(it).value().getLink());
                                break;
                            case Clickable::Function::SELECTTEXTBOX:
                                registry.getComponents<ecs::TextBox>().at(it).value().select();
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
                            case Clickable::Function::CHANGEMUSICVOLUME: Core::new_music_volume = _changeVolume(registry, it, graphical); break;
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
        for (std::size_t i = 0; i <= registry.getEntities().size(); i++) {
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
                try {
                    registry.getComponents<ecs::CompoServer>().at(it);
                } catch (ecs::Exception &err) {
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
                            graphical.client->sendComponentToServer(it, network::CustomMessage::UpdatePosPlayerServer, registry.getComponents<ecs::Position>().at(it).value());
                        }
                        if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("q") == true) {
                            veloX -= registry.getComponents<ecs::Position>().at(it).value().getXVelocity();
                            graphical.client->sendComponentToServer(it, network::CustomMessage::UpdatePosPlayerServer, registry.getComponents<ecs::Position>().at(it).value());
                        }
                        if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("s") == true) {
                            veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity();
                            graphical.client->sendComponentToServer(it, network::CustomMessage::UpdatePosPlayerServer, registry.getComponents<ecs::Position>().at(it).value());
                        }
                        if (registry.getComponents<ecs::Controllable>().at(it).value().getKey("d") == true) {
                            veloX += registry.getComponents<ecs::Position>().at(it).value().getXVelocity();
                            graphical.client->sendComponentToServer(it, network::CustomMessage::UpdatePosPlayerServer, registry.getComponents<ecs::Position>().at(it).value());
                        }
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
                }
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
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::Space)
                        controllable.at(it).value().setKey("space", true);
                    if (graphical->getEvent().key.code == sf::Keyboard::Key::LShift)
                        controllable.at(it).value().setKey("shift", true);
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

                sprites_manager.setAnimationCurrentFrame(entity_type, entity_id,
                    sprites_manager.getAnimationCurrentFrame(entity_type, entity_id) +
                    graphics::Graphical::world_current_time *
                    sprites_manager.getSpeedAnimation(entity_type, entity_id,
                        sprites_manager.getIndexCurrentAnimation(entity_type, entity_id))
                );

                registry.getComponents<ecs::Rectangle>().at(it).value().setXRectangle(
                    registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle() *
                    static_cast<int>(sprites_manager.getAnimationCurrentFrame(entity_type, entity_id))
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
                    }
                    sprites_manager.setAnimationCurrentFrame(entity_type, entity_id, 0);
                }
                graphical.setTextureRectSprite(it, registry.getComponents<ecs::Rectangle>().at(it).value().getXRectangle(), registry.getComponents<ecs::Rectangle>().at(it).value().getYRectangle(),
                    registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle(), registry.getComponents<ecs::Rectangle>().at(it).value().getHeightRectangle());
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            } catch (const ::Exception &e) {
                continue;
            }
        }
    }
} // namespace ecs

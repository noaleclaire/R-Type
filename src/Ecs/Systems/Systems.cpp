/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#include "Systems.hpp"
#include "../../client/Core.hpp"
#include "../../client/Exceptions/Exception.hpp"
#include "../Exceptions/ExceptionComponentNull.hpp"
#include "../Exceptions/ExceptionIndexComponent.hpp"
#include <cmath>

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
                            case Clickable::Function::JOINROOM: Core::actual_scene = registry.getComponents<ecs::CompoScene>().at(it).value().getScene(); break;
                            case Clickable::Function::JOINROOMBYID:
                                if (graphical->getTextString(registry.getComponents<ecs::Link>().at(it).value().getLink()).size() > 0) {
                                    Core::room_id = graphical->getTextString(registry.getComponents<ecs::Link>().at(it).value().getLink());
                                    Core::actual_scene = ecs::Scenes::JOINROOMBYID;
                                }
                                break;
                            case Clickable::Function::QUITROOM: Core::actual_scene = ecs::Scenes::QUITROOM; break;
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
        std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
        float spaceship_posX = 0;
        float spaceship_posY = 0;
        float monster_posX = 0;
        float monster_posY = 0;
        float redX = 0;
        float redY = 0;
        float greenX = 0;
        float greenY = 0;
        float blueX = 0;
        float blueY = 0;
        float spaceship_bossX = 0;
        float spaceship_bossY = 0;
        float wormsX = 0;
        float wormsY = 0;
        float magicianX = 0;
        float magicianY = 0;
        float iceX = 0;
        float iceY = 0;
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
                    spaceship_posX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                    spaceship_posY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
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
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BASIC_MONSTER) {
                    monster_posX = position.at(it).value().getXPosition();
                    monster_posY = position.at(it).value().getYPosition();
                    if (posX <= 1208 && posX >= spaceship_posX + 500) {
                        veloX -= registry.getComponents<ecs::Position>().at(it).value().getXVelocity() + 65;
                    }
                    if (posX <= 1208 && posX < spaceship_posX + 500) {
                        veloX += registry.getComponents<ecs::Position>().at(it).value().getXVelocity() + 65;
                    }
                    if (posY <= spaceship_posY) {
                        veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 65;
                    }
                    if (posY > spaceship_posY) {
                        veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 65;
                    }
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::GREEN_SHOT) {
                    if (posX < -100) {
                            posX = greenX + 200;
                            posY = greenY + 50;
                        }
                    veloX -= 300;
                    veloY = 0;
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::RED_SHOT) {
                    if (posX < -100) {
                        posX = redX + 200;
                        posY = redY + 50;
                    }
                    veloX -= 300;
                    veloY = 0;
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BLUE_SHOT) {
                    if (posX < -100) {
                        posX = blueX + 200;
                        posY = blueY + 50;
                    }
                    veloX -= 300;
                    veloY = 0;
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::SPACESHIP_SHOT) {
                    if (posX < -100) {
                        posX = spaceship_bossX + 350;
                        posY = spaceship_bossY;
                    }
                    veloX -= 300;
                    veloY = 0;
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::WORMS_SHOT) {
                    if (posX < -100) {
                        posX = wormsX;
                        posY = wormsY + 50;
                    }
                    veloX -= 300;
                    veloY = 0;
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::HEAD_SHOT) {
                    if (posX < -100) {
                        posX = iceX;
                        posY = iceY + 100;
                    }
                    veloX -= 300;
                    veloY = 0;
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BASIC_SHOT) {
                    if (posX < -100) {
                        registry.getComponents<ecs::Shootable>().at(it).value().setShooting(false);
                        if ((std::chrono::system_clock::now() - t) >= std::chrono::seconds(3)) {
                            posX = monster_posX;
                            posY = monster_posY;
                            t = std::chrono::system_clock::now();
                        }
                    }
                    if (posY >= spaceship_posY - 35 && posY <= spaceship_posY + 35 && registry.getComponents<ecs::Shootable>().at(it).value().getShooting() != true) {
                        veloX -= 500;
                        veloY = 0;
                        registry.getComponents<ecs::Shootable>().at(it).value().setShooting(true);
                        registry.getComponents<ecs::Shootable>().at(it).value().setBeenInRange(true);
                    }
                    if (registry.getComponents<ecs::Shootable>().at(it).value().getBeenInRange() == true)
                        veloX -= 500;
                    if (registry.getComponents<ecs::Shootable>().at(it).value().getShooting() != true && posX >= spaceship_posX + 500)
                        posX = monster_posX;
                    if (registry.getComponents<ecs::Shootable>().at(it).value().getShooting() != true && posX <= spaceship_posX + 500)
                        posX = monster_posX;
                    if (registry.getComponents<ecs::Shootable>().at(it).value().getShooting() != true && posY <= spaceship_posY)
                        posY = monster_posY;
                    if (registry.getComponents<ecs::Shootable>().at(it).value().getShooting() != true && posY > spaceship_posY)
                        posY = monster_posY;
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_FIRE_SPACESHIP) {
                    spaceship_bossX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                    spaceship_bossY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                    if (posY >= 0 && spaceship_posY <= 720/2) {
                        veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 70;
                    }
                    if (posY <= 225 && spaceship_posY > 720/2) {
                        veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 70;
                    }
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_FOREST_RED 
                    || registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_FOREST_GREEN
                    || registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_FOREST_BLUE) {
                    if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_FOREST_GREEN) {
                        greenX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                        greenY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                        if (spaceship_posY <= 720/2 && posY >= 0) {
                            veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 70;
                        }
                        if (spaceship_posY > 720/2 && posY <= 400) {
                            veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 70;
                        }
                        if (registry.getComponents<ecs::Position>().at(it).value().getGreenStart() != true) {
                            registry.getComponents<ecs::Position>().at(it).value().setGreenXPos(registry.getComponents<ecs::Position>().at(it).value().getXPosition());
                            registry.getComponents<ecs::Position>().at(it).value().setGreenYPos(registry.getComponents<ecs::Position>().at(it).value().getYPosition());
                            registry.getComponents<ecs::Position>().at(it).value().setGreenStart(true);
                        }
                    }
                    if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_FOREST_BLUE) {
                        blueX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                        blueY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                        if (spaceship_posY >= 720/2 && posY >= 0) {
                            veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 70;
                        }
                        if (spaceship_posY < 720/2 && posY <= 400) {
                            veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 70;
                        }
                        if (registry.getComponents<ecs::Position>().at(it).value().getBlueStart() != true) {
                            registry.getComponents<ecs::Position>().at(it).value().setBlueXPos(registry.getComponents<ecs::Position>().at(it).value().getXPosition());
                            registry.getComponents<ecs::Position>().at(it).value().setBlueYPos(registry.getComponents<ecs::Position>().at(it).value().getYPosition());
                            registry.getComponents<ecs::Position>().at(it).value().setBlueStart(true);
                        }
                    }
                    if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_FOREST_RED) {
                        redX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                        redY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                        if (spaceship_posY <= 720/2 && posY >= 0) {
                            veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 70;
                        }
                        if (spaceship_posY > 720/2 && posY <= 400) {
                            veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 70;
                        }
                        if (registry.getComponents<ecs::Position>().at(it).value().getRedStart() != true) {
                            registry.getComponents<ecs::Position>().at(it).value().setRedXPos(registry.getComponents<ecs::Position>().at(it).value().getXPosition());
                            registry.getComponents<ecs::Position>().at(it).value().setRedYPos(registry.getComponents<ecs::Position>().at(it).value().getYPosition());
                            registry.getComponents<ecs::Position>().at(it).value().setRedStart(true);
                        }
                    }
                    //faire des shots basics pour chacun des monstres
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_CAVERN_MAGICIAN) {
                    magicianX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                    magicianY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                    if (spaceship_posY <= 720/2 && posY >= 0) {
                            veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 100;
                    }
                    if (spaceship_posY > 720/2 && posY <= 220) {
                            veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 100;
                    }
                    // faire un shot qui target le player
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_ICE_HEADESTROYER) {
                    iceX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                    iceY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                    if (spaceship_posY <= 720/2 && posY >= 0) {
                            veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 100;
                    }
                    if (spaceship_posY > 720/2 && posY <= 131) {
                            veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 100;
                    }
                    // faire un shot tout droit
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::BOSS_DESERT_WORMS) {
                    wormsX = registry.getComponents<ecs::Position>().at(it).value().getXPosition();
                    wormsY = registry.getComponents<ecs::Position>().at(it).value().getYPosition();
                    if (posX <= 1090 && posX >= spaceship_posX + 300) {
                        veloX -= registry.getComponents<ecs::Position>().at(it).value().getXVelocity() + 100;
                    }
                    if (posX <= 1090 && posX < spaceship_posX + 300) {
                        veloX += registry.getComponents<ecs::Position>().at(it).value().getXVelocity() + 100;
                    }
                    if (spaceship_posY <= 720/2 && posY >= 0) {
                            veloY -= registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 100;
                    }
                    if (spaceship_posY > 720/2 && posY <= 130) {
                            veloY += registry.getComponents<ecs::Position>().at(it).value().getYVelocity() + 100;
                    }
                    // faire un shot tout droit
                }
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::FIRE_MONSTER 
                    || registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::CAVE_MONSTER
                    || registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::ICE_MONSTER
                    || registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::FOREST_MONSTER
                    || registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::DESERT_MONSTER) {
                    veloX -= 125;
                }
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
                // std::cout << "current_frame : " << sprites_manager.getAnimationCurrentFrame(entity_type, entity_id) << std::endl;

                if (registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle() != 0 && registry.getComponents<ecs::Rectangle>().at(it).value().getHeightRectangle() != 0) {
                    sprites_manager.setAnimationCurrentFrame(entity_type, entity_id,
                        sprites_manager.getAnimationCurrentFrame(entity_type, entity_id) +
                        graphics::Graphical::world_current_time *
                        sprites_manager.getSpeedAnimation(entity_type, entity_id,
                            sprites_manager.getIndexCurrentAnimation(entity_type, entity_id))
                    );
                    // std::cout << "current_frame 2 : " << sprites_manager.getAnimationCurrentFrame(entity_type, entity_id) << std::endl;

                    // std::cout << "rect : " << registry.getComponents<ecs::Rectangle>().at(it).value().getXRectangle() << std::endl;
                    // std::cout << "rect 2 : " << registry.getComponents<ecs::Rectangle>().at(it).value().getXRectangle() << std::endl;
                    if (sprites_manager.getAnimationCurrentFrame(entity_type, entity_id) >=
                    sprites_manager.getNbAnimation(entity_type, entity_id,
                    sprites_manager.getIndexCurrentAnimation(entity_type, entity_id))) {
                        //std::cout << "est" << std::endl;
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
} // namespace ecs

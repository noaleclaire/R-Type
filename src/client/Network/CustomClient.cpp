/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#include <typeindex>
#include <algorithm>
#include <cmath>
#include "CustomClient.hpp"
#include "../../Ecs/Exceptions/Exception.hpp"
#include "../Exceptions/Exception.hpp"

CustomClient::CustomClient(boost::asio::io_context &io_context, std::string host, unsigned short server_port)
    : network::UdpServerClient<network::CustomMessage>(io_context, host, server_port)
{
}

CustomClient::~CustomClient()
{
}

void CustomClient::pingServer()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::PingServer;
    ecs::Enum::ping_latency = std::chrono::system_clock::now();
    send(msg);
}

void CustomClient::initGame()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::InitGame;
    msg << *actual_scene;
    send(msg);
}

void CustomClient::getGame(ecs::Scenes room, std::size_t level_id)
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::SwitchToGame;
    msg << room << level_id;
    send(msg);
}

void CustomClient::createPublicRoom()
{
    ecs::Text player_name_class(const_cast<char *>(user_info->pseudo));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::CreatePublicRoom;
    msg << player_name_class;
    send(msg);
}

void CustomClient::createPrivateRoom()
{
    ecs::Text player_name_class(const_cast<char *>(user_info->pseudo));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::CreatePrivateRoom;
    msg << player_name_class;
    send(msg);
}

void CustomClient::initListRoom()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::InitListRoom;
    msg << -1;
    send(msg);
}

void CustomClient::joinRoom()
{
    ecs::Text player_name_class(const_cast<char *>(user_info->pseudo));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::JoinRoom;
    msg << player_name_class;
    msg << *actual_scene;
    send(msg);
}

void CustomClient::joinRoomById(int id_room)
{
    ecs::Text player_name_class(const_cast<char *>(user_info->pseudo));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::JoinRoomById;
    msg << player_name_class;
    msg << id_room;
    send(msg);
}

void CustomClient::quitRoom()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::QuitRoomServer;
    send(msg);
}

void CustomClient::switchRoomMode()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::SwitchRoomMode;
    send(msg);
}

void CustomClient::getPlanetInfo()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::GetPlanetInfo;
    send(msg);
}

void CustomClient::filterByRoomModeVersus()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::InitListRoom;
    msg << 1;
    send(msg);
}

void CustomClient::filterByRoomModeCoop()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::InitListRoom;
    msg << 0;
    send(msg);
}

void CustomClient::clientDisconnect()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::RemoveClient;
    send(msg);
}

void CustomClient::createShot(std::size_t linked_entity, ecs::Scenes scene)
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::CreateShot;
    msg << linked_entity << scene;
    send(msg);
}

void CustomClient::sendPlayerPos(int key, bool pressed, std::size_t entity, ecs::Position &pos, ecs::Rectangle &rect)
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::UpdatePosPlayerServer;
    msg << pressed << key << entity << pos << rect << *actual_scene;
    send(msg);
}

void CustomClient::onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    static_cast<void>(target_endpoint);
    switch (msg.header.id) {
        case network::CustomMessage::PingClient: {
            float latency =
                (std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count()
                - std::chrono::time_point_cast<std::chrono::microseconds>(ecs::Enum::ping_latency).time_since_epoch().count());
            latency /= 1000;
            ecs::Enum::ping_latency_ms = std::ceil(latency) + 10;
        } break;
        case network::CustomMessage::GetScene: {
            ecs::Scenes scene;
            msg >> scene;
            if (scene != ecs::Scenes::GAME1 && scene != ecs::Scenes::GAME2
            && scene != ecs::Scenes::GAME3 && scene != ecs::Scenes::RETURNTOGAME) {
                registry->setActualScene(scene);
                graphical->setActualGraphicsEntities(scene);
            } else {
                game_scene = scene;
            }
        } break;
        case network::CustomMessage::KillAnEntity: {
            std::size_t entity;
            msg >> entity;
            _killOneEntity(entity);
        } break;
        case network::CustomMessage::SendRoomMode: {
            try {
                bool mode = false;
                if (mode == false) {
                    if (*score > user_info->coop_high_score.at(*current_level_id - 1))
                        user_info->coop_high_score.at(*current_level_id - 1) = *score;
                } else {
                    if (*score > user_info->versus_high_score.at(*current_level_id - 1))
                        user_info->versus_high_score.at(*current_level_id - 1) = *score;
                }
            } catch (std::exception &e) {}
        } break;
        case network::CustomMessage::SendComponent: {
            std::size_t index_component_create = 0;
            std::size_t entity = 10000;
            msg >> index_component_create;
            msg >> entity;
            try {
                if (entity >= 10000)
                    return;
                registry->getNetComponentCreate().at(index_component_create)(msg);
                registry->getEntityById(entity);
                if (std::find(_tmp_entities_registry.begin(), _tmp_entities_registry.end(), registry->getEntityById(entity)) == _tmp_entities_registry.end())
                    _tmp_entities_registry.push_back(registry->getEntityById(entity));
            } catch (const ecs::Exception &e) {}
            catch (const std::out_of_range &e) {}
        } break;
        case network::CustomMessage::AllComponentSent: {
            _setRectAndSpriteComponent();
            _setTextComponent();
            _setParallax();
            _tmp_entities_registry.clear();
        } break;
        case network::CustomMessage::UpdateListRoom: {
            _setupListRoomScene(msg);
        } break;
        case network::CustomMessage::UpdatePosPlayerClient: {
            _updatePosPlayer(msg);
        } break;
        case network::CustomMessage::QuitRoomClient: {
            ecs::Scenes room_scene;
            ecs::Scenes scene_game;
            msg >> room_scene >> scene_game;
            _killEntities(room_scene);
            _killEntities(scene_game);
            is_host = false;
        } break;
        case network::CustomMessage::QuitGameClient: {
            game_scene = ecs::Scenes::RETURNTOGAME;
            msg >> tmp_scene;
        } break;
        case network::CustomMessage::SendPlanetInfo: {
            bool info;
            msg >> info;
            try {
                for (auto &it : registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMPLANETINFO))
                    registry->removeComponent<ecs::Drawable>(registry->getEntityById(it));
                for (auto &it : registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMHIGHSCORE))
                    registry->removeComponent<ecs::Drawable>(registry->getEntityById(it));
                if (info == false) {
                    registry->getComponents<ecs::Text>().at(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMHIGHSCORE).at(*current_level_id))
                    .value().setText(const_cast<char *>(std::to_string(user_info->coop_high_score.at(*current_level_id)).c_str()));
                    graphical->setTextString(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMHIGHSCORE).at(*current_level_id), std::to_string(user_info->coop_high_score.at(*current_level_id)));
                } else {
                    registry->getComponents<ecs::Text>().at(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMHIGHSCORE).at(*current_level_id))
                    .value().setText(const_cast<char *>(std::to_string(user_info->coop_high_score.at(*current_level_id)).c_str()));
                    graphical->setTextString(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMHIGHSCORE).at(*current_level_id), std::to_string(user_info->versus_high_score.at(*current_level_id)));
                }
                registry->getComponents<ecs::Text>().at(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMPLANETINFO).at(*current_level_id))
                .value().setText(const_cast<char *>(registry->getComponents<ecs::Text>().at(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMPLANETINFO).at(*current_level_id)).value().getText()));
                registry->addComponent<ecs::Drawable>(registry->getEntityById(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMPLANETINFO).at(*current_level_id)), ecs::Drawable());
                registry->addComponent<ecs::Drawable>(registry->getEntityById(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMHIGHSCORE).at(*current_level_id)), ecs::Drawable());
                graphical->setTextString(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMPLANETINFO).at(*current_level_id),
                registry->getComponents<ecs::Text>().at(registry->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMPLANETINFO).at(*current_level_id)).value().getText());
            } catch (const ecs::Exception &e) {
            } catch (const std::out_of_range &e) {}
        } break;
        case network::CustomMessage::IsHost: {
            is_host = true;
        } break;
        case network::CustomMessage::MaxRoomLimit: {
            _setErrorMessage("Max Number Of Rooms Were Already Be Created");
        } break;
        case network::CustomMessage::MaxPlayersInRoom: {
            _setErrorMessage("Max Number Of Players In This Room Reached");
        } break;
        case network::CustomMessage::RoomDoesntExists: {
            _setErrorMessage("This Room Doesn't Exists");
        } break;
        case network::CustomMessage::NotEnoughPlayer: {
            _setErrorMessage("Not Enough Player In This Room");
        } break;
        default: break;
    }
}

void CustomClient::_setupListRoomScene(network::Message<network::CustomMessage> &msg)
{
    std::size_t nb_rooms = 0;
    std::size_t tmp_nb_rooms = 0;
    ecs::Scenes room_scene;
    std::size_t entity_link_id;
    std::vector<float> rect;
    msg >> nb_rooms;
    if (non_shareable_registry->getActualScene() == ecs::Scenes::LISTROOM && *actual_scene == ecs::Scenes::LISTROOM) {
        for (auto &it : non_shareable_registry->getEntities()) {
            try {
                if (non_shareable_registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::ROOM) {
                    non_shareable_registry->removeComponent<ecs::Drawable>(it);
                    non_shareable_registry->removeComponent<ecs::CompoScene>(it);
                    entity_link_id = non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink();
                    non_shareable_registry->removeComponent<ecs::Drawable>(non_shareable_registry->getEntityById(entity_link_id));
                    non_shareable_registry->removeComponent<ecs::Text>(non_shareable_registry->getEntityById(entity_link_id));
                    non_shareable_registry->removeComponent<ecs::Drawable>(
                        non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink())
                    );
                }
            } catch (const ecs::Exception &e) {
                continue;
            }
        }
        for (auto &it : non_shareable_registry->getEntities()) {
            try {
                if (tmp_nb_rooms == nb_rooms)
                    break;
                if (non_shareable_registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::ROOM) {
                    non_shareable_registry->addComponent<ecs::Drawable>(it, ecs::Drawable());
                    msg >> room_scene;
                    non_shareable_registry->addComponent<ecs::CompoScene>(it, ecs::CompoScene(room_scene));
                    entity_link_id = non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink();
                    non_shareable_registry->addComponent<ecs::Drawable>(non_shareable_registry->getEntityById(entity_link_id), ecs::Drawable());
                    ecs::Text info_text;
                    msg >> info_text;
                    non_shareable_registry->addComponent<ecs::Text>(non_shareable_registry->getEntityById(entity_link_id), ecs::Text());
                    non_shareable_registry->getComponents<ecs::Text>().at(entity_link_id).value().setText(info_text.getText());
                    graphical->addText(entity_link_id, non_shareable_registry->getComponents<ecs::Text>().at(entity_link_id).value().getText(),
                    {non_shareable_registry->getComponents<ecs::Rectangle>().at(entity_link_id).value().getXRectangle(),
                    non_shareable_registry->getComponents<ecs::Rectangle>().at(entity_link_id).value().getYRectangle(),
                    non_shareable_registry->getComponents<ecs::Rectangle>().at(entity_link_id).value().getWidthRectangle()});
                    non_shareable_registry->addComponent<ecs::Drawable>(
                        non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()), ecs::Drawable()
                    );
                    bool roommode_id;
                    msg >> roommode_id;
                    non_shareable_registry->getComponents<ecs::Type>().at(
                        non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()
                    ).value().setEntityID(roommode_id);
                    rect = sprites_manager->get_Animations_rect(
                    non_shareable_registry->getComponents<ecs::Type>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getEntityType(),
                    non_shareable_registry->getComponents<ecs::Type>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getEntityID(), 0);

                    non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().setXRectangle(rect.at(0));
                    non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().setYRectangle(rect.at(1));
                    non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().setWidthRectangle(rect.at(2));
                    non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().setHeightRectangle(rect.at(3));
                    graphical->addSprite(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink(),
                        sprites_manager->get_Spritesheet(
                            non_shareable_registry->getComponents<ecs::Type>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getEntityType(),
                            non_shareable_registry->getComponents<ecs::Type>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getEntityID()),
                        rect
                    );
                    graphical->setSpritePosition(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink(),
                    non_shareable_registry->getComponents<ecs::Position>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getXPosition(),
                    non_shareable_registry->getComponents<ecs::Position>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getYPosition());
                    tmp_nb_rooms++;
                }

            } catch (const ecs::Exception &e) {
                continue;
            }
        }
    }
}

void CustomClient::_setRectAndSpriteComponent()
{
    std::vector<float> rect;

    for (auto &it : _tmp_entities_registry) {
        try {
            rect = sprites_manager->get_Animations_rect(
                registry->getComponents<ecs::Type>().at(it).value().getEntityType(), registry->getComponents<ecs::Type>().at(it).value().getEntityID(), 0);
            registry->getComponents<ecs::Rectangle>().at(it).value().setXRectangle(rect.at(0));
            registry->getComponents<ecs::Rectangle>().at(it).value().setYRectangle(rect.at(1));
            registry->getComponents<ecs::Rectangle>().at(it).value().setWidthRectangle(rect.at(2));
            registry->getComponents<ecs::Rectangle>().at(it).value().setHeightRectangle(rect.at(3));
            graphical->addSprite(it,
                sprites_manager->get_Spritesheet(
                    registry->getComponents<ecs::Type>().at(it).value().getEntityType(), registry->getComponents<ecs::Type>().at(it).value().getEntityID()),
                rect);
            graphical->setSpritePosition(it, registry->getComponents<ecs::Position>().at(it).value().getXPosition(), registry->getComponents<ecs::Position>().at(it).value().getYPosition());
        } catch (const ecs::Exception &e) {
            continue;
        } catch (const Exception &e) {
            continue;
        }
    }
}

void CustomClient::_setTextComponent()
{
    for (auto &it : _tmp_entities_registry) {
        try {
            graphical->addText(it, registry->getComponents<ecs::Text>().at(it).value().getText(),
            {registry->getComponents<ecs::Rectangle>().at(it).value().getXRectangle(),
            registry->getComponents<ecs::Rectangle>().at(it).value().getYRectangle(),
            registry->getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle()});
        } catch (const ecs::Exception &e) {
            continue;
        }
    }
}

void CustomClient::_setParallax()
{
    float x = 0;
    std::size_t entity_id = 0;
    for (auto &it : _tmp_entities_registry) {
        try {
            if (registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::BACKGROUND) {
                entity_id = registry->getComponents<ecs::Type>().at(it).value().getEntityID();
                x = registry->getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle();
            } else if (registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::PARALLAX
            && registry->getComponents<ecs::Type>().at(it).value().getEntityID() == entity_id)
                registry->getComponents<ecs::Position>().at(it).value().setXPosition(x);
        } catch (const ecs::Exception &e) {
            continue;
        }
    }
}

void CustomClient::_updatePosPlayer(network::Message<network::CustomMessage> &msg)
{
    ecs::Position pos;
    std::size_t entity = 10000;
    int key;
    bool pressed;
    msg >> pos >> entity >> key >> pressed;
    try {
        if (pressed == true) {
            if (key == 0) {
                registry->getComponents<ecs::Position>().at(entity).value().setYVelocity(-pos.getYVelocity());
            }
            if (key == 1) {
                registry->getComponents<ecs::Position>().at(entity).value().setXVelocity(-pos.getXVelocity());
            }
            if (key == 2) {
                registry->getComponents<ecs::Position>().at(entity).value().setYVelocity(pos.getYVelocity());
            }
            if (key == 3) {
                registry->getComponents<ecs::Position>().at(entity).value().setXVelocity(pos.getXVelocity());
            }
        } else {
            if (key == 0) {
                registry->getComponents<ecs::Position>().at(entity).value().setYVelocity(0);
            }
            if (key == 1) {
                registry->getComponents<ecs::Position>().at(entity).value().setXVelocity(0);
            }
            if (key == 2) {
                registry->getComponents<ecs::Position>().at(entity).value().setYVelocity(0);
            }
            if (key == 3) {
                registry->getComponents<ecs::Position>().at(entity).value().setXVelocity(0);
            }
        }
        graphical->setSpritePosition(entity,
        registry->getComponents<ecs::Position>().at(entity).value().getXPosition(),
        registry->getComponents<ecs::Position>().at(entity).value().getYPosition());
    } catch (const ecs::Exception &e) {}
    catch (const std::out_of_range &e) {}
}

void CustomClient::_setErrorMessage(std::string msg_error)
{
    error_msg_server = true;
    txt_error_msg_server = msg_error;
}

void CustomClient::_killEntities(ecs::Scenes scene)
{
    try {
        registry->setActualScene(scene);
        graphical->setActualGraphicsEntities(scene);
        for (auto &it : registry->getEntities())
            registry->killEntity(it);
        graphical->getAllSprites().clear();
        graphical->getAllRectangleShapes().clear();
        graphical->getAllTexts().clear();
    } catch (const ecs::Exception &e) {
        registry->setActualScene(*actual_scene);
        graphical->setActualGraphicsEntities(*actual_scene);
    }
}

void CustomClient::_killOneEntity(std::size_t entity)
{
    try {
        registry->killEntity(registry->getEntityById(entity));
        graphical->getAllSprites().erase(entity);
        graphical->getAllRectangleShapes().erase(entity);
        graphical->getAllTexts().erase(entity);
    } catch (const ecs::Exception &e) {
        registry->setActualScene(*actual_scene);
        graphical->setActualGraphicsEntities(*actual_scene);
    }
}
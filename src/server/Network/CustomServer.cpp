/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#include <filesystem>
#include <algorithm>
#include "CustomServer.hpp"
#include "../../Ecs/Component/component.hpp"
#include "../../Ecs/Factory.hpp"
#include "../Scenes/LobbySelector.hpp"
#include "../Scenes/Room.hpp"
#include "../Scenes/Game.hpp"
#include "../Utilities/ParserYaml.hpp"

CustomServer::CustomServer(boost::asio::io_context &io_context, unsigned short local_port)
    : network::UdpServerClient<network::CustomMessage>(io_context, local_port)
{
    _registries.push_back(std::make_tuple(ecs::Scenes::ROOM1, ecs::Scenes::GAME1, false, false, std::vector<std::pair<udp::endpoint, bool>>(), "", false, std::make_unique<ecs::Registry>()));
    _registries.push_back(std::make_tuple(ecs::Scenes::ROOM2, ecs::Scenes::GAME2, false, false, std::vector<std::pair<udp::endpoint, bool>>(), "", false, std::make_unique<ecs::Registry>()));
    _registries.push_back(std::make_tuple(ecs::Scenes::ROOM3, ecs::Scenes::GAME3, false, false, std::vector<std::pair<udp::endpoint, bool>>(), "", false, std::make_unique<ecs::Registry>()));

    for (std::size_t level_nb = 1; level_nb <= 5; level_nb++) {
        LevelManager level;
        ParserYaml::parseYaml(level, std::filesystem::current_path().append("src/server/levels/level-" + std::to_string(level_nb) + ".yaml").string());
        _levels.push_back(level);
    }
}

CustomServer::~CustomServer()
{
}

void CustomServer::updateSceneRoomInVectorRoom(ecs::Scenes room_scene, bool private_room, std::string player_name, udp::endpoint client_endpoint)
{
    _players_names.insert_or_assign(client_endpoint, player_name);
    _rooms_filter_mode.insert_or_assign(client_endpoint, -1);
    for (std::size_t i = 0; i < _registries.size(); i++) {
        if (std::get<0>(_registries.at(i)) == room_scene) {
            std::get<2>(_registries.at(i)) = true;
            std::get<3>(_registries.at(i)) = private_room;
            std::get<4>(_registries.at(i)).push_back(std::make_pair(client_endpoint, true));
            std::get<5>(_registries.at(i)) = _players_names.at(client_endpoint);
            return;
        }
    }
}

std::chrono::time_point<std::chrono::system_clock> CustomServer::getStartTime(ecs::Scenes scene) const
{
    return (_start_times.at(scene));
}

std::chrono::time_point<std::chrono::system_clock> CustomServer::getLastTime(ecs::Scenes scene) const
{
    return (_last_times.at(scene));
}

void CustomServer::setLastTime(ecs::Scenes scene, std::chrono::time_point<std::chrono::system_clock> new_time)
{
    _last_times.at(scene) = new_time;
}

void CustomServer::startTimes(ecs::Scenes scene)
{
    _start_times.insert_or_assign(scene, std::chrono::system_clock::now());
    _last_times.insert_or_assign(scene, _start_times.at(scene));
}

void CustomServer::onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    switch (msg.header.id) {
        case network::CustomMessage::PingServer: {
            _rooms_filter_mode.insert_or_assign(target_endpoint, -1);
            std::cout << "["
                      << "connection..."
                      << "]: Server Ping" << std::endl;
        } break;
        case network::CustomMessage::SwitchToGame: {
            ecs::Scenes client_scene;
            msg >> client_scene;
            _createGame(client_scene, target_endpoint);
        } break;
        case network::CustomMessage::InitGame: {
            ecs::Scenes game_scene;
            msg >> game_scene;
            _getGame(game_scene, target_endpoint);
        } break;
        case network::CustomMessage::CreatePublicRoom: {
            _createRoom(msg, target_endpoint);
        } break;
        case network::CustomMessage::CreatePrivateRoom: {
            _createRoom(msg, target_endpoint, true);
        } break;
        case network::CustomMessage::CreateShot: {
            _createShot(msg);
        } break;
        case network::CustomMessage::InitListRoom: {
            std::scoped_lock guard(_mtx);
            int room_filter_mode;
            msg >> room_filter_mode;
            _rooms_filter_mode.insert_or_assign(target_endpoint, room_filter_mode);
            network::Message<network::CustomMessage> message;
            _getInfoForListRoomScene(target_endpoint, message);
            send(message, target_endpoint);
        } break;
        case network::CustomMessage::JoinRoom: {
            _joinRoom(target_endpoint, msg);
        } break;
        case network::CustomMessage::JoinRoomById: {
            _joinRoomById(target_endpoint, msg);
        } break;
        case network::CustomMessage::QuitRoomServer: {
            _quitRoom(target_endpoint);
        } break;
        case network::CustomMessage::SwitchRoomMode: {
            _updateRoom(target_endpoint, msg);
        } break;
        case network::CustomMessage::RemoveClient: {
            _quitRoom(target_endpoint);
            _rooms_filter_mode.erase(target_endpoint);
            _players_names.erase(target_endpoint);
            for (std::size_t i = 0; i < _clients_endpoint.size(); i++) {
                if (_clients_endpoint.at(i) == target_endpoint)
                    _clients_endpoint.erase(std::next(_clients_endpoint.begin(), i));
            }
            std::cout << "["
                      << "disconnected..."
                      << "]: Client Remove" << std::endl;
        } break;
        default:
            break;
    }
}

void CustomServer::_createGame(ecs::Scenes room_scene, udp::endpoint target_endpoint)
{
    network::Message<network::CustomMessage> message;
    message.header.id = network::CustomMessage::GetScene;
    for (std::size_t i = 0; i < _registries.size(); i++) {
        if (std::get<0>(_registries.at(i)) == room_scene) {
            std::scoped_lock guard(_mtx);
            for (std::size_t j = 0; j < std::get<4>(_registries.at(i)).size(); j++) {
                if (std::get<4>(_registries.at(i)).at(j).first == target_endpoint && std::get<4>(_registries.at(i)).at(j).second != true)
                    return;
            }
            // if (std::get<4>(_registries.at(i)).size() < 2) {
            //     network::Message<network::CustomMessage> message2;
            //     message2.header.id = network::CustomMessage::NotEnoughPlayer;
            //     send(message2, target_endpoint);
            //     return;
            // }
            Game::initScene(this, *std::get<7>(_registries.at(i)), std::get<1>(_registries.at(i)), std::get<4>(_registries.at(i)), _levels.at(0));
            message << std::get<1>(_registries.at(i));
            for (auto &client_endpoint : std::get<4>(_registries.at(i))) {
                send(message, client_endpoint.first);
                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
            }
            return;
        }
    }
}

void CustomServer::_getGame(ecs::Scenes game_scene, udp::endpoint target_endpoint)
{
    for (std::size_t i = 0; i < _registries.size(); i++) {
        if (std::get<1>(_registries.at(i)) == game_scene) {
            _mtx.lock();
            Game::getScene(this, *std::get<7>(_registries.at(i)), std::get<1>(_registries.at(i)), std::get<4>(_registries.at(i)), target_endpoint);
            _mtx.unlock();
            for (auto &client_endpoint : std::get<4>(_registries.at(i))) {
                if (client_endpoint.first == target_endpoint && client_endpoint.second == true) {
                    Game::updateScene(this, *std::get<7>(_registries.at(i)), std::get<1>(_registries.at(i)), std::get<4>(_registries.at(i)));
                    break;
                }
            }
            return;
        }
    }
}

void CustomServer::_createShot(network::Message<network::CustomMessage> &msg)
{
    std::scoped_lock guard(_mtx);
    std::size_t entity;
    std::size_t linked_entity;
    ecs::Scenes scene;
    msg >> scene >> linked_entity;

    std::cout << "scene: " << scene << ", spaceship: " << linked_entity << std::endl;
    std::cout << "registry scene: " << static_cast<int>(_getGameRegistry(scene).getActualScene()) << std::endl;
    try {
        ecs::Ammo::AmmoType ammoType = _getGameRegistry(scene).getComponents<ecs::Shooter>().at(linked_entity).value().getAmmoType();
        float posX = _getGameRegistry(scene).getComponents<ecs::Position>().at(linked_entity).value().getXPosition() + _getGameRegistry(scene).getComponents<ecs::Rectangle>().at(linked_entity).value().getWidthRectangle()/2;
        float posY = _getGameRegistry(scene).getComponents<ecs::Position>().at(linked_entity).value().getYPosition() + _getGameRegistry(scene).getComponents<ecs::Rectangle>().at(linked_entity).value().getHeightRectangle()/2;
        int layer = _getGameRegistry(scene).getComponents<ecs::Layer>().at(linked_entity).value().getLayer() - 1;
        entity = ecs::Factory::createEntity(_getGameRegistry(scene), ecs::EntityTypes::SHOT, linked_entity, posX, posY, 0, 0, 0, 0, layer, static_cast<int>(ammoType));
        _getGameRegistry(scene).addComponent<ecs::CompoServer>(_getGameRegistry(scene).getEntityById(entity), ecs::CompoServer());
        for (auto &client_endpoint : _getClientsEndpoint(scene)) {
            sendNetworkComponents<network::CustomMessage>(_getGameRegistry(scene), entity, network::CustomMessage::SendComponent, client_endpoint.first);
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::AllComponentSent;
            send(message, client_endpoint.first);
            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
        }
    } catch (ecs::ExceptionComponentNull &e) {
        return;
    } catch (ecs::ExceptionIndexComponent &e) {
        return;
    }
}

void CustomServer::_createRoom(network::Message<network::CustomMessage> &msg, udp::endpoint target_endpoint, bool private_room)
{
    std::scoped_lock guard(_mtx);
    ecs::Text player_name_class;
    std::string player_name;
    msg >> player_name_class;
    player_name = player_name_class.getText();
    for (std::size_t i = 0; i < _registries.size(); i++) {
        if (std::get<2>(_registries.at(i)) == false) {
            Room::initScene(this, *std::get<7>(_registries.at(i)), std::get<0>(_registries.at(i)), target_endpoint, private_room, player_name);
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::AllComponentSent;
            send(message, target_endpoint);
            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
            network::Message<network::CustomMessage> message2;
            for (std::size_t j = 0; j < _clients_endpoint.size(); j++) {
                _getInfoForListRoomScene(_clients_endpoint.at(j), message2);
                send(message2, _clients_endpoint.at(j));
            }
            return;
        }
    }
    network::Message<network::CustomMessage> error_message;
    error_message.header.id = network::CustomMessage::MaxRoomLimit;
    send(error_message, target_endpoint);
}

void CustomServer::_getInfoForListRoomScene(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &message)
{
    message.header.id = network::CustomMessage::UpdateListRoom;
    std::size_t nb_rooms = 0;
    std::string rooms_text;
    for (int i = _registries.size() - 1; i >= 0; i--) {
        if (std::get<2>(_registries.at(i)) == true && std::get<3>(_registries.at(i)) == false) {
            if (_rooms_filter_mode.at(target_endpoint) == 0 && std::get<6>(_registries.at(i)) == false) {
                message << std::get<6>(_registries.at(i));
                rooms_text = std::get<5>(_registries.at(i)) + "         " + std::to_string(std::get<4>(_registries.at(i)).size()) + "/" + std::to_string(NB_MAX_PLAYERS_PER_ROOM);
                ecs::Text player_name_class(const_cast<char *>(rooms_text.c_str()));
                message << player_name_class;
                message << std::get<0>(_registries.at(i));
                nb_rooms++;
            } else if (_rooms_filter_mode.at(target_endpoint) == 1 && std::get<6>(_registries.at(i)) == true) {
                message << std::get<6>(_registries.at(i));
                rooms_text = std::get<5>(_registries.at(i)) + "         " + std::to_string(std::get<4>(_registries.at(i)).size()) + "/" + std::to_string(NB_MAX_PLAYERS_PER_ROOM);
                ecs::Text player_name_class(const_cast<char *>(rooms_text.c_str()));
                message << player_name_class;
                message << std::get<0>(_registries.at(i));
                nb_rooms++;
            } else if (_rooms_filter_mode.at(target_endpoint) == -1)  {
                message << std::get<6>(_registries.at(i));
                rooms_text = std::get<5>(_registries.at(i)) + "         " + std::to_string(std::get<4>(_registries.at(i)).size()) + "/" + std::to_string(NB_MAX_PLAYERS_PER_ROOM);
                ecs::Text player_name_class(const_cast<char *>(rooms_text.c_str()));
                message << player_name_class;
                message << std::get<0>(_registries.at(i));
                nb_rooms++;
            }
        }
    }
    message << nb_rooms;
}

void CustomServer::_joinRoom(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    std::scoped_lock guard(_mtx);
    ecs::Scenes room_scene;
    ecs::Text player_name_class;
    std::string player_name;
    msg >> room_scene;
    msg >> player_name_class;
    player_name = player_name_class.getText();
    for (std::size_t i = 0; i < _registries.size(); i++) {
        if (std::get<0>(_registries.at(i)) == room_scene && std::get<4>(_registries.at(i)).size() == NB_MAX_PLAYERS_PER_ROOM) {
            network::Message<network::CustomMessage> error_message;
            error_message.header.id = network::CustomMessage::MaxPlayersInRoom;
            send(error_message, target_endpoint);
            return;
        } else if (std::get<0>(_registries.at(i)) == room_scene) {
            std::get<4>(_registries.at(i)).push_back(std::make_pair(target_endpoint, false));
            _players_names.insert_or_assign(target_endpoint, player_name);
            _rooms_filter_mode.insert_or_assign(target_endpoint, -1);
            std::get<7>(_registries.at(i))->setActualScene(room_scene);
            for (auto &it : std::get<7>(_registries.at(i))->getEntities()) {
                try {
                    if (std::get<7>(_registries.at(i))->getComponents<ecs::Clickable>().at(it).value().getFunction() == ecs::Clickable::Function::TOGAME) {
                        std::get<7>(_registries.at(i))->removeComponent<ecs::Clickable>(it);
                        sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it, network::CustomMessage::SendComponent, target_endpoint);
                        std::get<7>(_registries.at(i))->addComponent<ecs::Clickable>(it, ecs::Clickable(ecs::Clickable::Function::TOGAME));
                    } else
                        sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it, network::CustomMessage::SendComponent, target_endpoint);
                } catch (const ecs::ExceptionIndexComponent &e) {
                    sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it, network::CustomMessage::SendComponent, target_endpoint);
                    continue;
                } catch (const ecs::ExceptionComponentNull &e) {
                    sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it, network::CustomMessage::SendComponent, target_endpoint);
                    continue;
                }
            }
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::AllComponentSent;
            send(message, target_endpoint);
            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
            network::Message<network::CustomMessage> message2;
            for (std::size_t j = 0; j < _clients_endpoint.size(); j++) {
                _getInfoForListRoomScene(_clients_endpoint.at(j), message2);
                send(message2, _clients_endpoint.at(j));
            }
            return;
        }
    }
}

void CustomServer::_joinRoomById(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    int id_room = 0;
    ecs::Text player_name_class;
    std::string player_name;
    msg >> id_room;
    msg >> player_name_class;
    player_name = player_name_class.getText();
    std::string room_id;
    for (std::size_t i = 0; i < _registries.size(); i++) {
        if (std::get<2>(_registries.at(i)) == true) {
            std::scoped_lock guard(_mtx);
            std::get<7>(_registries.at(i))->setActualScene(std::get<0>(_registries.at(i)));
            for (auto &it : std::get<7>(_registries.at(i))->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMID)) {
                room_id = std::get<7>(_registries.at(i))->getComponents<ecs::Text>().at(it).value().getText();
                if (room_id.substr(9) == std::to_string(id_room)) {
                    if (std::get<4>(_registries.at(i)).size() == NB_MAX_PLAYERS_PER_ROOM) {
                        network::Message<network::CustomMessage> error_message;
                        error_message.header.id = network::CustomMessage::MaxPlayersInRoom;
                        send(error_message, target_endpoint);
                        return;
                    }
                    std::get<4>(_registries.at(i)).push_back(std::make_pair(target_endpoint, false));
                    _players_names.insert_or_assign(target_endpoint, player_name);
                    _rooms_filter_mode.insert_or_assign(target_endpoint, -1);
                    network::Message<network::CustomMessage> message;
                    message.header.id = network::CustomMessage::GetScene;
                    message << std::get<0>(_registries.at(i));
                    send(message, target_endpoint);
                    std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
                    for (auto &it2 : std::get<7>(_registries.at(i))->getEntities()) {
                        try {
                            if (std::get<7>(_registries.at(i))->getComponents<ecs::Clickable>().at(it2).value().getFunction() == ecs::Clickable::Function::TOGAME) {
                                std::get<7>(_registries.at(i))->removeComponent<ecs::Clickable>(it2);
                                sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it2, network::CustomMessage::SendComponent, target_endpoint);
                                std::get<7>(_registries.at(i))->addComponent<ecs::Clickable>(it2, ecs::Clickable(ecs::Clickable::Function::TOGAME));
                            } else
                                sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it2, network::CustomMessage::SendComponent, target_endpoint);
                        } catch (const ecs::ExceptionIndexComponent &e) {
                            sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it2, network::CustomMessage::SendComponent, target_endpoint);
                            continue;
                        } catch (const ecs::ExceptionComponentNull &e) {
                            sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it2, network::CustomMessage::SendComponent, target_endpoint);
                            continue;
                        }
                    }
                    network::Message<network::CustomMessage> message2;
                    message2.header.id = network::CustomMessage::AllComponentSent;
                    send(message2, target_endpoint);
                    std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
                    if (std::get<3>(_registries.at(i)) == false) {
                        network::Message<network::CustomMessage> message3;
                        for (std::size_t j = 0; j < _clients_endpoint.size(); j++) {
                            _getInfoForListRoomScene(_clients_endpoint.at(j), message3);
                            send(message3, _clients_endpoint.at(j));
                        }
                    }
                    return;
                }
            }
        }
    }
    network::Message<network::CustomMessage> message4;
    message4.header.id = network::CustomMessage::RoomDoesntExists;
    send(message4, target_endpoint);
}

void CustomServer::_updateRoom(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    for (std::size_t i = 0; i < _registries.size(); i++) {
        for (std::size_t j = 0; j < std::get<4>(_registries.at(i)).size(); j++) {
            if (std::get<4>(_registries.at(i)).at(j).first == target_endpoint && std::get<4>(_registries.at(i)).at(j).second == true) {
                _mtx.lock();
                ecs::Registry tmp_registry = *std::get<7>(_registries.at(i));
                std::get<7>(_registries.at(i))->setActualScene(std::get<0>(_registries.at(i)));
                switch (msg.header.id)
                {
                    case network::CustomMessage::SwitchRoomMode: {
                        if (std::get<6>(_registries.at(i))) {
                            std::get<6>(_registries.at(i)) = false;
                            for (auto &it : std::get<7>(_registries.at(i))->getEntitiesIdByEcsType(ecs::EntityTypes::BUTTON)) {
                                if (std::get<7>(_registries.at(i))->getComponents<ecs::Type>().at(it).value().getEntityID() == 13)
                                    std::get<7>(_registries.at(i))->addComponent<ecs::Drawable>(std::get<7>(_registries.at(i))->getEntityById(it), ecs::Drawable());
                                if (std::get<7>(_registries.at(i))->getComponents<ecs::Type>().at(it).value().getEntityID() == 14) {
                                    std::get<7>(_registries.at(i))->removeComponent<ecs::Drawable>(std::get<7>(_registries.at(i))->getEntityById(it));
                                    break;
                                }
                            }
                        } else {
                            std::get<6>(_registries.at(i)) = true;
                            for (auto &it : std::get<7>(_registries.at(i))->getEntitiesIdByEcsType(ecs::EntityTypes::BUTTON)) {
                                if (std::get<7>(_registries.at(i))->getComponents<ecs::Type>().at(it).value().getEntityID() == 13)
                                    std::get<7>(_registries.at(i))->removeComponent<ecs::Drawable>(std::get<7>(_registries.at(i))->getEntityById(it));
                                if (std::get<7>(_registries.at(i))->getComponents<ecs::Type>().at(it).value().getEntityID() == 14) {
                                    std::get<7>(_registries.at(i))->addComponent<ecs::Drawable>(std::get<7>(_registries.at(i))->getEntityById(it), ecs::Drawable());
                                    break;
                                }
                            }
                        }
                        for (auto &it : std::get<7>(_registries.at(i))->getEntitiesIdByEcsType(ecs::EntityTypes::ROOMMODE)) {
                            std::get<7>(_registries.at(i))->getComponents<ecs::Type>().at(it).value().setEntityID(static_cast<std::size_t>(std::get<6>(_registries.at(i))));
                            break;
                        }
                        network::Message<network::CustomMessage> message;
                        for (std::size_t g = 0; g < _clients_endpoint.size(); g++) {
                            _getInfoForListRoomScene(_clients_endpoint.at(g), message);
                            send(message, _clients_endpoint.at(g));
                        }
                    } break;
                    default:
                        break;
                }
                _mtx.unlock();
                for (std::size_t g = 0; g < std::get<4>(_registries.at(i)).size(); g++)
                    compareRegistries(std::get<4>(_registries.at(i)).at(g).first, *std::get<7>(_registries.at(i)), tmp_registry);
                return;
            }
        }
    }
}

void CustomServer::_quitRoom(udp::endpoint target_endpoint)
{
    for (std::size_t i = 0; i < _registries.size(); i++) {
        for (std::size_t j = 0; j < std::get<4>(_registries.at(i)).size(); j++) {
            if (std::get<4>(_registries.at(i)).at(j).first == target_endpoint) {
                std::scoped_lock guard(_mtx);
                if (std::get<4>(_registries.at(i)).at(j).second == true && std::get<4>(_registries.at(i)).size() > 1) {
                    try {
                        std::get<4>(_registries.at(i)).at(j+1).second = true;
                        std::get<5>(_registries.at(i)) = _players_names.at(std::get<4>(_registries.at(i)).at(j+1).first);
                        for (auto &it : std::get<7>(_registries.at(i))->getEntitiesIdByEcsType(ecs::EntityTypes::BUTTON)) {
                            if (std::get<7>(_registries.at(i))->getComponents<ecs::Clickable>().at(it).value().getFunction() == ecs::Clickable::Function::TOGAME) {
                                sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it, network::CustomMessage::SendComponent, std::get<4>(_registries.at(i)).at(j+1).first);
                                break;
                            }
                        }
                    } catch (const std::out_of_range &e) {
                        std::get<4>(_registries.at(i)).at(j-1).second = true;
                        std::get<5>(_registries.at(i)) = _players_names.at(std::get<4>(_registries.at(i)).at(j-1).first);
                        for (auto &it : std::get<7>(_registries.at(i))->getEntitiesIdByEcsType(ecs::EntityTypes::BUTTON)) {
                            if (std::get<7>(_registries.at(i))->getComponents<ecs::Clickable>().at(it).value().getFunction() == ecs::Clickable::Function::TOGAME) {
                                sendNetworkComponents<network::CustomMessage>(*std::get<7>(_registries.at(i)), it, network::CustomMessage::SendComponent, std::get<4>(_registries.at(i)).at(j-1).first);
                                break;
                            }
                        }
                    }
                }
                network::Message<network::CustomMessage> message;
                message.header.id = network::CustomMessage::QuitRoomClient;
                message << std::get<0>(_registries.at(i));
                send(message, std::get<4>(_registries.at(i)).at(j).first);
                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
                std::get<4>(_registries.at(i)).erase(std::next(std::get<4>(_registries.at(i)).begin(), j));
                std::get<6>(_registries.at(i)) = false;
                _rooms_filter_mode.insert_or_assign(target_endpoint, -1);
                if (std::get<4>(_registries.at(i)).size() == 0) {
                    std::get<2>(_registries.at(i)) = false;
                    std::get<7>(_registries.at(i))->setActualScene(std::get<0>(_registries.at(i)));
                    for (auto &it : std::get<7>(_registries.at(i))->getEntities())
                        std::get<7>(_registries.at(i))->killEntity(it);
                }
                network::Message<network::CustomMessage> message2;
                for (std::size_t g = 0; g < _clients_endpoint.size(); g++) {
                    _getInfoForListRoomScene(_clients_endpoint.at(g), message2);
                    send(message2, _clients_endpoint.at(g));
                }
                return;
            }
        }
    }
}

void CustomServer::compareRegistries(udp::endpoint target_endpoint, ecs::Registry &registry, ecs::Registry &tmp_registry)
{
    std::scoped_lock guard(_mtx);
    bool update = false;
    std::vector<std::size_t> tmp_entities;
    for (auto &it : registry.getEntities()) {
        for (std::size_t i = 0; i < registry.getComponentsFind().size(); i++) {
            if (registry.getComponentsFind().at(i)(registry, it)
            != tmp_registry.getComponentsFind().at(i)(tmp_registry, it)) {
                tmp_entities.push_back(it);
                break;
            }
        }
        if (std::find(tmp_entities.begin(), tmp_entities.end(), it) != tmp_entities.end()) {
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::KillAnEntity;
            message << static_cast<std::size_t>(it);
            send(message, target_endpoint);
            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
            sendNetworkComponents<network::CustomMessage>(registry, it, network::CustomMessage::SendComponent, target_endpoint);
            update = true;
        }
    }
    for (auto &it : registry.getEntities()) {
        for (std::size_t i = 0; i < registry.getComponentsCompare().size(); i++) {
            try {
                if (registry.getComponentsCompare().at(i)(tmp_registry, it)
                != tmp_registry.getComponentsCompare().at(i)(registry, it)
                && std::find(tmp_entities.begin(), tmp_entities.end(), it) == tmp_entities.end()) {
                    sendNetworkComponent<network::CustomMessage>(registry, it, network::CustomMessage::SendComponent, target_endpoint, i);
                    update = true;
                }
            } catch (const ecs::ExceptionComponentNull &e) {
                continue;
            } catch (const ecs::ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    if (update == true) {
        network::Message<network::CustomMessage> message2;
        message2.header.id = network::CustomMessage::AllComponentSent;
        send(message2, target_endpoint);
        std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
    }
}

ecs::Registry &CustomServer::_getGameRegistry(ecs::Scenes scene)
{
    for (std::size_t i = 0; i < _registries.size(); i++) {
        if (std::get<1>(_registries.at(i)) == scene)
            return (*std::get<7>(_registries.at(i)));
    }
    return (*std::get<7>(_registries.at(0)));
}

std::vector<std::pair<udp::endpoint, bool>> &CustomServer::_getClientsEndpoint(ecs::Scenes scene)
{
    for (std::size_t i = 0; i < _registries.size(); i++) {
        if (std::get<1>(_registries.at(i)) == scene)
            return (std::get<4>(_registries.at(i)));
    }
    return (std::get<4>(_registries.at(0)));
}

/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#include "CustomServer.hpp"
#include "../../Ecs/Component/component.hpp"
#include "../../Ecs/Factory.hpp"
#include "../Scenes/LobbySelector.hpp"
#include "../Scenes/Room.hpp"

CustomServer::CustomServer(boost::asio::io_context &io_context, unsigned short local_port)
    : network::UdpServerClient<network::CustomMessage>(io_context, local_port)
{
    _rooms.push_back(std::make_tuple(ecs::Scenes::ROOM1, false, false, std::vector<std::pair<udp::endpoint, bool>>(), "", false));
    _rooms.push_back(std::make_tuple(ecs::Scenes::ROOM2, false, false, std::vector<std::pair<udp::endpoint, bool>>(), "", false));
    _rooms.push_back(std::make_tuple(ecs::Scenes::ROOM3, false, false, std::vector<std::pair<udp::endpoint, bool>>(), "", false));
    _rooms.push_back(std::make_tuple(ecs::Scenes::ROOM4, false, false, std::vector<std::pair<udp::endpoint, bool>>(), "", false));
}

CustomServer::~CustomServer()
{
}

void CustomServer::updateSceneRoomInVectorRoom(ecs::Scenes room_scene, bool private_room, std::string player_name, udp::endpoint client_endpoint)
{
    _players_names.insert_or_assign(client_endpoint, player_name);
    _rooms_filter_mode.insert_or_assign(client_endpoint, -1);
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        if (std::get<0>(_rooms.at(i)) == room_scene) {
            std::get<1>(_rooms.at(i)) = true;
            std::get<2>(_rooms.at(i)) = private_room;
            std::get<3>(_rooms.at(i)).push_back(std::make_pair(client_endpoint, true));
            std::get<4>(_rooms.at(i)) = _players_names.at(client_endpoint);
            return;
        }
    }
}

void CustomServer::onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    switch (msg.header.id) {
        case network::CustomMessage::PingServer: {
            std::cout << "["
                      << "connection..."
                      << "]: Server Ping" << std::endl;
        } break;
        case network::CustomMessage::SwitchToGame: {
            LobbySelector::initScene(this, _registry, target_endpoint);
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::AllComponentSent;
            sendToAllClients(message);
        } break;
        case network::CustomMessage::CreatePublicRoom: {
            std::cout << "a" << std::endl;
            _createRoom(msg, target_endpoint);
            std::cout << "b" << std::endl;
        } break;
        case network::CustomMessage::CreatePrivateRoom: {
            _createRoom(msg, target_endpoint, true);
        } break;
        case network::CustomMessage::InitListRoom: {
            std::cout << "1" << std::endl;
            int room_filter_mode;
            msg >> room_filter_mode;
            _rooms_filter_mode.insert_or_assign(target_endpoint, room_filter_mode);
            network::Message<network::CustomMessage> message;
            _getInfoForListRoomScene(target_endpoint, message);
            send(message, target_endpoint);
            std::cout << "2" << std::endl;
        } break;
        case network::CustomMessage::JoinRoom: {
            std::cout << "c" << std::endl;
            _joinRoom(target_endpoint, msg);
            std::cout << "d" << std::endl;
        } break;
        case network::CustomMessage::JoinRoomById: {
            _joinRoomById(target_endpoint, msg);
        } break;
        case network::CustomMessage::QuitRoomServer: {
            std::cout << "e" << std::endl;
            _quitRoom(target_endpoint);
            std::cout << "f" << std::endl;
        } break;
        case network::CustomMessage::SwitchRoomMode: {
            std::cout << "g" << std::endl;
            _updateRoom(target_endpoint, msg);
            std::cout << "h" << std::endl;
        } break;
        case network::CustomMessage::RemoveClient: {
            std::cout << "i" << std::endl;
            _quitRoom(target_endpoint);
            std::cout << "j" << std::endl;
            //CHANGE THESE BECAUSE IT DOESN'T DECOONECT OTHERWISE OR STD::OUT_OF_RANGE
            // for (auto it = _rooms_filter_mode.begin(); it != _rooms_filter_mode.end();) {
            //     if (it->first == target_endpoint)
            //         _rooms_filter_mode.erase(it);
            // }
            // for (auto it = _players_names.begin(); it != _players_names.end();) {
            //     if (it->first == target_endpoint)
            //         _players_names.erase(it);
            // }
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

void CustomServer::_createRoom(network::Message<network::CustomMessage> &msg, udp::endpoint target_endpoint, bool private_room)
{
    ecs::Text player_name_class;
    std::string player_name;
    msg >> player_name_class;
    player_name = player_name_class.getText();
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        if (std::get<1>(_rooms.at(i)) == false) {
            Room::initScene(this, _registry, std::get<0>(_rooms.at(i)), target_endpoint, private_room, player_name);
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
    for (int i = _rooms.size() - 1; i >= 0; i--) {
        if (std::get<1>(_rooms.at(i)) == true && std::get<2>(_rooms.at(i)) == false) {
            if (_rooms_filter_mode.at(target_endpoint) == 0 && std::get<5>(_rooms.at(i)) == false) {
                message << std::get<5>(_rooms.at(i));
                rooms_text = std::get<4>(_rooms.at(i)) + "         " + std::to_string(std::get<3>(_rooms.at(i)).size()) + "/" + std::to_string(NB_MAX_PLAYERS_PER_ROOM);
                ecs::Text player_name_class(const_cast<char *>(rooms_text.c_str()));
                message << player_name_class;
                message << std::get<0>(_rooms.at(i));
                nb_rooms++;
            } else if (_rooms_filter_mode.at(target_endpoint) == 1 && std::get<5>(_rooms.at(i)) == true) {
                message << std::get<5>(_rooms.at(i));
                rooms_text = std::get<4>(_rooms.at(i)) + "         " + std::to_string(std::get<3>(_rooms.at(i)).size()) + "/" + std::to_string(NB_MAX_PLAYERS_PER_ROOM);
                ecs::Text player_name_class(const_cast<char *>(rooms_text.c_str()));
                message << player_name_class;
                message << std::get<0>(_rooms.at(i));
                nb_rooms++;
            } else if (_rooms_filter_mode.at(target_endpoint) == -1)  {
                message << std::get<5>(_rooms.at(i));
                rooms_text = std::get<4>(_rooms.at(i)) + "         " + std::to_string(std::get<3>(_rooms.at(i)).size()) + "/" + std::to_string(NB_MAX_PLAYERS_PER_ROOM);
                ecs::Text player_name_class(const_cast<char *>(rooms_text.c_str()));
                message << player_name_class;
                message << std::get<0>(_rooms.at(i));
                nb_rooms++;
            }
        }
    }
    message << nb_rooms;
}

void CustomServer::_joinRoom(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    ecs::Scenes room_scene;
    ecs::Text player_name_class;
    std::string player_name;
    msg >> room_scene;
    msg >> player_name_class;
    player_name = player_name_class.getText();
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        if (std::get<0>(_rooms.at(i)) == room_scene && std::get<3>(_rooms.at(i)).size() == NB_MAX_PLAYERS_PER_ROOM) {
            network::Message<network::CustomMessage> error_message;
            error_message.header.id = network::CustomMessage::MaxPlayersInRoom;
            send(error_message, target_endpoint);
            return;
        } else if (std::get<0>(_rooms.at(i)) == room_scene) {
            std::get<3>(_rooms.at(i)).push_back(std::make_pair(target_endpoint, false));
            _players_names.insert_or_assign(target_endpoint, player_name);
            _rooms_filter_mode.insert_or_assign(target_endpoint, -1);
            _registry.setActualScene(room_scene);
            for (auto &it : _registry.getEntities())
                sendNetworkComponents(it, network::CustomMessage::SendComponent, target_endpoint);
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
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        if (std::get<1>(_rooms.at(i)) == true) {
            _registry.setActualScene(std::get<0>(_rooms.at(i)));
            for (auto &it : _registry.getEntitiesIdByEcsType(ecs::EntityTypes::ROOMID)) {
                room_id = _registry.getComponents<ecs::Text>().at(it).value().getText();
                if (room_id.substr(9) == std::to_string(id_room)) {
                    if (std::get<3>(_rooms.at(i)).size() == NB_MAX_PLAYERS_PER_ROOM) {
                        network::Message<network::CustomMessage> error_message;
                        error_message.header.id = network::CustomMessage::MaxPlayersInRoom;
                        send(error_message, target_endpoint);
                        return;
                    }
                    std::get<3>(_rooms.at(i)).push_back(std::make_pair(target_endpoint, false));
                    _players_names.insert_or_assign(target_endpoint, player_name);
                    _rooms_filter_mode.insert_or_assign(target_endpoint, -1);
                    network::Message<network::CustomMessage> message;
                    message.header.id = network::CustomMessage::GetRoomScene;
                    message << std::get<0>(_rooms.at(i));
                    send(message, target_endpoint);
                    std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
                    for (auto &it2 : _registry.getEntities())
                        sendNetworkComponents(it2, network::CustomMessage::SendComponent, target_endpoint);
                    network::Message<network::CustomMessage> message2;
                    message2.header.id = network::CustomMessage::AllComponentSent;
                    send(message2, target_endpoint);
                    std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
                    if (std::get<2>(_rooms.at(i)) == false) {
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
    ecs::Registry tmp_registry = _registry;
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        for (std::size_t j = 0; j < std::get<3>(_rooms.at(i)).size(); j++) {
            if (std::get<3>(_rooms.at(i)).at(j).first == target_endpoint) {
                _registry.setActualScene(std::get<0>(_rooms.at(i)));
                switch (msg.header.id)
                {
                    case network::CustomMessage::SwitchRoomMode: {
                        if (std::get<5>(_rooms.at(i))) {
                            std::get<5>(_rooms.at(i)) = false;
                            for (auto &it : _registry.getEntitiesIdByEcsType(ecs::EntityTypes::BUTTON)) {
                                if (_registry.getComponents<ecs::Type>().at(it).value().getEntityID() == 13)
                                    _registry.addComponent<ecs::Drawable>(_registry.getEntityById(it), ecs::Drawable());
                                if (_registry.getComponents<ecs::Type>().at(it).value().getEntityID() == 14) {
                                    _registry.removeComponent<ecs::Drawable>(_registry.getEntityById(it));
                                    break;
                                }
                            }
                        } else {
                            std::get<5>(_rooms.at(i)) = true;
                            for (auto &it : _registry.getEntitiesIdByEcsType(ecs::EntityTypes::BUTTON)) {
                                if (_registry.getComponents<ecs::Type>().at(it).value().getEntityID() == 13)
                                    _registry.removeComponent<ecs::Drawable>(_registry.getEntityById(it));
                                if (_registry.getComponents<ecs::Type>().at(it).value().getEntityID() == 14) {
                                    _registry.addComponent<ecs::Drawable>(_registry.getEntityById(it), ecs::Drawable());
                                    break;
                                }
                            }
                        }
                        for (auto &it : _registry.getEntitiesIdByEcsType(ecs::EntityTypes::ROOMMODE)) {
                            _registry.getComponents<ecs::Type>().at(it).value().setEntityID(static_cast<std::size_t>(std::get<5>(_rooms.at(i))));
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
                for (std::size_t g = 0; g < std::get<3>(_rooms.at(i)).size(); g++)
                    _compareRegistries(std::get<3>(_rooms.at(i)).at(g).first, tmp_registry);
                return;
            }
        }
    }
}

void CustomServer::_quitRoom(udp::endpoint target_endpoint)
{
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        for (std::size_t j = 0; j < std::get<3>(_rooms.at(i)).size(); j++) {
            if (std::get<3>(_rooms.at(i)).at(j).first == target_endpoint) {
                if (std::get<3>(_rooms.at(i)).at(j).second == true && std::get<3>(_rooms.at(i)).size() > 1) {
                    try {
                        std::get<3>(_rooms.at(i)).at(j+1).second = true;
                        std::get<4>(_rooms.at(i)) = _players_names.at(std::get<3>(_rooms.at(i)).at(j+1).first);
                    } catch (const std::out_of_range &e) {
                        std::get<3>(_rooms.at(i)).at(j-1).second = true;
                        std::get<4>(_rooms.at(i)) = _players_names.at(std::get<3>(_rooms.at(i)).at(j-1).first);
                    }
                }
                network::Message<network::CustomMessage> message;
                message.header.id = network::CustomMessage::QuitRoomClient;
                message << std::get<0>(_rooms.at(i));
                send(message, std::get<3>(_rooms.at(i)).at(j).first);
                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
                std::get<3>(_rooms.at(i)).erase(std::next(std::get<3>(_rooms.at(i)).begin(), j));
                std::get<5>(_rooms.at(i)) = false;
                _rooms_filter_mode.insert_or_assign(target_endpoint, -1);
                if (std::get<3>(_rooms.at(i)).size() == 0) {
                    std::get<1>(_rooms.at(i)) = false;
                    _registry.setActualScene(std::get<0>(_rooms.at(i)));
                    for (auto &it : _registry.getEntities())
                        _registry.killEntity(it);
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

void CustomServer::_compareRegistries(udp::endpoint target_endpoint, ecs::Registry &tmp_registry)
{
    for (auto &it : _registry.getEntities()) {
        for (std::size_t i = 0; i < _registry.getComponentCompare().size(); i++) {
            try {
                if (!_registry.getComponentCompare().at(i)(it, tmp_registry))
                    sendNetworkComponent<network::CustomMessage>(it, network::CustomMessage::SendComponent, target_endpoint, i);
            } catch (const ecs::ExceptionComponentNull &e) {
                continue;
            } catch (const ecs::ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    network::Message<network::CustomMessage> message;
    message.header.id = network::CustomMessage::AllComponentSent;
    send(message, target_endpoint);
}
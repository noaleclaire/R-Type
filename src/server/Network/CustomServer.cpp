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
    _rooms.push_back(std::make_tuple(ecs::Scenes::ROOM1, false, false, std::vector<std::pair<udp::endpoint, bool>>(), ""));
    _rooms.push_back(std::make_tuple(ecs::Scenes::ROOM2, false, false, std::vector<std::pair<udp::endpoint, bool>>(), ""));
    _rooms.push_back(std::make_tuple(ecs::Scenes::ROOM3, false, false, std::vector<std::pair<udp::endpoint, bool>>(), ""));
    _rooms.push_back(std::make_tuple(ecs::Scenes::ROOM4, false, false, std::vector<std::pair<udp::endpoint, bool>>(), ""));
}

CustomServer::~CustomServer()
{
}

void CustomServer::updateSceneRoomInVectorRoom(ecs::Scenes room_scene, bool private_room, std::string player_name, udp::endpoint client_endpoint)
{
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        if (std::get<0>(_rooms.at(i)) == room_scene) {
            std::get<1>(_rooms.at(i)) = true;
            std::get<2>(_rooms.at(i)) = private_room;
            std::get<3>(_rooms.at(i)).push_back(std::make_pair(client_endpoint, true));
            std::get<4>(_rooms.at(i)) = player_name;
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
            _createRoom(msg, target_endpoint);
        } break;
        case network::CustomMessage::CreatePrivateRoom: {
            _createRoom(msg, target_endpoint, true);
        } break;
        case network::CustomMessage::InitListRoom: {
            network::Message<network::CustomMessage> message;
            _getInfoForListRoomScene(message);
            send(message, target_endpoint);
        } break;
        case network::CustomMessage::JoinRoom: {
            _joinRoom(target_endpoint, msg);
        } break;
        case network::CustomMessage::JoinRoomById: {
            _joinRoomById(target_endpoint, msg);
        } break;
        case network::CustomMessage::RemoveClient: {
            _quitRoom(target_endpoint);
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
            _getInfoForListRoomScene(message2);
            sendToAllClients(message2);
            return;
        }
    }
    network::Message<network::CustomMessage> error_message;
    error_message.header.id = network::CustomMessage::MaxRoomLimit;
    send(error_message, target_endpoint);
}

void CustomServer::_getInfoForListRoomScene(network::Message<network::CustomMessage> &message)
{
    message.header.id = network::CustomMessage::UpdateListRoom;
    std::size_t nb_rooms = 0;
    std::string rooms_text;
    for (int i = _rooms.size() - 1; i >= 0; i--) {
        if (std::get<1>(_rooms.at(i)) == true && std::get<2>(_rooms.at(i)) == false) {
            rooms_text = std::get<4>(_rooms.at(i)) + "         " + std::to_string(std::get<3>(_rooms.at(i)).size()) + "/" + std::to_string(NB_MAX_PLAYERS_PER_ROOM);
            ecs::Text player_name_class(const_cast<char *>(rooms_text.c_str()));
            message << player_name_class;
            message << std::get<0>(_rooms.at(i));
            nb_rooms++;
        }
    }
    message << nb_rooms;
}

void CustomServer::_joinRoom(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    ecs::Scenes room_scene;
    msg >> room_scene;
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        if (std::get<0>(_rooms.at(i)) == room_scene && std::get<3>(_rooms.at(i)).size() == NB_MAX_PLAYERS_PER_ROOM) {
            network::Message<network::CustomMessage> error_message;
            error_message.header.id = network::CustomMessage::MaxPlayersInRoom;
            send(error_message, target_endpoint);
            return;
        } else if (std::get<0>(_rooms.at(i)) == room_scene) {
            std::get<3>(_rooms.at(i)).push_back(std::make_pair(target_endpoint, false));
            break;
        }
    }
    _registry.setActualScene(room_scene);
    for (auto &it : _registry.getEntities())
        sendNetworkComponents(it, network::CustomMessage::SendComponent, target_endpoint);
    network::Message<network::CustomMessage> message;
    message.header.id = network::CustomMessage::AllComponentSent;
    send(message, target_endpoint);
    std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
    network::Message<network::CustomMessage> message2;
    _getInfoForListRoomScene(message2);
    sendToAllClients(message2);
}

void CustomServer::_joinRoomById(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    int id_room = 0;
    msg >> id_room;
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
                    } else
                        std::get<3>(_rooms.at(i)).push_back(std::make_pair(target_endpoint, false));
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
                        _getInfoForListRoomScene(message3);
                        sendToAllClients(message3);
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

void CustomServer::_quitRoom(udp::endpoint target_endpoint)
{
    for (std::size_t i = 0; i < _rooms.size(); i++) {
        for (std::size_t j = 0; j < std::get<3>(_rooms.at(i)).size(); j++) {
            if (std::get<3>(_rooms.at(i)).at(j).first == target_endpoint) {
                if (std::get<3>(_rooms.at(i)).at(j).second == true && std::get<3>(_rooms.at(i)).size() > 1) {
                    try {
                        std::get<3>(_rooms.at(i)).at(j+1).second = true;
                    } catch (const std::out_of_range &e) {
                        std::get<3>(_rooms.at(i)).at(j-1).second = true;
                    }
                }
                std::get<3>(_rooms.at(i)).erase(std::next(std::get<3>(_rooms.at(i)).begin(), j));
                if (std::get<3>(_rooms.at(i)).size() == 0) {
                    std::get<1>(_rooms.at(i)) = false;
                    _registry.setActualScene(std::get<0>(_rooms.at(i)));
                    for (auto &it : _registry.getEntities())
                        _registry.killEntity(it);
                }
                network::Message<network::CustomMessage> message;
                _getInfoForListRoomScene(message);
                sendToAllClients(message);
                return;
            }
        }
    }
}

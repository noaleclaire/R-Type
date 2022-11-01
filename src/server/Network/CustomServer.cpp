/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#include "CustomServer.hpp"
#include "../../Ecs/Component/component.hpp"
#include "../../Ecs/Exceptions/ExceptionComponentNull.hpp"
#include "../../Ecs/Exceptions/ExceptionIndexComponent.hpp"
#include "../../Ecs/Factory.hpp"
#include "../Scenes/LobbySelector.hpp"
#include "../Scenes/Room.hpp"

CustomServer::CustomServer(boost::asio::io_context &io_context, unsigned short local_port)
    : network::UdpServerClient<network::CustomMessage>(io_context, local_port)
{
}

CustomServer::~CustomServer()
{
}

void CustomServer::addSceneRoomToVectorRoom(ecs::Scenes scene)
{
    _rooms.push_back(scene);
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
            LobbySelector::initScene(this, _registry);
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::AllGameComponentSent;
            sendToAllClients(message);
        } break;
        case network::CustomMessage::CreateRoom: {
            switch (_rooms.size())
            {
                case 0: Room::initScene(this, _registry, ecs::Scenes::ROOM1); break;
                case 1: Room::initScene(this, _registry, ecs::Scenes::ROOM2); break;
                case 2: Room::initScene(this, _registry, ecs::Scenes::ROOM3); break;
                case 3: Room::initScene(this, _registry, ecs::Scenes::ROOM4); break;
                case 4: Room::initScene(this, _registry, ecs::Scenes::ROOM5); break;
                case 5: Room::initScene(this, _registry, ecs::Scenes::ROOM6); break;
                default: return; break;
            }
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::AllGameComponentSent;
            send(message);
        } break;
        case network::CustomMessage::RemoveClient: {
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

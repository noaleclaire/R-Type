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

CustomServer::CustomServer(boost::asio::io_context &io_context, unsigned short local_port)
    : network::UdpServerClient<network::CustomMessage>(io_context, local_port)
{
}

CustomServer::~CustomServer()
{
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
            _initGame();
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::AllGameComponentSent;
            sendToAllClients(message);
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

            // case network::CustomMsgTypes::MessageAll:
            // {
            //     std::cout << "[" << client->GetID() << "]: Message All\n";

            //     // Construct a new message and send it to all clients
            //     olc::net::message<CustomMsgTypes> msg;
            //     msg.header.id = CustomMsgTypes::ServerMessage;
            //     msg << client->GetID();
            //     MessageAllClients(msg, client);

            // }
            // break;
    }
}

void CustomServer::_initGame()
{
    std::size_t entity;
    _registry.setActualScene(ecs::Scenes::GAME);

    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::BACKGROUND, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0);
    _sendNetworkComponents(entity);
    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::BACKGROUND, 1280, 0, 2, 0, 0, 0, 0, 0, 1, 0);
    _sendNetworkComponents(entity);
    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::BACKGROUND, 500, 0, 1, 0, 0, 0, 0, 0, 2, 1);
    _sendNetworkComponents(entity);
    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::SPACESHIP, 0, 340, 0, 0, 0, 0, 3);
    _sendNetworkComponents(entity);
    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::MONSTER, 1000, 450, 0, 0, 0, 0, 3);
    _sendNetworkComponents(entity);
}

void CustomServer::_sendNetworkComponents(std::size_t entity)
{
    for (std::size_t i = 0; i < _registry.getNetMessageCreate().size(); i++) {
        try {
            network::Message<network::CustomMessage> message = _registry.getNetMessageCreate().at(i)(entity, network::CustomMessage::SendGameComponent, i);
            sendToAllClients(message);
            std::this_thread::sleep_for(5ms);
        } catch (const ecs::ExceptionComponentNull &e) {
            continue;
        } catch (const ecs::ExceptionIndexComponent &e) {
            continue;
        }
    }
}

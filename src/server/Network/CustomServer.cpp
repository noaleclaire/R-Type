/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#include "CustomServer.hpp"
#include "../../Ecs/Component/component.hpp"
#include "../../Ecs/Factory.hpp"
#include "../../Ecs/Exceptions/ExceptionIndexComponent.hpp"
#include "../../Ecs/Exceptions/ExceptionComponentNull.hpp"

CustomServer::CustomServer(boost::asio::io_context &io_context, unsigned short local_port) :
    network::UdpServerClient<network::CustomMessage>(io_context, local_port)
{
}

CustomServer::~CustomServer()
{
}

void CustomServer::onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    switch (msg.header.id)
    {
        case network::CustomMessage::PingServer:
        {
            std::cout << "[" << "connection..." << "]: Server Ping\n";
        }
        break;
        case network::CustomMessage::SwitchToGame:
        {
            network::Message<network::CustomMessage> _msg;
            _msg.header.id = network::CustomMessage::AllGameComponentSent;
            _initGame();
            send(_msg, target_endpoint);
        }
        default: break;

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

    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::BACKGROUND, 0, 0, 0, 0, 0, 0, 1);
    _sendNetworkComponents(entity);
    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::SPACESHIP, 0, 340, 0, 0, 0, 0, 2);
    _sendNetworkComponents(entity);
    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::MONSTER, 1000, 450, 0, 0, 0, 0, 2);
    _sendNetworkComponents(entity);
}

void CustomServer::_sendNetworkComponents(std::size_t entity)
{
    _sendNetworkComponent<ecs::Clickable>(entity, ecs::ComponentTypes::CLICKABLE);
    _sendNetworkComponent<ecs::Collider>(entity, ecs::ComponentTypes::COLLIDER);
    _sendNetworkComponent<ecs::Controllable>(entity, ecs::ComponentTypes::CONTROLLABLE);
    _sendNetworkComponent<ecs::Drawable>(entity, ecs::ComponentTypes::DRAWABLE);
    _sendNetworkComponent<ecs::Type>(entity, ecs::ComponentTypes::TYPE);
    _sendNetworkComponent<ecs::Killable>(entity, ecs::ComponentTypes::KILLABLE);
    _sendNetworkComponent<ecs::Layer>(entity, ecs::ComponentTypes::LAYER);
    _sendNetworkComponent<ecs::Position>(entity, ecs::ComponentTypes::POSITION);
    _sendNetworkComponent<ecs::Shooter>(entity, ecs::ComponentTypes::SHOOTER);
    _sendNetworkComponent<ecs::Shootable>(entity, ecs::ComponentTypes::SHOOTABLE);
    _sendNetworkComponent<ecs::Rectangle>(entity, ecs::ComponentTypes::RECTANGLE);
}

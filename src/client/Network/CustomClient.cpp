/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#include <typeindex>
#include "CustomClient.hpp"
#include "../../Ecs/Exceptions/Exception.hpp"

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
    send(msg);
}

void CustomClient::initGame()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::SwitchToGame;
    send(msg);
}

void CustomClient::clientDisconnect()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::RemoveClient;
    send(msg);
}

void CustomClient::onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    static_cast<void>(target_endpoint);
    switch (msg.header.id) {
        case network::CustomMessage::SendGameComponent: {
            registry->setActualScene(ecs::Scenes::GAME);
            std::size_t index_component_create = 0;
            msg >> index_component_create;
            registry->getNetComponentCreate().at(index_component_create)(msg);
        } break;
        case network::CustomMessage::AllGameComponentSent: {
            _setRectAndSpriteComponent();
        } break;
        default: break;
    }
}

void CustomClient::_setRectAndSpriteComponent()
{
    std::vector<float> rect;

    for (auto &it : registry->getEntities()) {
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
        }
    }
}

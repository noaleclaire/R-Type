/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#include "CustomClient.hpp"
#include "../../Ecs/Component/component.hpp"
#include "../../Ecs/Exceptions/Exception.hpp"
#include "../../Ecs/NetworkComponent.hpp"

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
            _receivedGameComponent(msg);
        } break;
        case network::CustomMessage::ComponentType: {
            msg >> _actualType;
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
        } catch (const ecs::Exception &e) {
            continue;
        }
    }
}

void CustomClient::_receivedGameComponent(network::Message<network::CustomMessage> &msg)
{
    switch (_actualType) {
        case ecs::ComponentTypes::CLICKABLE: {
            auto res = ecs::NetworkComponent<ecs::Clickable, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Clickable>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::COLLIDER: {
            auto res = ecs::NetworkComponent<ecs::Collider, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Collider>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::CONTROLLABLE: {
            auto res = ecs::NetworkComponent<ecs::Controllable, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Controllable>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::DRAWABLE: {
            auto res = ecs::NetworkComponent<ecs::Drawable, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Drawable>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::KILLABLE: {
            auto res = ecs::NetworkComponent<ecs::Killable, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Killable>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::LAYER: {
            auto res = ecs::NetworkComponent<ecs::Layer, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Layer>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::POSITION: {
            auto res = ecs::NetworkComponent<ecs::Position, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Position>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::RECTANGLE: {
            auto res = ecs::NetworkComponent<ecs::Rectangle, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Rectangle>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::SHOOTABLE: {
            auto res = ecs::NetworkComponent<ecs::Shootable, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Shootable>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::SHOOTER: {
            auto res = ecs::NetworkComponent<ecs::Shooter, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Shooter>(registry->getEntityById(res.first), res.second);
        } break;
        case ecs::ComponentTypes::TYPE: {
            auto res = ecs::NetworkComponent<ecs::Type, network::CustomMessage>::createComponent(msg);
            registry->addEntity(res.first);
            registry->addComponent<ecs::Type>(registry->getEntityById(res.first), res.second);
        } break;
        default: break;
    }
}

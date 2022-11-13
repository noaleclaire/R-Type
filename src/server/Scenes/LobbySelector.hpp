/*
** EPITECH PROJECT, 2022
** LobbySelector
** File description:
** LobbySelector
*/

#pragma once
#include "ScenesInitializer.hpp"
#include "../../Network/UdpServerClient.hpp"

class CustomServer;
class LobbySelector : public ScenesInitializer {
    public:
        LobbySelector() = default;
        ~LobbySelector() = default;

        static void initScene(CustomServer *server, ecs::Registry &registry, udp::endpoint client_endpoint)
        {
            std::size_t entity;
            registry.setActualScene(ecs::Scenes::GAME);

            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, 0, 0, 0, 0, 1, 0);
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 1280, 0, -80, 0, 0, 0, 0, 0, 1, 0);
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 500, 0, -60, 0, 0, 0, 0, 0, 2, 1);
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::SPACESHIP, 0, 340, 0, 0, 0, 0, 3);
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 1000, 450, 0, 0, 0, 0, 3, 0);
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 720, 550, 0, 0, 0, 0, 3, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BASIC_MONSTER);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::SHOT, registry.getComponents<ecs::Position>().at(entity).value().getXPosition(), registry.getComponents<ecs::Position>().at(entity).value().getYPosition(), 0, 0, 0, 0, 4, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BASIC_SHOT);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 800, 0, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BOSS_FIRE_SPACESHIP);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);

            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 1000, 30, 0, 0, 0, 0, 5, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BOSS_FOREST_RED);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::SHOT, (registry.getComponents<ecs::Position>().at(entity).value().getXPosition()/2), (registry.getComponents<ecs::Position>().at(entity).value().getYPosition()/2), 0, 0, 0, 0, 4, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::RED_SHOT);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 550, 30, 0, 0, 0, 0, 5, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BOSS_FOREST_GREEN);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::SHOT, (registry.getComponents<ecs::Position>().at(entity).value().getXPosition()/2), (registry.getComponents<ecs::Position>().at(entity).value().getYPosition()/2), 0, 0, 0, 0, 4, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::GREEN_SHOT);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 775, 350, 0, 0, 0, 0, 5, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BOSS_FOREST_BLUE);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::SHOT, (registry.getComponents<ecs::Position>().at(entity).value().getXPosition()/2), (registry.getComponents<ecs::Position>().at(entity).value().getYPosition()/2), 0, 0, 0, 0, 4, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BLUE_SHOT);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 690, 100, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BOSS_CAVERN_MAGICIAN);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);

            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 900, 100, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BOSS_ICE_HEADESTROYER);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);

            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 800, 100, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::BOSS_DESERT_WORMS);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);

            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 1000, 100, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::FIRE_MONSTER);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 1000, 200, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::ICE_MONSTER);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 1000, 300, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::CAVE_MONSTER);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 1000, 400, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::FOREST_MONSTER);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 1000, 500, 0, 0, 0, 0, 5, 0);
            // registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::DESERT_MONSTER);
            // registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            // server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint, true);
        }
};

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
        /**
         * @brief Construct a new Lobby Selector object
         * 
         */
        LobbySelector() = default;
        /**
         * @brief Destroy the Lobby Selector object
         * 
         */
        ~LobbySelector() = default;
        /**
         * @brief 
         * 
         * @param server 
         * @param registry 
         * @param client_endpoint 
         */
        static void initScene(CustomServer *server, ecs::Registry &registry, udp::endpoint client_endpoint)
        {
            std::size_t entity;
            registry.setActualScene(ecs::Scenes::GAME);

            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, 0, 0, 0, 0, 1, 0);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 1280, 0, -80, 0, 0, 0, 0, 0, 1, 0);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 500, 0, -60, 0, 0, 0, 0, 0, 2, 1);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::SPACESHIP, 0, 340, 0, 0, 0, 0, 3, 0);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint, true);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::MONSTER, 1000, 450, 0, 0, 0, 0, 3);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint, true);
        }
};

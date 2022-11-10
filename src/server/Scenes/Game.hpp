/*
** EPITECH PROJECT, 2022
** Game
** File description:
** Game
*/

#pragma once
#include <chrono>
#include <sstream>
#include <iomanip>
#include "ScenesInitializer.hpp"
#include "../../Network/UdpServerClient.hpp"
#include "../../Utilities/LevelManager.hpp"

class CustomServer;
class Game : public ScenesInitializer {
    public:
        /**
         * @brief Construct a new Game object
         * 
         */
        Game() = default;
        /**
         * @brief Destroy the Game object
         * 
         */
        ~Game() = default;
        /**
         * @brief Init the scene and start the clock corresponding to the level
         * 
         * @param server
         * @param registry
         * @param scene
         * @param client_endpoint
         * @param level
         * @param level_nb
         */
        static void initScene(CustomServer *server, ecs::Registry &registry, ecs::Scenes scene, udp::endpoint client_endpoint, LevelManager &level, std::size_t level_nb)
        {
            std::size_t entity;

            registry.setActualScene(scene);
            server->startTimes(level_nb);
            for (auto &it : level.getEntitiesDatas()) {
                if (it._attributes.at(EntityAttributes::spawn_time) == 0) {
                    entity = ecs::Factory::createEntity(registry, it._entity_type_and_id.first, it._attributes.at(EntityAttributes::position_x).value(), it._attributes.at(EntityAttributes::position_y).value(),
                        it._attributes.at(EntityAttributes::velocity_x).value(), it._attributes.at(EntityAttributes::velocity_y).value(), 0, 0, 0, 0, it._attributes.at(EntityAttributes::layer), it._entity_type_and_id.second);
                    if (it._attributes.at(EntityAttributes::shooter).value() == true)
                        registry.addComponent<ecs::Shooter>(registry.getEntityById(entity), ecs::Shooter());
                    // registry.addComponent<ecs::CompoServer>(registry.getEntityById(entity), ecs::CompoServer());
                    server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint);
                }
            }
        }
        /**
         * @brief Update the scene with the clock
         * 
         * @param server
         * @param registry
         * @param scene
         * @param client_endpoint
         * @param level
         * @param level_nb
         */
        static void updateScene(CustomServer *server, ecs::Registry &registry, ecs::Scenes scene, udp::endpoint client_endpoint, LevelManager &level, std::size_t level_nb)
        {
            std::size_t entity;
            std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();

            registry.setActualScene(scene);
            for (auto &it : level.getEntitiesDatas()) {
                if (it._attributes.at(EntityAttributes::spawn_time).value() < (std::chrono::time_point_cast<std::chrono::milliseconds>(server->getLastTime(level_nb)).time_since_epoch().count() - std::chrono::time_point_cast<std::chrono::milliseconds>(server->getStartTime(level_nb)).time_since_epoch().count()) &&
                    it._attributes.at(EntityAttributes::spawn_time).value() >= (std::chrono::time_point_cast<std::chrono::milliseconds>(t).time_since_epoch().count() - std::chrono::time_point_cast<std::chrono::milliseconds>(server->getStartTime(level_nb)).time_since_epoch().count())) {
                    entity = ecs::Factory::createEntity(registry, it._entity_type_and_id.first, it._attributes.at(EntityAttributes::position_x).value(), it._attributes.at(EntityAttributes::position_y).value(),
                        it._attributes.at(EntityAttributes::velocity_x).value(), it._attributes.at(EntityAttributes::velocity_y).value(), 0, 0, 0, 0, it._attributes.at(EntityAttributes::layer), it._entity_type_and_id.second);
                    if (it._attributes.at(EntityAttributes::shooter).value() == true)
                        registry.addComponent<ecs::Shooter>(registry.getEntityById(entity), ecs::Shooter());
                    // registry.addComponent<ecs::CompoServer>(registry.getEntityById(entity), ecs::CompoServer());
                    server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint);
                }
            }
            server->setLastTime(level_nb, t);
        }
};

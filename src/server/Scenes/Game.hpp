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
#include "../../Ecs/Exceptions/ExceptionComponentNull.hpp"
#include "../../Ecs/Exceptions/ExceptionIndexComponent.hpp"
#include "../../Ecs/Systems/SystemsServer.hpp"

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
         * @param clients_endpoint
         * @param level
         */
        static void initScene(CustomServer *server, ecs::Registry &registry, ecs::Scenes scene, std::vector<std::pair<udp::endpoint, bool>> &clients_endpoint, LevelManager &level)
        {
            std::size_t entity;

            registry.setActualScene(scene);

            for (std::size_t client_id = 0; client_id < clients_endpoint.size(); client_id++) {
                ecs::Factory::createEntity(registry, ecs::EntityTypes::SPACESHIP, 100, 120 * (client_id + 1), 1, client_id);
            }
            for (auto &it : level.getEntitiesDatas()) {
                entity = ecs::Factory::createEntity(registry, it._entity_type_and_id.first, it._attributes.at(EntityAttributes::position_x).value(), it._attributes.at(EntityAttributes::position_y).value(),
                    it._attributes.at(EntityAttributes::velocity_x).value(), it._attributes.at(EntityAttributes::velocity_y).value(), 0, 0, 0, 0, it._attributes.at(EntityAttributes::layer).value(), it._entity_type_and_id.second);
                if (it._attributes.at(EntityAttributes::shooter).value() == true)
                    registry.addComponent<ecs::Shooter>(registry.getEntityById(entity), ecs::Shooter());
                registry.addComponent<ecs::CompoServer>(registry.getEntityById(entity), ecs::CompoServer(it._attributes.at(EntityAttributes::spawn_time).value()));
            }
            server->startTimes(scene);
        }
        static void getScene(CustomServer *server, ecs::Registry &registry, ecs::Scenes scene, std::vector<std::pair<udp::endpoint, bool>> &clients_endpoint, udp::endpoint target_endpoint)
        {
            registry.setActualScene(scene);

            for (auto &it : registry.getEntities()) {
                try {
                    registry.getComponents<ecs::CompoServer>().at(it);
                } catch (const ecs::Exception &err) {
                    for (std::size_t client_id = 0; client_id < clients_endpoint.size(); client_id++) {
                        if (clients_endpoint.at(client_id).first == target_endpoint &&
                        registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::SPACESHIP &&
                        registry.getComponents<ecs::Type>().at(it).value().getEntityID() == client_id) {
                            registry.addComponent<ecs::Controllable>(it, ecs::Controllable());
                            registry.getComponents<ecs::Position>().at(it).value().setXVelocity(150);
                            registry.getComponents<ecs::Position>().at(it).value().setYVelocity(150);
                            server->sendNetworkComponents<network::CustomMessage>(registry, it, network::CustomMessage::SendComponent, target_endpoint);
                            break;
                        }
                    }
                    try {
                        registry.getComponents<ecs::Controllable>().at(it);
                        registry.removeComponent<ecs::Controllable>(it);
                        registry.getComponents<ecs::Position>().at(it).value().setXVelocity(0);
                        registry.getComponents<ecs::Position>().at(it).value().setYVelocity(0);
                        continue;
                    } catch (const ecs::ExceptionIndexComponent &e) {
                        server->sendNetworkComponents<network::CustomMessage>(registry, it, network::CustomMessage::SendComponent, target_endpoint);
                    } catch (const ecs::ExceptionComponentNull &e) {
                        server->sendNetworkComponents<network::CustomMessage>(registry, it, network::CustomMessage::SendComponent, target_endpoint);
                    }
                }
            }
            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::AllComponentSent;
            server->send(message, target_endpoint);
            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
            std::cout << std::endl;
        }
        /**
         * @brief Update the scene with the clock
         *
         * @param server
         * @param registry
         * @param scene
         * @param clients_endpoint
         */
        static void updateScene(CustomServer *server, ecs::Registry &registry, ecs::Scenes scene, std::vector<std::pair<udp::endpoint, bool>> clients_endpoint)
        {
            std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();

            registry.setActualScene(scene);

            while (1) {
                t = std::chrono::system_clock::now();
                try {
                    for (auto &it : registry.getEntities()) {
                        try {
                            registry.getComponents<ecs::CompoServer>().at(it);
                            if ((std::chrono::milliseconds(registry.getComponents<ecs::CompoServer>().at(it).value().getSpawnTime()) > server->getLastTime(scene) - server->getStartTime(scene) &&
                                std::chrono::milliseconds(registry.getComponents<ecs::CompoServer>().at(it).value().getSpawnTime()) <= t - server->getStartTime(scene)) ||
                                (registry.getComponents<ecs::CompoServer>().at(it).value().getSpawnTime() == 0 && server->getLastTime(scene) - server->getStartTime(scene) == std::chrono::milliseconds(0))) {
                                std::cout << "timepoint" << std::endl;
                                for (auto &client_endpoint : clients_endpoint) {
                                    server->sendNetworkComponents<network::CustomMessage>(registry, it, network::CustomMessage::SendComponent, client_endpoint.first);
                                    network::Message<network::CustomMessage> message;
                                    message.header.id = network::CustomMessage::AllComponentSent;
                                    server->send(message, client_endpoint.first);
                                    std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
                                }
                            }
                            if (std::chrono::milliseconds(registry.getComponents<ecs::CompoServer>().at(it).value().getSpawnTime()) < t - server->getStartTime(scene)) {
                                ecs::Registry tmp_registry = registry;
                                ecs::SystemsServer::Shot(registry, server, clients_endpoint);
                                ecs::SystemsServer::Position(registry, registry.getComponents<ecs::Position>(), server->getLastTime(scene));
                                for (auto &client_endpoint : clients_endpoint) {
                                    server->compareRegistries(client_endpoint.first, registry, tmp_registry);
                                }
                            }
                        } catch (const ecs::ExceptionComponentNull &e) {
                            continue;
                        } catch (const ecs::ExceptionIndexComponent &e) {
                            continue;
                        }
                    }
                } catch (const ecs::Exception &e) {
                    return;
                }
                server->setLastTime(scene, t);
            }
        }
};

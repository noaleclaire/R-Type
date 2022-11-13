/*
** EPITECH PROJECT, 2022
** SystemsServer.cpp
** File description:
** SystemsServer.cpp
*/

#include "SystemsServer.hpp"

namespace ecs
{
    void SystemsServer::Shot(Registry &registry, CustomServer *server, std::vector<std::pair<udp::endpoint, bool>> clients_endpoint)
    {
        for (auto &it : registry.getEntities()) {
            try {
                if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::SHOT) {
                    if (registry.getComponents<ecs::Ammo>().at(it).value().isDead(registry.getComponents<ecs::Position>().at(it).value().getXPosition(), registry.getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle()) == true ||
                        registry.getComponents<ecs::Ammo>().at(it).value().isDead() == true) {
                        std::cout << "kill: " << it << std::endl;
                        registry.killEntity(registry.getEntityById(it));
                        for (auto &client_endpoint : clients_endpoint) {
                            network::Message<network::CustomMessage> message;
                            message.header.id = network::CustomMessage::KillAnEntity;
                            message << it;
                            server->send(message, client_endpoint.first);
                            std::this_thread::sleep_for(std::chrono::milliseconds(ecs::Enum::ping_latency_ms));
                        }
                        continue;
                    }
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

    void SystemsServer::Kill(Registry &registry, SparseArray<ecs::Killable> &killable, CustomServer *server, std::vector<std::pair<udp::endpoint, bool>> clients_endpoint)
    {
        for (auto &it : registry.getEntities()) {
            try {
                killable.at(it);
                if (killable.at(it).value().getLife() == 0) {
                    registry.killEntity(it);
                    for (auto &client_endpoint : clients_endpoint) {
                        network::Message<network::CustomMessage> message;
                        message.header.id = network::CustomMessage::KillAnEntity;
                        message << it;
                        server->send(message, client_endpoint.first);
                        std::this_thread::sleep_for(std::chrono::milliseconds(ecs::Enum::ping_latency_ms));
                    }
                }
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
}
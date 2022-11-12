/*
** EPITECH PROJECT, 2022
** SystemsServer.cpp
** File description:
** SystemsServer.cpp
*/

#include "SystemsServer.hpp"

namespace ecs
{
    void SystemsServer::Position(Registry &registry, SparseArray<ecs::Position> const &position, std::chrono::time_point<std::chrono::system_clock> last_time)
    {
        for (auto &it : registry.getEntities()) {
            try {
                registry.getComponents<ecs::CompoServer>().at(it);
                float posX = position.at(it).value().getXPosition();
                float posY = position.at(it).value().getYPosition();
                float veloX = position.at(it).value().getXVelocity();
                float veloY = position.at(it).value().getYVelocity();
                posX += veloX * (std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count() - std::chrono::time_point_cast<std::chrono::microseconds>(last_time).time_since_epoch().count())/1000000;
                posY += veloY * (std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count() - std::chrono::time_point_cast<std::chrono::microseconds>(last_time).time_since_epoch().count())/1000000;
                registry.getComponents<ecs::Position>().at(it).value().setXPosition(posX);
                registry.getComponents<ecs::Position>().at(it).value().setYPosition(posY);
            } catch (const ExceptionComponentNull &e) {
                continue;
            } catch (const ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

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
                            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
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
}
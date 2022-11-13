/*
** EPITECH PROJECT, 2022
** SystemsServer.cpp
** File description:
** SystemsServer.cpp
*/

#include "SystemsServer.hpp"
#include "../Factory.hpp"
#include <iomanip>

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
                float test = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count() - std::chrono::time_point_cast<std::chrono::microseconds>(last_time).time_since_epoch().count();
                test /= 1000000;
                // std::cout << (std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count() - std::chrono::time_point_cast<std::chrono::microseconds>(last_time).time_since_epoch().count())/1000 << "ms" << std::endl;
                std::cout << test << "s" << std::endl;
                posX += veloX * test;
                posY += veloY * test;
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

    void SystemsServer::Collider(Registry &registry, SparseArray<ecs::Collider> &collider)
    {
        for (auto &it : registry.getEntities()) {
            try {
                collider.at(it);
                for (auto &it_in : registry.getEntities()) {
                    try {
                        collider.at(it_in);
                        if (it == it_in)
                            continue;
                        if (_checkCollisionByPosAndRect(registry, it, it_in) == true) {
                            if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == SPACESHIP && registry.getComponents<ecs::Type>().at(it_in).value().getEntityType() == MONSTER)
                                registry.getComponents<ecs::Killable>().at(it).value().setLife(0);
                            if (registry.getComponents<ecs::Type>().at(it).value().getEntityType() == SHOT && registry.getComponents<ecs::Type>().at(it_in).value().getEntityType() == MONSTER)
                                registry.getComponents<ecs::Killable>().at(it_in).value().substractLife(registry.getComponents<ecs::Ammo>().at(it).value().getDamage());
                        }
                    } catch (const ExceptionComponentNull &e) {
                        continue;
                    } catch (const ExceptionIndexComponent &e) {
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

    bool SystemsServer::_checkCollisionByPosAndRect(Registry &registry, std::size_t entity, std::size_t entity_in)
    {
        int entity_posX = registry.getComponents<ecs::Position>().at(entity).value().getXPosition();
        int entity_posY = registry.getComponents<ecs::Position>().at(entity).value().getYPosition();
        int entity_in_posX = registry.getComponents<ecs::Position>().at(entity_in).value().getXPosition();
        int entity_in_posY = registry.getComponents<ecs::Position>().at(entity_in).value().getYPosition();
        int entity_width = registry.getComponents<ecs::Rectangle>().at(entity).value().getWidthRectangle();
        int entity_height = registry.getComponents<ecs::Rectangle>().at(entity).value().getHeightRectangle();
        int entity_in_width = registry.getComponents<ecs::Rectangle>().at(entity_in).value().getWidthRectangle();
        int entity_in_height = registry.getComponents<ecs::Rectangle>().at(entity_in).value().getHeightRectangle();
        bool xCollide = false;

        for (int tmp_x = entity_in_posX; xCollide == false && tmp_x < entity_in_posX + entity_in_width; tmp_x++) {
            if (tmp_x > entity_posX && tmp_x < entity_posX + entity_width)
                xCollide = true;
        }
        for (int tmp_y = entity_in_posY; xCollide == true && tmp_y < entity_in_posY + entity_in_height; tmp_y++) {
            if (tmp_y > entity_posY && tmp_y < entity_posY + entity_height)
                return (true);
        }
        return (false);
    }
}
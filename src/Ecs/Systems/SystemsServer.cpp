/*
** EPITECH PROJECT, 2022
** SystemsServer.cpp
** File description:
** SystemsServer.cpp
*/

#include "SystemsServer.hpp"

namespace ecs
{
    void SystemsServer::Kill(Registry &registry, SparseArray<ecs::Killable> &killable, CustomServer *server, std::vector<std::pair<udp::endpoint, bool>> clients_endpoint)
    {
        for (auto &it : registry.getEntities()) {
            try {
                killable.at(it);
                if (killable.at(it).value().getLife() == 0) {
                    registry.killEntity(it);
                    // server->_mtx.lock();
                    for (auto &client_endpoint : clients_endpoint) {
                        network::Message<network::CustomMessage> message;
                        message.header.id = network::CustomMessage::KillAnEntity;
                        message << it;
                        server->send(message, client_endpoint.first);
                        std::this_thread::sleep_for(std::chrono::milliseconds(ecs::Enum::ping_latency_ms));
                    }
                    // server->_mtx.unlock();
                }
            } catch (const Exception &e) {
                continue;
            }
        }
    }
}
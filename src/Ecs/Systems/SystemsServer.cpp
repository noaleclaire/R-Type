/*
** EPITECH PROJECT, 2022
** SystemsServer.cpp
** File description:
** SystemsServer.cpp
*/

#include "SystemsServer.hpp"

namespace ecs
{
    void SystemsServer::Kill(Registry &registry, SparseArray<ecs::Killable> &killable)
    {
        // server->_mtx.lock();
        for (auto &it : registry.getEntities()) {
            try {
                killable.at(it);
                if (killable.at(it).value().getLife() == 0) {
                    registry.killEntity(it);
                }
            } catch (const Exception &e) {
                continue;
            }
        }
        // server->_mtx.unlock();
    }
}
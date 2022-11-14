/*
** EPITECH PROJECT, 2022
** SystemsServer
** File description:
** SystemsServer
*/

#pragma once

#include "../../server/Network/CustomServer.hpp"

namespace ecs
{
    class SystemsServer {
      public:
        /**
         * @brief
         *
         * @param registry
         * @param killable
         * @param server
         * @param clients_endpoint
         */
        static void Kill(Registry &registry, SparseArray<ecs::Killable> &killable, CustomServer *server);
      private:
    };
}
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
         * @brief System handling shots in server side
         *
         * @param registry
         * @param server
         * @param clients_endpoint
         */
        static void Shot(ecs::Registry &registry, CustomServer *server, std::vector<std::pair<udp::endpoint, bool>> clients_endpoint);
        /**
         * @brief
         *
         * @param registry
         * @param killable
         * @param server
         * @param clients_endpoint
         */
        static void Kill(Registry &registry, SparseArray<ecs::Killable> &killable, CustomServer *server,std::vector<std::pair<udp::endpoint, bool>> clients_endpoint);
      private:
    };
}
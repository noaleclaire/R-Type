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
         * @param position
         * @param last_time
         */
        static void VerifyPosition(Registry &registry, SparseArray<ecs::Position> const &position, float loop_time);
        /**
         * @brief System handling shots in server side
         *
         * @param registry
         * @param server
         * @param clients_endpoint
         */
        static void Shot(ecs::Registry &registry, CustomServer *server, std::vector<std::pair<udp::endpoint, bool>> clients_endpoint);
    };
}
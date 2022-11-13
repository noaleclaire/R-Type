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
        /**
         * @brief
         *
         * @param registry
         * @param collider
         */
        static void Collider(Registry &registry, SparseArray<ecs::Collider> &collider);
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
        /**
         * @brief 
         *
         * @param registry
         * @param entity
         * @param entity_in
         */
        static bool _checkCollisionByPosAndRect(Registry &registry, std::size_t entity, std::size_t entity_in);
    };
}
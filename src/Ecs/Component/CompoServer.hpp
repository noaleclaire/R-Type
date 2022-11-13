/*
** EPITECH PROJECT, 2022
** CompoServer
** File description:
** CompoServer
*/

#pragma once

#include "AComponent.hpp"

namespace ecs {
    class CompoServer : public AComponent {
        public:
            CompoServer(int spawn_time = 0)
            {
                _spawn_time = spawn_time;
                if (spawn_time < 0)
                    _spawn_time = 0;
            };
            CompoServer(const CompoServer &other) = default;
            ~CompoServer() = default;
            CompoServer &operator=(const CompoServer &other) = default;

            int getSpawnTime() const
            {
                return (_spawn_time);
            };

            friend bool operator==(const CompoServer &lhs, const CompoServer &rhs)
            {
                return lhs._spawn_time == rhs._spawn_time;
            }
        private:
            int _spawn_time;
    };
}

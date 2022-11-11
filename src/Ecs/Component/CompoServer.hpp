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
            CompoServer() = default;
            CompoServer(const CompoServer &other) = default;
            ~CompoServer() = default;
            CompoServer &operator=(const CompoServer &other) = default;

            friend bool operator==(const CompoServer &lhs, const CompoServer &rhs)
            {
                static_cast<void>(lhs);
                static_cast<void>(rhs);
                return true;
            }
        protected:
        private:
    };
}

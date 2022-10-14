/*
** EPITECH PROJECT, 2022
** Collider.hpp
** File description:
** Collider.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Collider : public AComponent {
      public:
        Collider() = default;
        Collider(const Collider &other) = default;
        ~Collider() = default;
        Collider &operator=(const Collider &other) = default;
    };
} // namespace ecs

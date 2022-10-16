/*
** EPITECH PROJECT, 2022
** Controllable.hpp
** File description:
** Controllable.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Controllable : public AComponent {
      public:
        Controllable() = default;
        Controllable(const Controllable &other) = default;
        ~Controllable() = default;
        Controllable &operator=(const Controllable &other) = default;
    };
} // namespace ecs

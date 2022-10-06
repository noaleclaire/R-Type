/*
** EPITECH PROJECT, 2022
** Controllable.hpp
** File description:
** Controllable.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace component
{
    class Controllable : public IComponent {
      public:
        Controllable() = default;
        Controllable(const Controllable &other) = default;
        ~Controllable() override = default;
        Controllable &operator=(const Controllable &other) = default;
    };
} // namespace component

/*
** EPITECH PROJECT, 2022
** Shooter.hpp
** File description:
** Shooter.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class Shooter : public AComponent {
      public:
        Shooter() = default;
        Shooter(const Shooter &other) = default;
        ~Shooter() = default;
        Shooter &operator=(const Shooter &other) = default;
    };
} // namespace component

/*
** EPITECH PROJECT, 2022
** Shooter.hpp
** File description:
** Shooter.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace component
{
    class Shooter : public IComponent {
      public:
        Shooter();
        Shooter(const Shooter &other) = default;
        ~Shooter() override = default;
        Shooter &operator=(const Shooter &other) = default;
    };
} // namespace component

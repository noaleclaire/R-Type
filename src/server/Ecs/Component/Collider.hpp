/*
** EPITECH PROJECT, 2022
** Collider.hpp
** File description:
** Collider.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace component
{
    class Collider : public IComponent {
      public:
        Collider() = default;
        Collider(const Collider &other) = default;
        ~Collider() override = default;
        Collider &operator=(const Collider &other) = default;
    };
} // namespace component

/*
** EPITECH PROJECT, 2022
** Clickable.hpp
** File description:
** Clickable.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class Clickable : public AComponent {
      public:
        Clickable() = default;
        Clickable(const Clickable &other) = default;
        ~Clickable() = default;
        Clickable &operator=(const Clickable &other) = default;
    };
} // namespace component

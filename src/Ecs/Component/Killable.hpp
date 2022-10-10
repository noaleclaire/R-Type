/*
** EPITECH PROJECT, 2022
** Killable.hpp
** File description:
** Killable.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class Killable : public AComponent {
      public:
        Killable() = default;
        Killable(const Killable &other) = default;
        ~Killable() = default;
        Killable &operator=(const Killable &other) = default;
    };
} // namespace component

/*
** EPITECH PROJECT, 2022
** Killable.hpp
** File description:
** Killable.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace component
{
    class Killable : public IComponent {
      public:
        Killable() = default;
        Killable(const Killable &other) = default;
        ~Killable() override = default;
        Killable &operator=(const Killable &other) = default;
    };
} // namespace component

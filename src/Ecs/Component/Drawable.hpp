/*
** EPITECH PROJECT, 2022
** Drawable.hpp
** File description:
** Drawable.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace component
{
    class Drawable : public IComponent {
      public:
        Drawable() = default;
        Drawable(const Drawable &other) = default;
        ~Drawable() override = default;
        Drawable &operator=(const Drawable &other) = default;
    };
} // namespace component

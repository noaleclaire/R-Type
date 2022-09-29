/*
** EPITECH PROJECT, 2022
** Drawable.hpp
** File description:
** Drawable.hpp
*/

#pragma once

namespace component
{
    class Drawable {
      public:
        Drawable() = default;
        Drawable(const Drawable &other) = default;
        ~Drawable() = default;
        Drawable &operator=(const Drawable &other) = default;
    };
} // namespace component

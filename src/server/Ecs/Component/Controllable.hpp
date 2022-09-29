/*
** EPITECH PROJECT, 2022
** Controllable.hpp
** File description:
** Controllable.hpp
*/

#pragma once

namespace component
{
    class Controllable {
      public:
        Controllable() = default;
        Controllable(const Controllable &other) = default;
        ~Controllable() = default;
        Controllable &operator=(const Controllable &other) = default;
    };
} // namespace component

/*
** EPITECH PROJECT, 2022
** Controllable.hpp
** File description:
** Controllable.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Controllable : public AComponent {
      public:
        /**
         * @brief Construct a new Controllable object
         *
         */
        Controllable() = default;
        /**
         * @brief Construct a new Controllable object
         *
         * @param other
         */
        Controllable(const Controllable &other) = default;
        /**
         * @brief Destroy the Controllable object
         *
         */
        ~Controllable() = default;
        /**
         * @brief
         *
         * @param other
         * @return Controllable&
         */
        Controllable &operator=(const Controllable &other) = default;
    };
} // namespace ecs

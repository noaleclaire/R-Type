/*
** EPITECH PROJECT, 2022
** Shooter.hpp
** File description:
** Shooter.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Shooter : public AComponent {
      public:
        /**
         * @brief Construct a new Shooter object
         *
         */
        Shooter() = default;
        /**
         * @brief Construct a new Shooter object
         *
         * @param other
         */
        Shooter(const Shooter &other) = default;
        /**
         * @brief Destroy the Shooter object
         *
         */
        ~Shooter() = default;
        /**
         * @brief
         *
         * @param other
         * @return Shooter&
         */
        Shooter &operator=(const Shooter &other) = default;
    };
} // namespace ecs

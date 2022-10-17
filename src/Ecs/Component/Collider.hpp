/*
** EPITECH PROJECT, 2022
** Collider.hpp
** File description:
** Collider.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Collider : public AComponent {
      public:
        /**
         * @brief Construct a new Collider object
         *
         */
        Collider() = default;
        /**
         * @brief Construct a new Collider object
         *
         * @param other
         */
        Collider(const Collider &other) = default;
        /**
         * @brief Destroy the Collider object
         *
         */
        ~Collider() = default;
        /**
         * @brief
         *
         * @param other
         * @return Collider&
         */
        Collider &operator=(const Collider &other) = default;
    };
} // namespace ecs

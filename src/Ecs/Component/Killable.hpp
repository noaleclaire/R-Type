/*
** EPITECH PROJECT, 2022
** Killable.hpp
** File description:
** Killable.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Killable : public AComponent {
      public:
        /**
         * @brief Construct a new Killable object
         *
         */
        Killable() = default;
        /**
         * @brief Construct a new Killable object
         *
         * @param other
         */
        Killable(const Killable &other) = default;
        /**
         * @brief Destroy the Killable object
         *
         */
        ~Killable() = default;
        /**
         * @brief
         *
         * @param other
         * @return Killable&
         */
        Killable &operator=(const Killable &other) = default;
    };
} // namespace ecs

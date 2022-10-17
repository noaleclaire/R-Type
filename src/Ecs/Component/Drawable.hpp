/*
** EPITECH PROJECT, 2022
** Drawable.hpp
** File description:
** Drawable.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Drawable : public AComponent {
      public:
        /**
         * @brief Construct a new Drawable object
         *
         */
        Drawable() = default;
        /**
         * @brief Construct a new Drawable object
         *
         * @param other
         */
        Drawable(const Drawable &other) = default;
        /**
         * @brief Destroy the Drawable object
         *
         */
        ~Drawable() = default;
        /**
         * @brief
         *
         * @param other
         * @return Drawable&
         */
        Drawable &operator=(const Drawable &other) = default;
    };
} // namespace ecs

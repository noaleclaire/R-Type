/*
** EPITECH PROJECT, 2022
** Shootable.hpp
** File description:
** Shootable.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Shootable : public AComponent {
      public:
        /**
         * @brief Construct a new Shootable object
         *
         */
        Shootable() = default;
        /**
         * @brief Construct a new Shootable object
         *
         * @param other
         */
        Shootable(const Shootable &other) = default;
        /**
         * @brief Destroy the Shootable object
         *
         */
        ~Shootable() = default;
        /**
         * @brief
         *
         * @param other
         * @return Shootable&
         */
        Shootable &operator=(const Shootable &other) = default;

        /** Getter */

        /** Setter */

        friend bool operator==(const Shootable &lhs, const Shootable &rhs)
        {
          static_cast<void>(lhs);
          static_cast<void>(rhs);
          return true;
        }
    };
} // namespace ecs

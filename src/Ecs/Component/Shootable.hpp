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
         * @param angle
         */
        Shootable(int angle = 0);
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
        /**
         * @brief Get the Angle object
         *
         * @return int
         */
        int getAngle() const;

        /** Setter */
        /**
         * @brief Set the Angle object
         *
         * @param angle
         */
        void setAngle(int angle);

      private:
        int _angle;
    };
} // namespace ecs

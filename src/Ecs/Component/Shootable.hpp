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
        /**
         * @brief Set the Angle object
         *
         * @param angle
         */
        void setAngle(int angle);
        bool getShooting() const;
        void setShooting(bool isShooting);
        bool getBeenInRange() const;
        void setBeenInRange(bool beenIn);

      private:
        int _angle;
        bool _shooting = false; // mettre dans le compo basic shot plus tard
        bool _been_in_range = false;


        friend bool operator==(const Shootable &lhs, const Shootable &rhs)
        {
          static_cast<void>(lhs);
          static_cast<void>(rhs);
          return true;
        }
    };
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** Velocity.hpp
** File description:
** Velocity.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class Velocity : public AComponent {
      public:
        Velocity(float x, float y);
        Velocity(const Velocity &other) = default;
        ~Velocity() = default;
        Velocity &operator=(const Velocity &other) = default;

        /* Getter */
        float getXVelocity() const;
        float getYVelocity() const;

        /* Setter */
        void setXVelocity(float x);
        void setYVelocity(float y);

      private:
        float _x;
        float _y;
    };
} // namespace component

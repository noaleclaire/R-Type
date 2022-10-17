/*
** EPITECH PROJECT, 2022
** Position.hpp
** File description:
** Position.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Position : public AComponent {
      public:
        Position() = default;
        Position(float x, float y, float xVelocity = 1, float yVelocity = 1);
        Position(const Position &other) = default;
        ~Position() = default;
        Position &operator=(const Position &other) = default;

        /* Getter */
        float getXPosition() const;
        float getYPosition() const;
        float getXVelocity() const;
        float getYVelocity() const;

        /* Setter */
        void setXPosition(float x);
        void setYPosition(float y);
        void setXVelocity(float x);
        void setYVelocity(float y);

      private:
        float _x;
        float _y;
        float _xVelocity;
        float _yVelocity;
    };
} // namespace ecs

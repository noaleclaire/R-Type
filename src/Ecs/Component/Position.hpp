/*
** EPITECH PROJECT, 2022
** Position.hpp
** File description:
** Position.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class Position : public AComponent {
      public:
        Position(float x, float y);
        Position(const Position &other) = default;
        ~Position() = default;
        Position &operator=(const Position &other) = default;

        /* Getter */
        float getXPosition() const;
        float getYPosition() const;

        /* Setter */
        void setXPosition(float x);
        void setYPosition(float y);

      private:
        float _x;
        float _y;
    };
} // namespace component

/*
** EPITECH PROJECT, 2022
** Position.cpp
** File description:
** Position.cpp
*/

#include "Position.hpp"

namespace component
{
    Position::Position(float x, float y) : _x(x), _y(y)
    {
    }

    /* Getter */
    float Position::getXPosition() const
    {
        return _x;
    }

    float Position::getYPosition() const
    {
        return _y;
    }

    /* Setter */
    void Position::setXPosition(float x)
    {
        _x = x;
    }

    void Position::setYPosition(float y)
    {
        _y = y;
    }
} // namespace component

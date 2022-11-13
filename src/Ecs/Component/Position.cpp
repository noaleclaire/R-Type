/*
** EPITECH PROJECT, 2022
** Position.cpp
** File description:
** Position.cpp
*/

#include "Position.hpp"

namespace ecs
{
    Position::Position(float x, float y, float xVelocity, float yVelocity) : _x(x), _y(y), _xVelocity(xVelocity), _yVelocity(yVelocity)
    {
    }

    /** Getter */
    float Position::getXPosition() const
    {
        return _x;
    }
    float Position::getYPosition() const
    {
        return _y;
    }

    float Position::getXVelocity() const
    {
        return _xVelocity;
    }

    float Position::getYVelocity() const
    {
        return _yVelocity;
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

    void Position::setXVelocity(float x)
    {
        _xVelocity = x;
    }

    void Position::setYVelocity(float y)
    {
        _yVelocity = y;
    }
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** Velocity.cpp
** File description:
** Velocity.cpp
*/

#include "Velocity.hpp"

namespace component
{
    Velocity::Velocity(float x, float y) : _x(x), _y(y)
    {
    }

    /* Getter */
    float Velocity::getXVelocity() const
    {
        return _x;
    }

    float Velocity::getYVelocity() const
    {
        return _y;
    }

    /* Setter */
    void Velocity::setXVelocity(float x)
    {
        _x = x;
    }

    void Velocity::setYVelocity(float y)
    {
        _y = y;
    }
} // namespace component

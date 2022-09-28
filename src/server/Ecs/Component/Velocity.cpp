/*
** EPITECH PROJECT, 2022
** Velocity.cpp
** File description:
** Velocity.cpp
*/

#include "Velocity.hpp"

component::Velocity::Velocity(float x, float y) : _x(x), _y(y)
{
}

/* Getter */
float component::Velocity::getXVelocity() const
{
    return _x;
}

float component::Velocity::getYVelocity() const
{
    return _y;
}

/* Setter */
void component::Velocity::setXVelocity(float x)
{
    _x = x;
}

void component::Velocity::setYVelocity(float y)
{
    _y = y;
}

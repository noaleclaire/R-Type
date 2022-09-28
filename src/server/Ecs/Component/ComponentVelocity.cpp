/*
** EPITECH PROJECT, 2022
** ComponentVelocity.cpp
** File description:
** ComponentVelocity.cpp
*/

#include "ComponentVelocity.hpp"

ComponentVelocity::ComponentVelocity(float x, float y) : _x(x), _y(y)
{
}

/* Getter */
float ComponentVelocity::getXVelocity() const
{
    return _x;
}

float ComponentVelocity::getYVelocity() const
{
    return _y;
}

/* Setter */
void ComponentVelocity::setXVelocity(float x)
{
    _x = x;
}

void ComponentVelocity::setYVelocity(float y)
{
    _y = y;
}

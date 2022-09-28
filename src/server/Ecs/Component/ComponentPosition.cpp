/*
** EPITECH PROJECT, 2022
** ComponentPosition.cpp
** File description:
** ComponentPosition.cpp
*/

#include "ComponentPosition.hpp"

ComponentPosition::ComponentPosition(float x, float y) : _x(x), _y(y)
{
}

/* Getter */
float ComponentPosition::getXPosition() const
{
    return _x;
}

float ComponentPosition::getYPosition() const
{
    return _y;
}

/* Setter */
void ComponentPosition::setXPosition(float x)
{
    _x = x;
}

void ComponentPosition::setYPosition(float y)
{
    _y = y;
}

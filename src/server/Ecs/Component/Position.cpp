/*
** EPITECH PROJECT, 2022
** Position.cpp
** File description:
** Position.cpp
*/

#include "Position.hpp"

component::Position::Position(float x, float y) : _x(x), _y(y)
{
}

/* Getter */
float component::Position::getXPosition() const
{
    return _x;
}

float component::Position::getYPosition() const
{
    return _y;
}

/* Setter */
void component::Position::setXPosition(float x)
{
    _x = x;
}

void component::Position::setYPosition(float y)
{
    _y = y;
}

/*
** EPITECH PROJECT, 2022
** Shootable.cpp
** File description:
** Shootable.cpp
*/

#include "Shootable.hpp"

component::Shootable::Shootable(int angle) : _angle(angle)
{
}

/* Getter */
int component::Shootable::getAngle() const
{
    return _angle;
}

/* Setter */
void component::Shootable::setAngle(int angle)
{
    _angle = angle;
}

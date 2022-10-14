/*
** EPITECH PROJECT, 2022
** Shootable.cpp
** File description:
** Shootable.cpp
*/

#include "Shootable.hpp"

namespace ecs
{
    Shootable::Shootable(int angle) : _angle(angle)
    {
    }

    /* Getter */
    int Shootable::getAngle() const
    {
        return _angle;
    }

    /* Setter */
    void Shootable::setAngle(int angle)
    {
        _angle = angle;
    }
} // namespace ecs

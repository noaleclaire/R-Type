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

    bool Shootable::getShooting() const
    {
        return _shooting;
    }

    bool Shootable::getBeenInRange() const
    {
        return _been_in_range;
    }


    /* Setter */
    void Shootable::setAngle(int angle)
    {
        _angle = angle;
    }

    void Shootable::setShooting(bool isShooting)
    {
        _shooting = isShooting;
    }

    void Shootable::setBeenInRange(bool beenIn)
    {
        _been_in_range = beenIn;
    }
} // namespace ecs

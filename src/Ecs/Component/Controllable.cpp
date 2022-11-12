/*
** EPITECH PROJECT, 2022
** Controllable.cpp
** File description:
** Controllable.cpp
*/

#include "Controllable.hpp"

namespace ecs
{
    Controllable::Controllable() : _z(false), _q(false), _s(false), _d(false), _space(false), _shift(false)
    {
    }

    void Controllable::setKey(std::string key, bool state)
    {
        if (key == "z")
            _z = state;
        if (key == "q")
            _q = state;
        if (key == "s")
            _s = state;
        if (key == "d")
            _d = state;
        if (key == "space")
            _space = state;
        if (key == "shift")
            _shift = state;
    }

    bool Controllable::getKey(std::string key) const
    {
        if (key == "z")
            return (_z);
        if (key == "q")
            return (_q);
        if (key == "s")
            return (_s);
        if (key == "d")
            return (_d);
        if (key == "space")
            return (_space);
        if (key == "shift")
            return (_shift);
        return (false);
    }
}

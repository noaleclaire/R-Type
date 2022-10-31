/*
** EPITECH PROJECT, 2022
** Controllable.cpp
** File description:
** Controllable.cpp
*/

#include "Controllable.hpp"

namespace ecs
{
    Controllable::Controllable(bool z, bool q, bool s, bool d) : _z(z), _q(q), _s(s), _d(d)
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
        return (false);
    }
}

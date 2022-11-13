/*
** EPITECH PROJECT, 2022
** Killable.cpp
** File description:
** Killable.cpp
*/

#include "Killable.hpp"

namespace ecs
{
    Killable::Killable(std::size_t life) : _life(life)
    {
    }

    std::size_t Killable::getLife() const
    {
        return (_life);
    }

    void Killable::setLife(std::size_t life)
    {
        _life = life;
    }

    void Killable::substractLife(int damage)
    {
        if (damage >= _life)
            _life = 0;
        else
            _life -= damage;
    }
}

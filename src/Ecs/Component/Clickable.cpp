/*
** EPITECH PROJECT, 2022
** Clickable.cpp
** File description:
** Clickable.cpp
*/

#include "Clickable.hpp"

namespace ecs
{
    Clickable::Clickable(Function function) : _function(function)
    {
    }

    /* Getter */
    Clickable::Function Clickable::getFunction() const
    {
        return (_function);
    }

    /* Setter */
    void Clickable::setFunction(Function function)
    {
        _function = function;
    }
} // namespace ecs

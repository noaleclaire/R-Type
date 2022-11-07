/*
** EPITECH PROJECT, 2022
** Link.cpp
** File description:
** Link.cpp
*/

#include "Link.hpp"

namespace ecs
{
    Link::Link(std::size_t entity) : _entity(entity)
    {
    }

    /* Getter */
    std::size_t Link::getLink() const
    {
        return (_entity);
    }

    /* Setter */
    void Link::setLink(std::size_t entity)
    {
        _entity = entity;
    }
} // namespace ecs

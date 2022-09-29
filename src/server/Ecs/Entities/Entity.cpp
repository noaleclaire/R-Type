/*
** EPITECH PROJECT, 2022
** Entity
** File description:
** Entity
*/

#include "Entity.hpp"

namespace ecs
{
    std::size_t Entity::_idCount = 0;

    Entity::Entity(std::optional<std::size_t> id)
    {
        if (id)
            _id = id.value();
        else {
            _id = _idCount;
            _idCount++;
        }
    }

    Entity::~Entity()
    {
    }

    Entity::operator std::size_t()
    {
        return (_id);
    }

    Entity::operator std::size_t() const
    {
        return (_id);
    }

    std::size_t Entity::get_id() const
    {
        return (_id);
    }

    void Entity::set_label(std::string label)
    {
        _label = label;
    }

    std::string Entity::get_label() const
    {
        return (_label);
    }
} // namespace ecs

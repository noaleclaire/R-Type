/*
** EPITECH PROJECT, 2022
** Type.cpp
** File description:
** Type.cpp
*/

#include "Type.hpp"

namespace ecs
{
    Type::Type(EntityTypes entityType, std::size_t entityID) : _entityType(entityType), _entityID(entityID)
    {
    }

    /* Getter */
    EntityTypes Type::getEntityType() const
    {
        return (_entityType);
    }
    std::size_t Type::getEntityID() const
    {
        return (_entityID);
    }

    /* Setter */
    void Type::setEntityType(EntityTypes entityType)
    {
        _entityType = entityType;
    }
    void Type::setEntityID(std::size_t entityID)
    {
        _entityID = entityID;
    }
} // namespace ecs

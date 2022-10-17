/*
** EPITECH PROJECT, 2022
** Type
** File description:
** Type
*/

#pragma once

#include <string>
#include "../Enum.hpp"
#include "AComponent.hpp"

namespace ecs
{
    class Type : public AComponent {
        public:
            Type() = default;
            Type(ecs::EntityTypes entityType, std::size_t entityID = 0);
            Type(const Type &other) = default;
            ~Type() = default;
            Type &operator=(const Type &other) = default;

            /* Getter */
            EntityTypes getEntityType() const;
            std::size_t getEntityID() const;

            /* Setter */
            void setEntityType(EntityTypes entityType);
            void setEntityID(std::size_t);
        private:
            EntityTypes _entityType;
            std::size_t _entityID;
    };
}

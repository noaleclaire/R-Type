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
        /**
         * @brief Construct a new Type object
         *
         */
        Type() = default;
        /**
         * @brief Construct a new Type object
         *
         * @param entityType
         * @param entityID
         */
        Type(ecs::EntityTypes entityType, std::size_t entityID = 0);
        /**
         * @brief Construct a new Type object
         *
         * @param other
         */
        Type(const Type &other) = default;
        /**
         * @brief Destroy the Type object
         *
         */
        ~Type() = default;
        /**
         * @brief
         *
         * @param other
         * @return Type&
         */
        Type &operator=(const Type &other) = default;

        /* Getter */
        /**
         * @brief Get the Entity Type object
         *
         * @return EntityTypes
         */
        EntityTypes getEntityType() const;
        /**
         * @brief Get the Entity I D object
         *
         * @return std::size_t
         */
        std::size_t getEntityID() const;

        /* Setter */
        /**
         * @brief Set the Entity Type object
         *
         * @param entityType
         */
        void setEntityType(EntityTypes entityType);
        /**
         * @brief Set the Entity I D object
         *
         */
        void setEntityID(std::size_t);

      private:
        EntityTypes _entityType;
        std::size_t _entityID;
    };
} // namespace ecs

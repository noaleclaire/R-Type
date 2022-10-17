/*
** EPITECH PROJECT, 2022
** Entity
** File description:
** Entity
*/

#pragma once
#include <iostream>
#include <optional>

namespace ecs
{
    class Entity {
      public:
        /**
         * @brief Construct a new Entity object
         *
         * @param id
         */
        explicit Entity(std::optional<std::size_t> id = std::nullopt);
        /**
         * @brief Destroy the Entity object
         *
         */
        ~Entity();
        /**
         * @brief
         *
         * @return std::size_t
         */
        operator std::size_t();
        /**
         * @brief
         *
         * @return std::size_t
         */
        operator std::size_t() const;
        /**
         * @brief Get the Id object
         *
         * @return std::size_t
         */
        std::size_t getId() const;
        static std::size_t _idCount;

      private:
        std::size_t _id;
    };
} // namespace ecs

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
        explicit Entity(std::optional<std::size_t> id = std::nullopt);
        ~Entity();
        operator std::size_t();
        operator std::size_t() const;

        std::size_t getId() const;
        static std::size_t _idCount;

      private:
        std::size_t _id;
    };
} // namespace ecs

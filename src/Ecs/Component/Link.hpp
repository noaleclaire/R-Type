/*
** EPITECH PROJECT, 2022
** Link
** File description:
** Link
*/

#pragma once

#include <string>
#include "AComponent.hpp"

namespace ecs
{
    class Link : public AComponent {
      public:
        /**
         * @brief Construct a new Link object
         *
         * @param Link
         */
        Link(std::size_t Link = 0);
        /**
         * @brief Construct a new Link object
         *
         * @param other
         */
        Link(const Link &other) = default;
        /**
         * @brief Destroy the Link object
         *
         */
        ~Link() = default;
        /**
         * @brief
         *
         * @param other
         * @return Link&
         */
        Link &operator=(const Link &other) = default;

        /* Getter */
        /**
         * @brief Get the Linked entity id
         *
         * @return int
         */
        std::size_t getLink() const;

        /* Setter */
        /**
         * @brief Set the Linked entity id
         *
         * @param entity
         */
        void setLink(std::size_t entity);

      private:
        std::size_t _entity;
    };
} // namespace ecs

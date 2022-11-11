/*
** EPITECH PROJECT, 2022
** TextBox.hpp
** File description:
** TextBox.hpp
*/

#pragma once

#include <string>
#include "AComponent.hpp"

namespace ecs
{
    class TextBox : public AComponent {
      public:
        /**
         * @brief Construct a new TextBox object
         *
         * @param max_size
         */
        TextBox(std::size_t max_size = 1);
        /**
         * @brief Construct a new TextBox object
         *
         * @param other
         */
        TextBox(const TextBox &other) = default;
        /**
         * @brief Destroy the TextBox object
         *
         */
        ~TextBox() = default;
        /**
         * @brief
         *
         * @param other
         * @return TextBox&
         */
        TextBox &operator=(const TextBox &other) = default;

        /* Getter */
        /**
         * @brief Return true if the TextBox is selected and false if not
         *
         * @return int
         */
        bool isSelected() const;

        /**
         * @brief Select the TextBox
         */
        void select();
        /**
         * @brief Unselect the TextBox
         */
        void unselect();
        /**
         * @brief Unselect the TextBox
         */
        std::size_t getMaxSize() const;
        /**
         * @brief Unselect the TextBox
         *
         * @param max_size
         */
        void setMaxSize(std::size_t max_size);

        friend bool operator==(const TextBox &lhs, const TextBox &rhs)
        {
            return lhs._selected == rhs._selected && lhs._max_size == rhs._max_size;
        }
      private:
        bool _selected;
        std::size_t _max_size;
    };
} // namespace ecs

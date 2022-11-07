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
         * @param TextBox
         */
        TextBox();
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

      private:
        bool _selected;
    };
} // namespace ecs

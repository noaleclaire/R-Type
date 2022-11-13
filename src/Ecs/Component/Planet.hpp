/*
** EPITECH PROJECT, 2022
** Planet
** File description:
** Planet
*/

#pragma once

#include "AComponent.hpp"
#include <string>

namespace ecs
{
    class Planet : public AComponent {
        public:
            /**
             * @brief Construct a new Planet object
             * 
             */
            Planet(std::size_t level_id = 1, bool selected = false) : _level_id(level_id), _selected(selected) {};
            /**
             * @brief Construct a new Planet object
             * 
             * @param other 
             */
            Planet(const Planet &other) = default;
            /**
             * @brief Destroy the Planet object
             * 
             */
            ~Planet() = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Planet& 
             */
            Planet &operator=(const Planet &other) = default;
            std::size_t getLevelID() const { return _level_id; };
            void select() { _selected = true; };
            void unselect() { _selected = false; };
            bool isSelected() const { return _selected; };

            friend bool operator==(const Planet &lhs, const Planet &rhs)
            {
                return lhs._level_id == rhs._level_id && lhs._selected == rhs._selected;
            }
        private:
            std::size_t _level_id;
            bool _selected;
    };
}

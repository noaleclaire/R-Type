/*
** EPITECH PROJECT, 2022
** Achievement.hpp
** File description:
** Achievement.hpp
*/

#pragma once
#include "AComponent.hpp"
#include <string>

namespace ecs
{
    class Achievement : public AComponent {
        public:
            /**
             * @brief Construct a new Achievement object
             * 
             */
            Achievement(std::size_t id = 0) : _id(id) {};
            /**
             * @brief Construct a new Achievement object
             * 
             * @param other 
             */
            Achievement(const Achievement &other) = default;
            /**
             * @brief Destroy the Achievement object
             * 
             */
            ~Achievement() = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Achievement& 
             */
            Achievement &operator=(const Achievement &other) = default;
            std::size_t getID() const { return _id; };

            friend bool operator==(const Achievement &lhs, const Achievement &rhs)
            {
                return lhs._id == rhs._id;
            }
        private:
            std::size_t _id;
    };
}

/*
** EPITECH PROJECT, 2022
** Killable.hpp
** File description:
** Killable.hpp
*/

#pragma once

#include "AComponent.hpp"
#include <string>

namespace ecs
{
    class Killable : public AComponent {
      public:
        /**
         * @brief Construct a new Killable object
         *
         * @param life
         */
        Killable(std::size_t life = 1);
        /**
         * @brief Construct a new Killable object
         *
         * @param other
         */
        Killable(const Killable &other) = default;
        /**
         * @brief Destroy the Killable object
         *
         */
        ~Killable() = default;
        /**
         * @brief
         *
         * @param other
         * @return Killable&
         */
        Killable &operator=(const Killable &other) = default;
        /**
         * @brief
         *
         * @return std::size_t
         */
        std::size_t getLife() const;
        /**
         * @brief
         *
         * @param life
         */
        void setLife(std::size_t life);
        /**
         * @brief
         *
         * @param damage
         */
        void substractLife(int damage);


        friend bool operator==(const Killable &lhs, const Killable &rhs)
        {
            static_cast<void>(lhs);
            static_cast<void>(rhs);
            return true;
        }
      private:
        std::size_t _life;
    };
} // namespace ecs

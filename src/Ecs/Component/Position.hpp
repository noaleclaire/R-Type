/*
** EPITECH PROJECT, 2022
** Position.hpp
** File description:
** Position.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Position : public AComponent {
      public:
        /**
         * @brief Construct a new Position object
         *
         */
        Position() = default;
        /**
         * @brief Construct a new Position object
         *
         * @param x
         * @param y
         * @param xVelocity
         * @param yVelocity
         */
        Position(float x, float y, float xVelocity = 1, float yVelocity = 1);
        /**
         * @brief Construct a new Position object
         *
         * @param other
         */
        Position(const Position &other) = default;
        /**
         * @brief Destroy the Position object
         *
         */
        ~Position() = default;
        /**
         * @brief
         *
         * @param other
         * @return Position&
         */
        Position &operator=(const Position &other) = default;

        /** Getter */
        /**
         * @brief
         *
         * @return float
         */
        float getXPosition() const;
        /**
         * @brief
         *
         * @return float
         */
        float getYPosition() const;
        /**
         * @brief
         *
         * @return float
         */
        float getXVelocity() const;
        /**
         * @brief
         *
         * @return float
         */
        float getYVelocity() const;

        /** Setter */
        /**
         * @brief
         *
         * @param x
         */
        void setXPosition(float x);
        /**
         * @brief
         *
         * @param y
         */
        void setYPosition(float y);
        /**
         * @brief
         *
         * @param x
         */
        void setXVelocity(float x);
        /**
         * @brief
         *
         * @param y
         */
        void setYVelocity(float y);

      private:
        float _x;
        float _y;
        float _xVelocity;
        float _yVelocity;
    };
} // namespace ecs

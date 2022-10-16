/*
** EPITECH PROJECT, 2022
** Position.hpp
** File description:
** Position.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class Position : public AComponent {
      public:
      /**
       * @brief Construct a new Position object
       * 
       * @param x 
       * @param y 
       */
        Position(float x, float y);
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

      private:
        float _x;
        float _y;
    };
} // namespace component

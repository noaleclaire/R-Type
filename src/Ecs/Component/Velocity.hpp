/*
** EPITECH PROJECT, 2022
** Velocity.hpp
** File description:
** Velocity.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace component
{
    class Velocity : public AComponent {
      public:
      /**
       * @brief Construct a new Velocity object
       * 
       * @param x 
       * @param y 
       */
        Velocity(float x, float y);
        /**
         * @brief Construct a new Velocity object
         * 
         * @param other 
         */
        Velocity(const Velocity &other) = default;
        /**
         * @brief Destroy the Velocity object
         * 
         */
        ~Velocity() = default;
        /**
         * @brief 
         * 
         * @param other 
         * @return Velocity& 
         */
        Velocity &operator=(const Velocity &other) = default;

        /* Getter */
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

        /* Setter */
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
    };
} // namespace component

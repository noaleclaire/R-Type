/*
** EPITECH PROJECT, 2022
** Rectangle.hpp
** File description:
** Rectangle.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Rectangle : public AComponent {
      public:
        /**
         * @brief Construct a new Rectangle object
         *
         */
        Rectangle() = default;
        /**
         * @brief Construct a new Rectangle object
         *
         * @param x
         * @param y
         * @param width
         * @param height
         */
        Rectangle(float x, float y, float width, float height);
        /**
         * @brief Construct a new Rectangle object
         *
         * @param other
         */
        Rectangle(const Rectangle &other) = default;
        /**
         * @brief Destroy the Rectangle object
         *
         */
        ~Rectangle() = default;
        /**
         * @brief
         *
         * @param other
         * @return Rectangle&
         */
        Rectangle &operator=(const Rectangle &other) = default;

        /* Getter */
        /**
         * @brief
         *
         * @return float
         */
        float getXRectangle() const;
        /**
         * @brief
         *
         * @return float
         */
        float getYRectangle() const;
        /**
         * @brief Get the Width Rectangle object
         *
         * @return float
         */
        float getWidthRectangle() const;
        /**
         * @brief Get the Height Rectangle object
         *
         * @return float
         */
        float getHeightRectangle() const;

        /* Setter */
        /**
         * @brief
         *
         * @param x
         */
        void setXRectangle(float x);
        /**
         * @brief
         *
         * @param y
         */
        void setYRectangle(float y);
        /**
         * @brief Set the Width Rectangle object
         *
         * @param width
         */
        void setWidthRectangle(float width);
        /**
         * @brief Set the Height Rectangle object
         *
         * @param height
         */
        void setHeightRectangle(float height);

      private:
        float _x;
        float _y;
        float _width;
        float _height;
    };
} // namespace ecs

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
        Rectangle(float x, float y, float width, float height);
        Rectangle(const Rectangle &other) = default;
        ~Rectangle() = default;
        Rectangle &operator=(const Rectangle &other) = default;

        /* Getter */
        float getXRectangle() const;
        float getYRectangle() const;
        float getWidthRectangle() const;
        float getHeightRectangle() const;

        /* Setter */
        void setXRectangle(float x);
        void setYRectangle(float y);
        void setWidthRectangle(float width);
        void setHeightRectangle(float height);

      private:
        float _x;
        float _y;
        float _width;
        float _height;
    };
} // namespace ecs

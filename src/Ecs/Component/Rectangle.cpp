/*
** EPITECH PROJECT, 2022
** Rectangle.cpp
** File description:
** Rectangle.cpp
*/

#include "Rectangle.hpp"

namespace ecs
{
    Rectangle::Rectangle(float x, float y, float width, float height) : _x(x), _y(y), _width(width), _height(height)
    {
    }

    /* Getter */
    float Rectangle::getXRectangle() const
    {
        return _x;
    }

    float Rectangle::getYRectangle() const
    {
        return _y;
    }

    float Rectangle::getWidthRectangle() const
    {
        return _width;
    }

    float Rectangle::getHeightRectangle() const
    {
        return _height;
    }

    /* Setter */
    void Rectangle::setXRectangle(float x)
    {
        _x = x;
    }

    void Rectangle::setYRectangle(float y)
    {
        _y = y;
    }

    void Rectangle::setWidthRectangle(float width)
    {
        _width = width;
    }

    void Rectangle::setHeightRectangle(float height)
    {
        _height = height;
    }

} // namespace ecs

/*
** EPITECH PROJECT, 2022
** ComponentPosition.hpp
** File description:
** ComponentPosition.hpp
*/

#pragma once

class ComponentPosition {
    public:
        ComponentPosition(float x, float y);
        ComponentPosition(const ComponentPosition &other) = default;
        ~ComponentPosition() = default;
        ComponentPosition &operator=(const ComponentPosition &other) = default;

        /* Getter */
        float getXPosition() const;
        float getYPosition() const;

        /* Setter */
        void setXPosition(float x);
        void setYPosition(float y);

    private:
        float _x;
        float _y;
};

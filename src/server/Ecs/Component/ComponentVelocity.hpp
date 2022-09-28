/*
** EPITECH PROJECT, 2022
** ComponentVelocity.hpp
** File description:
** ComponentVelocity.hpp
*/

#pragma once

class ComponentVelocity {
    public:
        ComponentVelocity(float x, float y);
        ComponentVelocity(const ComponentVelocity &other) = default;
        ~ComponentVelocity() = default;
        ComponentVelocity &operator=(const ComponentVelocity &other) = default;

        /* Getter */
        float getXVelocity() const;
        float getYVelocity() const;

        /* Setter */
        void setXVelocity(float x);
        void setYVelocity(float y);

    private:
        float _x;
        float _y;
};

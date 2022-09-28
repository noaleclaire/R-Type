/*
** EPITECH PROJECT, 2022
** Collider.hpp
** File description:
** Collider.hpp
*/

#pragma once

namespace component {
    class Collider {
        public:
            Collider() = default;
            Collider(const Collider &other) = default;
            ~Collider() = default;
            Collider &operator=(const Collider &other) = default;
    };
}

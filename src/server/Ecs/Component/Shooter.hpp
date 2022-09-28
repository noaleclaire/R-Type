/*
** EPITECH PROJECT, 2022
** Shooter.hpp
** File description:
** Shooter.hpp
*/

#pragma once

namespace component {
    class Shooter {
        public:
            Shooter();
            Shooter(const Shooter &other) = default;
            ~Shooter() = default;
            Shooter &operator=(const Shooter &other) = default;
    };
}

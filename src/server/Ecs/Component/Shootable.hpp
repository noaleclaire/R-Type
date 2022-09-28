/*
** EPITECH PROJECT, 2022
** Shootable.hpp
** File description:
** Shootable.hpp
*/

#pragma once

namespace component {
    class Shootable {
        public:
            Shootable(int angle);
            Shootable(const Shootable &other) = default;
            ~Shootable() = default;
            Shootable &operator=(const Shootable &other) = default;

            /* Getter */
            int getAngle() const;

            /* Setter */
            void setAngle(int angle);
        private:
            int _angle;
    };
};

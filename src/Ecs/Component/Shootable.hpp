/*
** EPITECH PROJECT, 2022
** Shootable.hpp
** File description:
** Shootable.hpp
*/

#pragma once

#include "IComponent.hpp"

namespace component
{
    class Shootable : public IComponent {
      public:
        Shootable(int angle);
        Shootable(const Shootable &other) = default;
        ~Shootable() override = default;
        Shootable &operator=(const Shootable &other) = default;

        /* Getter */
        int getAngle() const;

        /* Setter */
        void setAngle(int angle);

      private:
        int _angle;
    };
} // namespace component

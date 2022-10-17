/*
** EPITECH PROJECT, 2022
** Clickable.hpp
** File description:
** Clickable.hpp
*/

#pragma once

#include "AComponent.hpp"

namespace ecs
{
    class Clickable : public AComponent {
      public:
        enum Function { EXIT, TOGAME };
        Clickable(Function function = Function::EXIT);
        Clickable(const Clickable &other) = default;
        ~Clickable() = default;
        Clickable &operator=(const Clickable &other) = default;

        /* Getter */
        Function getFunction() const;

        /* Setter */
        void setFunction(Function function);

      private:
        Function _function;
    };
} // namespace ecs

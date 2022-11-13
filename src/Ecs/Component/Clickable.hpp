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
        enum Function { EXIT, TOGAME, TOSETTINGS, TOMENU, TOHTP, TOACHIEVEMENTS, QUITROOM, SWITCHROOMMODE, FILTERBYROOMMODEVERSUS, FILTERBYROOMMODECOOP, REFRESHFILTERSROOM,
                        CREATEPUBLICROOM, CREATEPRIVATEROOM, LISTROOM, JOINROOM, JOINROOMBYID,
                        CHANGEMUSICVOLUME, CHANGESFXVOLUME, SELECTTEXTBOX, CONFIRMPSEUDO, SELECTPLANET };
        /**
         * @brief Construct a new Clickable object
         *
         * @param function
         */
        Clickable(Function function = Function::EXIT);
        /**
         * @brief Construct a new Clickable object
         *
         * @param other
         */
        Clickable(const Clickable &other) = default;
        /**
         * @brief Destroy the Clickable object
         *
         */
        ~Clickable() = default;
        /**
         * @brief
         *
         * @param other
         * @return Clickable&
         */
        Clickable &operator=(const Clickable &other) = default;

        /* Getter */
        /**
         * @brief Get the Function object
         *
         * @return Function
         */
        Function getFunction() const;

        /* Setter */
        /**
         * @brief Set the Function object
         *
         * @param function
         */
        void setFunction(Function function);

        friend bool operator==(const Clickable &lhs, const Clickable &rhs)
        {
            return lhs._function == rhs._function;
        }
      private:
        Function _function;
    };
} // namespace ecs

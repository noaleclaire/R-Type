/*
** EPITECH PROJECT, 2022
** Controllable.hpp
** File description:
** Controllable.hpp
*/

#pragma once

#include "AComponent.hpp"
#include <string>

namespace ecs
{
    class Controllable : public AComponent {
      public:
        /**
         * @brief Construct a new Controllable object
         *
         * @param z
         * @param q
         * @param s
         * @param d
         */
        Controllable(bool z = false, bool q = false, bool s = false, bool d =false);
        /**
         * @brief Construct a new Controllable object
         *
         * @param other
         */
        Controllable(const Controllable &other) = default;
        /**
         * @brief Destroy the Controllable object
         *
         */
        ~Controllable() = default;
        /**
         * @brief
         *
         * @param other
         * @return Controllable&
         */
        Controllable &operator=(const Controllable &other) = default;
        /**
         * @brief Set the Key object
         * 
         * @param key 
         * @param state 
         */
        void setKey(std::string key, bool state);
        /**
         * @brief Get the Key object
         * 
         * @param key 
         * @return true 
         * @return false 
         */
        bool getKey(std::string key) const;

      private:
        bool _z;
        bool _q;
        bool _s;
        bool _d;
    };
} // namespace ecs

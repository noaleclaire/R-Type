/*
** EPITECH PROJECT, 2022
** Shooter.hpp
** File description:
** Shooter.hpp
*/

#pragma once

#include "AComponent.hpp"
#include <chrono>

namespace ecs
{
    class Shooter : public AComponent {
      public:
        /**
         * @brief Construct a new Shooter object
         *
         */
        Shooter() : _lastShot(std::chrono::system_clock::now()) {};
        /**
         * @brief Construct a new Shooter object
         *
         * @param other
         */
        Shooter(const Shooter &other) = default;
        /**
         * @brief Destroy the Shooter object
         *
         */
        ~Shooter() = default;
        /**
         * @brief
         *
         * @param other
         * @return Shooter&
         */
        Shooter &operator=(const Shooter &other) = default;
        /**
         * @brief Get the time point of the last shot
         *
         * @return std::chrono::time_point<std::chrono::system_clock>
         */
        std::chrono::time_point<std::chrono::system_clock> getLastShot()
        {
            return (_lastShot);
        }
        /**
         * @brief Set the time point of the last shot to the given time point
         *
         * @param lastShot
         */
        void setLastShot(std::chrono::time_point<std::chrono::system_clock> lastShot = std::chrono::system_clock::now()) { _lastShot = lastShot; };

        friend bool operator==(const Shooter &lhs, const Shooter &rhs)
        {
            static_cast<void>(lhs);
            static_cast<void>(rhs);
            return true;
        }
      private:
        std::chrono::time_point<std::chrono::system_clock> _lastShot;
    };
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** Shooter.hpp
** File description:
** Shooter.hpp
*/

#pragma once

#include "AComponent.hpp"
#include "Ammo.hpp"
#include <chrono>

namespace ecs
{
    class Shooter : public AComponent {
      public:
        /**
         * @brief Construct a new Shooter object
         *
         * @param ammoType
         */
        Shooter(Ammo::AmmoType ammoType = Ammo::AmmoType::CLASSIC) : _lastShot(std::chrono::system_clock::now()), _ammoType(ammoType) {};
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
        std::chrono::time_point<std::chrono::system_clock> getLastShot() { return (_lastShot); }
        /**
         * @brief Set the time point of the last shot to the given time point
         *
         * @param lastShot
         */
        void setLastShot(std::chrono::time_point<std::chrono::system_clock> lastShot = std::chrono::system_clock::now()) { _lastShot = lastShot; };
        /**
         * @brief Get the selected ammo type
         *
         * @return Ammo::AmmoType
         */
        Ammo::AmmoType getAmmoType() { return (_ammoType); }
        /**
         * @brief Set the selected ammo type
         *
         * @param ammoType
         */
        void setAmmoType(Ammo::AmmoType ammoType) { _ammoType = ammoType; };

        friend bool operator==(const Shooter &lhs, const Shooter &rhs)
        {
            return lhs._lastShot == rhs._lastShot && lhs._ammoType == rhs._ammoType;
        }
      private:
        std::chrono::time_point<std::chrono::system_clock> _lastShot;
        Ammo::AmmoType _ammoType;
    };
} // namespace ecs

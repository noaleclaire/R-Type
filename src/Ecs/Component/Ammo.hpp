/*
** EPITECH PROJECT, 2022
** Ammo
** File description:
** Ammo
*/

#pragma once

#include "AComponent.hpp"
#include <chrono>
#include <unordered_map>

namespace ecs
{
    class Ammo : public AComponent {
      public:
        enum AmmoType { CLASSIC, CLASSIC2 };
        struct AmmoAttributes {
            int die_time = -1;//time after the shot died (if needed)
            int damage = 0;//damage dealt by the shot
            int shot_rate = 0;//time (ms) before each shot
            float velocity_x = 0;
            float velocity_y = 0;
            bool die_after_collide = true;//true if the shot die after a collision, false if not
        };
        static std::unordered_map<AmmoType, AmmoAttributes> ammoAttributesByType;

        /**
         * @brief Construct a new Ammo object
         *
         */
        Ammo(AmmoType type = CLASSIC);
        /**
         * @brief Construct a new Ammo object
         *
         * @param other
         */
        Ammo(const Ammo &other) = default;
        /**
         * @brief Destroy the Ammo object
         *
         */
        ~Ammo() = default;
        /**
         * @brief
         *
         * @param other
         * @return Ammo&
         */
        Ammo &operator=(const Ammo &other) = default;
        /**
         * @brief Get if the shot is off action
         *
         * @param posX
         * @return bool
         */
        bool isDead(float posX, float width) const;
        /**
         * @brief Get if the shot is off action
         *
         * @return bool
         */
        bool isDead() const;
        /**
         * @brief Get the velocity of the ammo
         *
         * @return std::pair<float, float>
         */
        std::pair<float, float> getVelocity() const;
        /**
         * @brief Get the damage of the ammo
         *
         * @return int
         */
        int getDamage() const;
        /**
         * @brief Get the shot rate of the ammo
         *
         * @return int
         */
        int getShotRate() const;
        /**
         * @brief Get if the shot die after collide an entity
         *
         * @return bool
         */
        bool dieAfterCollide() const;

        friend bool operator==(const Ammo &lhs, const Ammo &rhs)
        {
            return lhs._type == rhs._type;
        }
      private:
        AmmoType _type;
        std::chrono::time_point<std::chrono::system_clock> _spawn;
    };
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** Ammo
** File description:
** Ammo
*/

#include "Ammo.hpp"

#include <iostream>

namespace ecs
{
    std::unordered_map<Ammo::AmmoType, Ammo::AmmoAttributes> Ammo::ammoAttributesByType = {{Ammo::AmmoType::CLASSIC, {-1, 10, 500, 1000, 0, true}},
                                                                                            {Ammo::AmmoType::BEAM, {3000, 1, 5000, 0, 0, false}}};

    Ammo::Ammo(Ammo::AmmoType type) : _type(type), _spawn(std::chrono::system_clock::now())
    {
    }

    bool Ammo::isDead(float posX, float width) const
    {
        if (posX >= 1280 || posX + width <= 0)
            return true;
        return false;
    }

    bool Ammo::isDead() const
    {
        if (ammoAttributesByType.at(_type).die_time == -1)
            return false;
        if ((std::chrono::system_clock::now() - _spawn) >= std::chrono::milliseconds(ammoAttributesByType.at(_type).die_time))
            return true;
        return false;
    }

    std::pair<float, float> Ammo::getVelocity() const
    {
        return (std::make_pair(ammoAttributesByType.at(_type).velocity_x, ammoAttributesByType.at(_type).velocity_y));
    }

    int Ammo::getDamage() const
    {
        return (ammoAttributesByType.at(_type).damage);
    }

    int Ammo::getShotRate() const
    {
        return (ammoAttributesByType.at(_type).shot_rate);
    }

    bool Ammo::dieAfterCollide() const
    {
        return (ammoAttributesByType.at(_type).die_after_collide);
    }
}

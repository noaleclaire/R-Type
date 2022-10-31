/*
** EPITECH PROJECT, 2022
** Settings
** File description:
** Settings
*/

#pragma once
#include "ScenesInitializer.hpp"

class Settings : public ScenesInitializer {
    public:
        Settings() = default;
        ~Settings() = default;

        static void initScene(ecs::Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical)
        {
            registry.setActualScene(ecs::Scenes::SETTINGS);
        }
};

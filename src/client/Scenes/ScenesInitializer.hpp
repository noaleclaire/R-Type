/*
** EPITECH PROJECT, 2022
** ScenesInitializer
** File description:
** ScenesInitializer
*/

#pragma once
#include <vector>
#include "../Sfml/Graphical.hpp"
#include "../Sfml/SpritesManager.hpp"
#include "../../Ecs/Registry.hpp"
#include "../../Ecs/Factory.hpp"

class ScenesInitializer {
    public:
        ScenesInitializer();
        ScenesInitializer(const ScenesInitializer &other) = delete;
        ~ScenesInitializer();
        ScenesInitializer &operator=(const ScenesInitializer &other) = delete;

    protected:
    private:
};

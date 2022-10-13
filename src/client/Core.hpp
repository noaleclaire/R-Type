/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#pragma once
#include "../Ecs/Registry.hpp"
#include "Sfml/SpritesManager.hpp"
#include "Sfml/Graphical.hpp"
#include <atomic>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include "../Network/shared.hpp"


class Core {
    public:
        Core();
        ~Core();

    protected:
    private:
        void _initMenu();
        void _initSettings();
        void _initWin();
        void _initLoose();
        void _gameLoop();

        ecs::Registry _registry;
        graphics::SpritesManager _sprites_manager;
        graphics::Graphical _graphical;
};

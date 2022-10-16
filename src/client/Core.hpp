/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#pragma once
#include "Sfml/Graphical.hpp"
#include <iostream>
#include <string>
#include <unordered_map>


class Core {
    public:
        Core();
        ~Core();

    protected:
    private:
        void _initMenu();
        void _initSettings();
        void _gameLoop();

        ecs::Registry _registry;
        SpritesManager _sprites_manager;
        graphics::Graphical _graphical;
};

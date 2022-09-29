/*
** EPITECH PROJECT, 2022
** net
** File description:
** net
*/

#pragma once

#include <cstdio>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Network/shared.hpp"

class window
{
    public:
        window();
        ~window();
        int launch_window(shared_memory_t *s);
    private:
};

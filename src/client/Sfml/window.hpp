/*
** EPITECH PROJECT, 2022
** net
** File description:
** net
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include "../Network/shared.hpp"

class window {
  public:
    window();
    ~window();
    int launch_window(shared_memory_t *s);

  private:
};

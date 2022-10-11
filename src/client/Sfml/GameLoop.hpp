
/*
** EPITECH PROJECT, 2022
** GameLoop
** File description:
** GameLoop
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <atomic>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include "../Network/shared.hpp"

class GameLoop {
  public:
    GameLoop();
    ~GameLoop();

    void createWindow(int height, int width, std::string name = "Window");
    int launchLoop(std::shared_ptr<void()> s);

  private:
    sf::RenderWindow _window;
};

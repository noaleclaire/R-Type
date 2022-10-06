
/*
** EPITECH PROJECT, 2022
** net
** File description:
** net
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

class window {
  public:
    window();
    ~window();
    int launch_window(std::shared_ptr<void()> s);

  private:
};

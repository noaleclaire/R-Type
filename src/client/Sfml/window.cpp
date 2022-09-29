/*
** EPITECH PROJECT, 2022
** ecs
** File description:
** ecs
*/

#include "window.hpp"

window::window()
{
}

window::~window()
{
}

int window::launch_window(shared_memory_t *s)
{
    sf::RenderWindow _window(sf::VideoMode(520, 800), "My _window");

    _window.setFramerateLimit(60);
    while (_window.isOpen()) {
       sf::Event event;
       while (_window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               _window.close();
       }
       _window.setActive();
       _window.display();
    }
    return 0;
}
/*
** EPITECH PROJECT, 2022
** GameLoop
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::createWindow(int height, int width, std::string name)
{
    _window.create(sf::VideoMode(height, width), name);
}

int GameLoop::launchLoop(std::shared_ptr<void()> s)
{
    (void)s;
    sf::RenderWindow _window(sf::VideoMode(520, 800), "My _window");

    createWindow(520, 800);
    _window.setFramerateLimit(60);
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.setActive();
        _window.display();
    }
    return 0;
}

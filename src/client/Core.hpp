/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#pragma once
#include <iostream>
#include <string>
#include "Network/CustomClient.hpp"
#include "Sfml/Graphical.hpp"
#include <unordered_map>

class Core {
  public:
    Core(boost::asio::io_context &io_context, std::string host, unsigned short server_port);
    ~Core();

    static ecs::Scenes actual_scene;

  protected:
  private:
    void _initMenu();
    void _initSettings();
    void _switchScenes();
    void _gameLoop();
    void _gameStop();

    boost::asio::io_context &_io_context;
    CustomClient _client;
    std::thread _client_thread;
    ecs::Registry _unique_registry;
    ecs::Registry _shared_registry;
    ecs::Registry *_actual_registry;
    void _setActualRegistry(ecs::Scenes _scene);
    SpritesManager _sprites_manager;
    graphics::Graphical _graphical;
    ecs::Scenes _last_scene = ecs::Scenes::MENU;
};

/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Network/CustomClient.hpp"
#include "UserInfo.hpp"

class Core {
  public:
    Core(boost::asio::io_context &io_context, std::string host, unsigned short server_port);
    Core(const Core &other) = delete;
    ~Core();
    Core &operator=(const Core &other) = delete;

    static ecs::Scenes actual_scene;

  protected:
  private:
    void _handleUserPseudo();
    void _setActualRegistry();
    void _switchScenes();
    void _switchScenesCreateRoom();
    void _switchScenesJoinRoom();
    void _gameLoop();
    void _gameStop();

    boost::asio::io_context &_io_context;
    UserInfo _user_info;
    CustomClient _client;
    std::thread _client_thread;
    ecs::Registry _unique_registry;
    ecs::Registry _shared_registry;
    ecs::Registry *_actual_registry;
    SpritesManager _sprites_manager;
    graphics::Graphical _graphical;
    ecs::Scenes _last_scene = ecs::Scenes::MENU;
};

/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#include <filesystem>
#include "Core.hpp"
#include "../Ecs/Systems/Systems.hpp"
#include "../Utilities/ParserYaml.hpp"
#include "Exceptions/Exception.hpp"
#include "Scenes/Menu.hpp"
#include "Scenes/Settings.hpp"
#include "Scenes/ListRoom.hpp"

ecs::Scenes Core::actual_scene = ecs::Scenes::MENU;

Core::Core(boost::asio::io_context &io_context, std::string host, unsigned short server_port) : _io_context(io_context), _client(io_context, host, server_port)
{
    ParserYaml::parseYaml(_sprites_manager, std::filesystem::current_path() / "assets/sprites/sprites_config.yaml");
    // _sprites_manager.printSpritesData();

    _graphical.addAllTextures(_sprites_manager);
    Menu::initScene(_unique_registry, _sprites_manager, _graphical);
    Settings::initScene(_unique_registry, _sprites_manager, _graphical);
    ListRoom::initScene(_unique_registry, _sprites_manager, _graphical);

    _actual_registry = &_unique_registry;
    _client.registry = &_shared_registry;
    _client.non_shareable_registry = &_unique_registry;
    _client_thread = std::thread(bind(&boost::asio::io_context::run, boost::ref(io_context)));
    _client.pingServer();

    _client.graphical = &_graphical;
    _client.sprites_manager = &_sprites_manager;

    _gameLoop();
}

Core::~Core()
{
}

void Core::_setActualRegistry()
{
    if (Core::actual_scene == ecs::Scenes::MENU || Core::actual_scene == ecs::Scenes::SETTINGS || Core::actual_scene == ecs::Scenes::LISTROOM)
        _actual_registry = &_unique_registry;
    else
        _actual_registry = &_shared_registry;
}

void Core::_switchScenesCreateRoom()
{
    if (_last_scene != ecs::Scenes::PUBLICROOM && Core::actual_scene == ecs::Scenes::PUBLICROOM) {
        _client.createPublicRoom();
        std::this_thread::sleep_for(std::chrono::milliseconds(205)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = ecs::Scenes::MENU;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualSpritesEntities(Core::actual_scene);
        } else
            Core::actual_scene = _actual_registry->getActualScene();
    }
    if (_last_scene != ecs::Scenes::PRIVATEROOM && Core::actual_scene == ecs::Scenes::PRIVATEROOM) {
        _client.createPrivateRoom();
        std::this_thread::sleep_for(std::chrono::milliseconds(205)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = ecs::Scenes::MENU;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualSpritesEntities(Core::actual_scene);
        } else
            Core::actual_scene = _actual_registry->getActualScene();
    }
}

void Core::_switchScenesJoinRoom()
{
    if ((_last_scene != ecs::Scenes::ROOM1 && Core::actual_scene == ecs::Scenes::ROOM1) ||
    (_last_scene != ecs::Scenes::ROOM2 && Core::actual_scene == ecs::Scenes::ROOM2) ||
    (_last_scene != ecs::Scenes::ROOM3 && Core::actual_scene == ecs::Scenes::ROOM3) ||
    (_last_scene != ecs::Scenes::ROOM4 && Core::actual_scene == ecs::Scenes::ROOM4)) {
        _client.joinRoom(Core::actual_scene);
        std::this_thread::sleep_for(std::chrono::milliseconds(205)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = ecs::Scenes::LISTROOM;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualSpritesEntities(Core::actual_scene);
        }
    }
    if (_last_scene != ecs::Scenes::JOINROOMBYID && Core::actual_scene == ecs::Scenes::JOINROOMBYID) {
        _client.joinRoomById(0); // change id_room !!!
        std::this_thread::sleep_for(std::chrono::milliseconds(205)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = ecs::Scenes::LISTROOM;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualSpritesEntities(Core::actual_scene);
        } else
            Core::actual_scene = _actual_registry->getActualScene();
    }
}

void Core::_switchScenes()
{
    if (_last_scene != ecs::Scenes::MENU && Core::actual_scene == ecs::Scenes::MENU)
        _actual_registry->setActualScene(Core::actual_scene);
    if (_last_scene != ecs::Scenes::SETTINGS && Core::actual_scene == ecs::Scenes::SETTINGS)
        _actual_registry->setActualScene(Core::actual_scene);
    if (_last_scene != ecs::Scenes::LISTROOM && Core::actual_scene == ecs::Scenes::LISTROOM) {
        _actual_registry->setActualScene(Core::actual_scene);
        _client.initListRoom();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
    }

    _switchScenesJoinRoom();
    _switchScenesCreateRoom();

    if (_last_scene != ecs::Scenes::GAME && Core::actual_scene == ecs::Scenes::GAME) {
        _actual_registry->setActualScene(Core::actual_scene);
        _client.initGame();
        std::this_thread::sleep_for(std::chrono::milliseconds(205)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
    }

    _last_scene = Core::actual_scene;
}

void Core::_gameStop()
{
    _client.clientDisconnect();
    std::this_thread::sleep_for(std::chrono::milliseconds(DISCONNECTION_TIME));
    _io_context.stop();
    if (_client_thread.joinable())
        _client_thread.join();
}

void Core::_gameLoop()
{
    _graphical.getWindow().create(_graphical.getVideoMode(), ""); // sf::Style::None
    _graphical.getWindow().setFramerateLimit(60);
    _actual_registry->setActualScene(actual_scene);
    try {
        while (_graphical.getWindow().isOpen()) {
            _graphical.getWorldClock();
            _setActualRegistry();
            _graphical.setActualSpritesEntities(Core::actual_scene);
            _switchScenes();
            _graphical.handleEvents(*_actual_registry);
            ecs::Systems::Parallaxe(*_actual_registry, _actual_registry->getComponents<ecs::Type>());
            ecs::Systems::Position(*_actual_registry, _actual_registry->getComponents<ecs::Position>(), _graphical);
            _graphical.draw(*_actual_registry);
        }
    } catch (const Exception &e) {
        _gameStop();
        throw e;
    } catch (std::exception &e) {
        _gameStop();
        throw e;
    }
    _gameStop();
}

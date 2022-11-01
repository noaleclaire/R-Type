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

ecs::Scenes Core::actual_scene = ecs::Scenes::MENU;

Core::Core(boost::asio::io_context &io_context, std::string host, unsigned short server_port) : _io_context(io_context), _client(io_context, host, server_port)
{
    ParserYaml::parseYaml(_sprites_manager, std::filesystem::current_path() / "assets/sprites/sprites_config.yaml");
    // _sprites_manager.printSpritesData();

    _graphical.addAllTextures(_sprites_manager);
    Menu::initScene(_unique_registry, _sprites_manager, _graphical);
    Settings::initScene(_unique_registry, _sprites_manager, _graphical);

    _actual_registry = &_unique_registry;
    _client.registry = &_shared_registry;
    _client_thread = std::thread(bind(&boost::asio::io_context::run, boost::ref(io_context)));
    _client.pingServer();

    _client.graphical = &_graphical;
    _client.sprites_manager = &_sprites_manager;

    _gameLoop();
}

Core::~Core()
{
}

void Core::_setActualRegistry(ecs::Scenes _scene)
{
    if (_scene == ecs::Scenes::MENU || _scene == ecs::Scenes::SETTINGS)
        _actual_registry = &_unique_registry;
    else
        _actual_registry = &_shared_registry;
}

void Core::_switchScenes()
{
    if (_last_scene != ecs::Scenes::MENU && Core::actual_scene == ecs::Scenes::MENU)
        _actual_registry->setActualScene(Core::actual_scene);
    if (_last_scene != ecs::Scenes::SETTINGS && Core::actual_scene == ecs::Scenes::SETTINGS)
        _actual_registry->setActualScene(Core::actual_scene);

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
            _setActualRegistry(Core::actual_scene);
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

/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#include "Core.hpp"
#include <chrono>
#include <filesystem>
#include "../Ecs/Factory.hpp"
#include "../Ecs/Systems/Systems.hpp"
#include "../Utilities/ParserYaml.hpp"
#include "Exceptions/Exception.hpp"

using namespace std::chrono_literals;

ecs::Scenes Core::actual_scene = ecs::Scenes::MENU;

Core::Core(boost::asio::io_context &io_context, std::string host, unsigned short server_port) : _io_context(io_context), _client(io_context, host, server_port)
{
    _client.registry = &_shared_registry;
    _actual_registry = &_unique_registry;
    _client_thread = std::thread(bind(&boost::asio::io_context::run, boost::ref(io_context)));
    _client.pingServer();

    ParserYaml::parseYaml(_sprites_manager, std::filesystem::current_path() / "assets/sprites/sprites_config.yaml");
    // _sprites_manager.printSpritesData();

    _graphical.addAllTextures(_sprites_manager);

    _client.graphical = &_graphical;
    _client.sprites_manager = &_sprites_manager;

    _initMenu();
    _initSettings();

    _gameLoop();
}

Core::~Core()
{
}

void Core::_initMenu()
{
    std::vector<float> rect;
    std::size_t entity;

    _unique_registry.setActualScene(ecs::Scenes::MENU);

    rect = _sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
    entity = ecs::Factory::createEntity(_unique_registry, ecs::EntityTypes::BACKGROUND, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1);
    _graphical.addSprite(entity, _sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);

    rect = _sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 0, 0);
    entity = ecs::Factory::createEntity(_unique_registry, ecs::EntityTypes::BUTTON, 480, 200, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
    _unique_registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOGAME);
    _graphical.addSprite(entity, _sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 0), rect);
}

void Core::_initSettings()
{
    _unique_registry.setActualScene(ecs::Scenes::SETTINGS);
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
    if (_last_scene != ecs::Scenes::GAME && Core::actual_scene == ecs::Scenes::GAME) {
        _client.initGame();
        std::this_thread::sleep_for(500ms);
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
            _setActualRegistry(Core::actual_scene);
            _graphical.setActualSpritesEntities(Core::actual_scene);
            _switchScenes();
            _graphical.handleEvents(*_actual_registry);
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

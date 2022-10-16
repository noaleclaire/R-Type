/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#include "Core.hpp"
#include <filesystem>
#include "../Ecs/Factory.hpp"
#include "../Ecs/Systems/Systems.hpp"
#include "../Utilities/ParserYaml.hpp"

Core::Core()
{
    ParserYaml::parseYaml(_sprites_manager, std::filesystem::current_path() / "assets/sprites/sprites_config.yaml");
    _sprites_manager.printSpritesData();

    _graphical.addAllTextures(_sprites_manager);

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

    _registry.setActualScene(ecs::Scenes::MENU);

    rect = _sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0);
    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::BACKGROUND, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1);
    _graphical.addSprite(entity, _sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);

    rect = _sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 0);
    entity = ecs::Factory::createEntity(_registry, ecs::EntityTypes::BUTTON, 480, 200, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
    _graphical.addSprite(entity, _sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 0), rect);
}

void Core::_initSettings()
{
    _registry.setActualScene(ecs::Scenes::SETTINGS);
}

void Core::_gameLoop()
{
    _graphical.getWindow().create(_graphical.getVideoMode(), ""); //sf::Style::None
    _graphical.getWindow().setFramerateLimit(60);
    _registry.setActualScene(ecs::Scenes::MENU);
    while (_graphical.getWindow().isOpen()) {
        _graphical.handleEvents(_registry);
        ecs::Systems::Position(_registry, _registry.getComponents<ecs::Position>(), _graphical);
        _graphical.draw(_registry);
    }
}

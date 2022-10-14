/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#include <filesystem>
#include "Core.hpp"
#include "../Ecs/Factory.hpp"
#include "../Utilities/ParserYaml.hpp"
#include "../Ecs/Systems/Systems.hpp"

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
}

void Core::_initSettings()
{
    _registry.setActualScene(ecs::Scenes::SETTINGS);
}

void Core::_gameLoop()
{
    std::shared_ptr<void()> s;
    (void)s;

    _graphical.getWindow().create(_graphical.getVideoMode(), "", sf::Style::None);
    _graphical.getWindow().setFramerateLimit(60);
    _registry.setActualScene(ecs::Scenes::MENU);
    while (_graphical.getWindow().isOpen()) {
        while (_graphical.getWindow().pollEvent(_graphical.getEvent())) {
            if (_graphical.getEvent().type == sf::Event::Closed)
                _graphical.getWindow().close();
        }
        _graphical.getWindow().clear();
        ecs::Systems::Drawable(_registry, _registry.getComponents<ecs::Drawable>(), _graphical);
        _graphical.getWindow().display();
    }
}

/*
** EPITECH PROJECT, 2022
** Settings
** File description:
** Settings
*/

#pragma once
#include "ScenesInitializer.hpp"

class Settings : public ScenesInitializer {
    public:
        Settings() = default;
        ~Settings() = default;

        static void initScene(ecs::Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical)
        {
            std::vector<float> rect;
            std::size_t entity;

            registry.setActualScene(ecs::Scenes::SETTINGS);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 1280, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 1, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 500, 0, -60, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 1);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 1), rect);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 10, 10, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 0), rect);

            rect = {700, 300, 200, 80};
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::TEST));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            graphical.addRectangleShape(entity, rect, sf::Color::Green);
        }
};

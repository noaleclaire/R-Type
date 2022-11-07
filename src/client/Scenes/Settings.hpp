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

            //Backgrounds
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
                //Parallaxe
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 1280, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 10, 10, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 0), rect);

            rect = {700, 300, 200, 80};
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::CHANGEVOLUME));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Green);

            rect = {700, 300, 20, 80};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Red);

            rect = {775, 325, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "10%", rect);

            //TextBox
            rect = {300, 100, 200, 80};
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::SELECTTEXTBOX));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            registry.addComponent<ecs::TextBox>(registry.getEntityById(entity), ecs::TextBox(PSEUDO_SIZE));
            graphical.addRectangleShape(entity, rect, sf::Color::Green);
            graphical.setRectangleShapeOutline(entity, sf::Color::Red, 5);

            rect = {310, 125, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "", rect);
        }
};

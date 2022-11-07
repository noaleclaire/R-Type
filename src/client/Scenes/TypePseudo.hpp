/*
** EPITECH PROJECT, 2022
** TypePseudo
** File description:
** TypePseudo
*/

#pragma once
#include "ScenesInitializer.hpp"

class TypePseudo : public ScenesInitializer {
    public:
        TypePseudo() = default;
        ~TypePseudo() = default;

        static void initScene(ecs::Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical)
        {
            //NE PAS METTRE 2 TEXTES DANS CETTE SCENE
            std::vector<float> rect;
            std::size_t entity;
            std::size_t btn_y = 350;

            registry.setActualScene(ecs::Scenes::TYPEPSEUDO);

            //Backgrounds
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
                //Parallaxe
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, rect.at(2), 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            //Logo
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 1, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 100, 75, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 1), rect);
            //TextBox
            rect = {600, 100, 200, 80};
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
                //Text in
            rect = {610, 125, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "", rect);
            //Buttons
                //join game
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 5, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 928 - rect.at(2), btn_y, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 5), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            btn_y += rect.at(3) + 5;
                //exit
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 3, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 928 - rect.at(2), btn_y, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::EXIT);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 3), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
        };
};

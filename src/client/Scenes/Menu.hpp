/*
** EPITECH PROJECT, 2022
** Menu
** File description:
** Menu
*/

#pragma once
#include "ScenesInitializer.hpp"

class Menu : public ScenesInitializer {
    public:
        Menu() = default;
        ~Menu() = default;

        static void initScene(ecs::Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical)
        {
            std::vector<float> rect;
            std::size_t entity;
            std::size_t btn_y = 350;

            registry.setActualScene(ecs::Scenes::MENU);

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
            //Buttons
                //join game
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 4, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 1280 - rect.at(2), btn_y, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 4, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::LISTROOM);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 4), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            btn_y += rect.at(3) + 5;
                //create public game
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 1, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 1280 - rect.at(2) - 186, btn_y, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::CREATEPUBLICROOM);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 1), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
                //create private game
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 1280 - rect.at(2), btn_y, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 0, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::CREATEPRIVATEROOM);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 0), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            btn_y += rect.at(3) + 5;
                //how to play
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 3, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 1280 - rect.at(2), btn_y, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOSETTINGS);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 3), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            btn_y += rect.at(3) + 5;
                //settings
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 5, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 1280 - rect.at(2), btn_y, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 5, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOSETTINGS);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 5), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            btn_y += rect.at(3) + 5;
                //exit
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 2, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 1280 - rect.at(2), btn_y, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::EXIT);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 2), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
        };
};

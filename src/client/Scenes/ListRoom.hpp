/*
** EPITECH PROJECT, 2022
** ListRoom
** File description:
** ListRoom
*/

#pragma once
#include "ScenesInitializer.hpp"

class ListRoom : public ScenesInitializer {
    public:
        ListRoom() = default;
        ~ListRoom() = default;

        static void initScene(ecs::Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical)
        {
            std::vector<float> rect;
            std::size_t entity;

            registry.setActualScene(ecs::Scenes::LISTROOM);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 1280, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 1, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 500, 0, -60, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 1);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 1), rect);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::JOINROOMBYID);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 0), rect);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 480, 100, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 480, 250, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 480, 450, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);

            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 480, 550, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);
        };
};

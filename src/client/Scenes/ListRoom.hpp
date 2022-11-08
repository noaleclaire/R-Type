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
            std::string nb_players_in_room = "";

            registry.setActualScene(ecs::Scenes::LISTROOM);

            // //Backgrounds
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            //     //Parallaxe
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 1280, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            // //Logo
            //     //logo menu join
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 2, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 100, 75, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 2), rect);
            //     //logo private room
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 3, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 100, 75, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 3), rect);
            // //Zone
            //     //bg private room zone
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 4, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 100, 75, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 4), rect);
            //     //public mainframe
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 5, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 100, 75, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 5), rect);

            // //Buttons
            //     //back arrow
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 6, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 6, 2);
            // registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            // registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 6), rect);
            //     //join private room
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 7, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 7, 2);
            // registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::JOINROOMBYID);
            // registry.removeComponent<ecs::Pressed>(registry.getEntityById(entity));
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 7), rect);
            //     //versus button
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 8, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 8, 2);
            // registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::JOINROOMBYID);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 8), rect);
            //     //coop button
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 9, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 9, 2);
            // registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::JOINROOMBYID);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 9), rect);
            // //TextBox
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::TEXTBOX, 0, 0);
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::SELECTTEXTBOX));
            // registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1)));
            // registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            // registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXTBOX));
            // registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            // registry.addComponent<ecs::TextBox>(registry.getEntityById(entity), ecs::TextBox(ROOM_ID_SIZE));
            //     //Text in
            // rect = {rect.at(0), rect.at(1), 30};
            // entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1)));
            // registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            // registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            // graphical.addText(entity, "", rect);

            // //Rooms
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 480, 100, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOMMODE, 0, 0);
            //     //logo mode of the room
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(0, 0));
            // registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            // registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMMODE));
            //     //nb players in room
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(0, 0));
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXTNBPLAYERS));
            // registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>(nb_players_in_room.c_str())));
            // rect = {registry.getComponents<ecs::Position>().at(entity).value().getXPosition(), registry.getComponents<ecs::Position>().at(entity).value().getYPosition(), 30};
            // graphical.addText(entity, registry.getComponents<ecs::Text>().at(entity).value().getText(), rect);

            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 480, 250, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOMMODE, 0, 0);
            //     //logo mode of the room
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(0, 0));
            // registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            // registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMMODE));
            //     //nb players in room
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(0, 0));
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXTNBPLAYERS));
            // registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>(nb_players_in_room.c_str())));
            // rect = {registry.getComponents<ecs::Position>().at(entity).value().getXPosition(), registry.getComponents<ecs::Position>().at(entity).value().getYPosition(), 30};
            // graphical.addText(entity, registry.getComponents<ecs::Text>().at(entity).value().getText(), rect);

            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 480, 450, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOMMODE, 0, 0);
            // entity = registry.spawnEntity();
            //     //logo mode of the room
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(0, 0));
            // registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            // registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMMODE));
            //     //nb players in room
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(0, 0));
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXTNBPLAYERS));
            // registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>(nb_players_in_room.c_str())));
            // rect = {registry.getComponents<ecs::Position>().at(entity).value().getXPosition(), registry.getComponents<ecs::Position>().at(entity).value().getYPosition(), 30};
            // graphical.addText(entity, registry.getComponents<ecs::Text>().at(entity).value().getText(), rect);

            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 480, 550, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOMMODE, 0, 0);
            //     //logo mode of the room
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(0, 0));
            // registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            // registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMMODE));
            //     //nb players in room
            // entity = registry.spawnEntity();
            // registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(0, 0));
            // registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXTNBPLAYERS));
            // registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>(nb_players_in_room.c_str())));
            // rect = {registry.getComponents<ecs::Position>().at(entity).value().getXPosition(), registry.getComponents<ecs::Position>().at(entity).value().getYPosition(), 30};
            // graphical.addText(entity, registry.getComponents<ecs::Text>().at(entity).value().getText(), rect);
        };
};

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
        /**
         * @brief Construct a new List Room object
         * 
         */
        ListRoom() = default;
        /**
         * @brief Destroy the List Room object
         * 
         */
        ~ListRoom() = default;
        /**
         * @brief 
         * 
         * @param registry 
         * @param sprites_manager 
         * @param graphical 
         */
        static void initScene(ecs::Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical)
        {
            std::vector<float> rect;
            std::size_t entity;
            std::size_t tmp_entity;

            registry.setActualScene(ecs::Scenes::LISTROOM);
            graphical.setActualGraphicsEntities(ecs::Scenes::LISTROOM);

            //Backgrounds
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
                //Parallax
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, rect.at(2), 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::PARALLAX);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::PARALLAX, 0), rect);
            //Logo
                //logo menu join
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 10, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 485, 38, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2, 10);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 10), rect);
                //logo private room
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 11, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 78, 269, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2, 11);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 11), rect);
            //Zone
                //bg private room zone
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 12, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 22, 348, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2, 12);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 12), rect);
                //bg public mainframe
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 13, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 356, 170, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2, 13);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 13), rect);

            //Text
                //Text Refresh
            rect = {1080, 480, 30};
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1)));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "RESET FILTERS", rect);
            //TextBox
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::TEXTBOX, 0, 0);
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::SELECTTEXTBOX));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(74, 384));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXTBOXNUMBER));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            registry.addComponent<ecs::TextBox>(registry.getEntityById(entity), ecs::TextBox(ROOM_ID_SIZE));
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::TEXTBOX, 0), rect);
                //Text in
            rect = {94, 401, 24};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            tmp_entity = entity;
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1)));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "", rect);

            //Buttons
                //back arrow
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 30, 624, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 6, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 6), rect);
                //join private room
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 7, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 92, 465, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 7, 3);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::JOINROOMBYID);
            registry.removeComponent<ecs::Pressed>(registry.getEntityById(entity));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(tmp_entity));
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 7), rect);
                //versus button
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 8, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 59, 52, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 8, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::FILTERBYROOMMODEVERSUS);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 8), rect);
                //coop button
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 9, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 972, 22, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 9, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::FILTERBYROOMMODECOOP);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 9), rect);
                //refresh button
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 15, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 1115, 376, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 15, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::REFRESHFILTERSROOM);
            registry.removeComponent<ecs::Pressed>(registry.getEntityById(entity));
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 15), rect);

            //Room1
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 368, 221, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3);
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);
                //player name + nb players in room
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(570, 232, 60, 0));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addText(entity, "", {registry.getComponents<ecs::Rectangle>().at(entity).value().getXRectangle(),
            registry.getComponents<ecs::Rectangle>().at(entity).value().getYRectangle(), registry.getComponents<ecs::Rectangle>().at(entity).value().getWidthRectangle()});
                //logo mode of the room
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOMMODE, 0, 0);
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(393, 252));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMMODE, 0));
            //Room2
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 368, 363, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3);
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);
                //player name + nb players in room
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(570, 360, 60, 0));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addText(entity, "", {registry.getComponents<ecs::Rectangle>().at(entity).value().getXRectangle(),
            registry.getComponents<ecs::Rectangle>().at(entity).value().getYRectangle(), registry.getComponents<ecs::Rectangle>().at(entity).value().getWidthRectangle()});
                //logo mode of the room
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOMMODE, 0, 0);
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(393, 383));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMMODE, 0));
            //Room3
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOM, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::ROOM, 368, 509, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3);
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::ROOM, 0), rect);
                //player name + nb players in room
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(570, 520, 60, 0));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addText(entity, "", {registry.getComponents<ecs::Rectangle>().at(entity).value().getXRectangle(),
            registry.getComponents<ecs::Rectangle>().at(entity).value().getYRectangle(), registry.getComponents<ecs::Rectangle>().at(entity).value().getWidthRectangle()});
                //logo mode of the room
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::ROOMMODE, 0, 0);
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(393, 540));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMMODE, 0));
        };
};

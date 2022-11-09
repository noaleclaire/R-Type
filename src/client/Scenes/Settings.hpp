/*
** EPITECH PROJECT, 2022
** Settings
** File description:
** Settings
*/

#pragma once

#include "ScenesInitializer.hpp"
#include "../UserInfo.hpp"

class Settings : public ScenesInitializer {
    public:
        Settings() = default;
        ~Settings() = default;

        static void initScene(ecs::Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical)
        {
            std::vector<float> rect;
            std::size_t entity;
            std::size_t tmp_entity;
            std::size_t tmp_width;

            registry.setActualScene(ecs::Scenes::SETTINGS);

            //Backgrounds
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
                //Parallaxe
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, rect.at(2), 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
                //Logo and button from the menu but background
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 3, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2, 3);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 3), rect);
                //Black filter
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 2, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3, 2);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 2), rect);
                //Popup
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 4, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 260, 153, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3, 4);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 4), rect);
            //Shape volume
                //Music
                    //Shape background
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            rect = {394, 362, rect.at(2) - 27, rect.at(3) - 25};
            entity = registry.spawnEntity();
            tmp_width = rect.at(2);
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::CHANGEMUSICVOLUME));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Black);
                    //Shape volume changer
            rect.at(2) = rect.at(2) * Core::new_music_volume/100;
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(5));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Red);
                    //Text volume value
            rect = {rect.at(0) + tmp_width/2 - 5, rect.at(1) + 3, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(6));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::MUSIC));
            graphical.addText(entity, "10%", rect);
                //SFX
                    //Shape background
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            rect = {394, 447, rect.at(2) - 27, rect.at(3) - 25};
            entity = registry.spawnEntity();
            tmp_width = rect.at(2);
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::CHANGESFXVOLUME));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Black);
                    //Shape volume changer
            rect.at(2) = rect.at(2) * Core::new_sfx_volume/100;
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(5));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Red);
                    //Text volume value
            rect = {rect.at(0) + tmp_width/2 - 5, rect.at(1) + 3, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(6));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SFX));
            graphical.addText(entity, "10%", rect);
            //TextBox
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 7, 0);
            rect = {394, 277, rect.at(2) - 27, rect.at(3) - 25};
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::SELECTTEXTBOX));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXTBOX));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            registry.addComponent<ecs::TextBox>(registry.getEntityById(entity), ecs::TextBox(PSEUDO_SIZE));
            graphical.addRectangleShape(entity, rect, sf::Color::Black);
                //Text in
            rect = {rect.at(0) + 5, rect.at(1) + 5, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            tmp_entity = entity;
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(5));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::PSEUDO));
            graphical.addText(entity, "", rect);
            //Bars (background)
                //Bar enter new name
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 7, 0);
            tmp_width = rect.at(2);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 376, 264, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 7, 7);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 7), rect);
                //Bar volume music
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 376, 349, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 7, 6);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 6), rect);
                //Bar volume sfx
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 376, 434, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 7, 6);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 6), rect);
            //Buttons
                //back arrow
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 280, 173, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 6, 4);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 6), rect);
                //confirm new pseudo
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 11, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 376 + tmp_width + 5, 262, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 11, 4);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::CONFIRMPSEUDO);
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(tmp_entity));
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 11), rect);
        }
};

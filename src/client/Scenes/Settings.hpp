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
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 3), rect);
                //Black filter
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 2, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 2), rect);
                //Popup
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 4, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 260, 153, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 4), rect);
            //Shape volume
                //Music
                    //Shape background
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            rect = {394, 362, rect.at(2) - 27, rect.at(3) - 25};
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::CHANGEVOLUME));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Black);
                    //Shape volume changer
            rect.at(2) /= 10;
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(5));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Red);
                    //Text volume value
            rect = {rect.at(0) + rect.at(2) * 5 - 5, rect.at(1) + 3, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(6));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "10%", rect);
                //SFX
                    //Shape background
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            rect = {394, 447, rect.at(2) - 27, rect.at(3) - 25};
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::CHANGEVOLUME));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Black);
                    //Shape volume changer
            rect.at(2) /= 10;
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(5));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            graphical.addRectangleShape(entity, rect, sf::Color::Red);
                    //Text volume value
            rect = {rect.at(0) + rect.at(2) * 5 - 5, rect.at(1) + 3, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(6));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "10%", rect);
            //TextBox
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            rect = {394, 277, rect.at(2) - 27, rect.at(3) - 25};
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Clickable>(registry.getEntityById(entity), ecs::Clickable(ecs::Clickable::Function::SELECTTEXTBOX));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(rect.at(0), rect.at(1), rect.at(2), rect.at(3)));
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::SHAPE));
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            registry.addComponent<ecs::TextBox>(registry.getEntityById(entity), ecs::TextBox(PSEUDO_SIZE));
            graphical.addRectangleShape(entity, rect, sf::Color::Green);
                //Text in
            rect = {rect.at(0) + 5, rect.at(1) + 5, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            tmp_entity = entity;
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(5));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "", rect);
            //Barres (background)
                //Barre enter new name
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 376, 264, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 7, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 6), rect);
                //Barre volume music
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 376, 349, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 7, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 6), rect);
                //Barre volume sfx
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 376, 434, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 7, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 6), rect);
            //Buttons
                //back arrow -> changer le sprite
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 280, 173, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 4);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 0), rect);
            //     //confirm new pseudo
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 0, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 700, 100, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            // registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::CONFIRMPSEUDO);
            // registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(tmp_entity));
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 0), rect);
        }
};

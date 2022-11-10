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
        /**
         * @brief Construct a new Type Pseudo object
         * 
         */
        TypePseudo() = default;
        /**
         * @brief Destroy the Type Pseudo object
         * 
         */
        ~TypePseudo() = default;
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
            std::size_t tmp_width;
            std::size_t tmp_entity;

            registry.setActualScene(ecs::Scenes::TYPEPSEUDO);

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
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 5, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 207, 220, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3, 5);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 5), rect);
            // TextBox
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 8, 0);
            rect = {249, 368, rect.at(2) - 27, rect.at(3) - 25};
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
            rect = {rect.at(0) + 10, rect.at(1) + 10, 30};
            entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            tmp_entity = entity;
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(5));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            graphical.addText(entity, "", rect);
            //Bars (background)
                //Bar enter new name
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 8, 0);
            tmp_width = rect.at(2);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 231, 355, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 6, 8);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 8), rect);
            //Buttons
                //pseudo
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 11, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 231 + tmp_width + 5, 358, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 11, 4);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 11), rect);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
                //confirm pseudo -> duplicata of pseudo but non drawable
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 11, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 231 + tmp_width + 5, 358, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 11, 4);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::CONFIRMPSEUDO);
            registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(tmp_entity));
            registry.removeComponent<ecs::Drawable>(registry.getEntityById(entity));
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 11), rect);
            //     //exit
            // rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 3, 0);
            // entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 928 - rect.at(2), 600, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 2);
            // registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::EXIT);
            // graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 3), rect);
            // registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
        };
};
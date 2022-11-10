/*
** EPITECH PROJECT, 2022
** HowToPlay
** File description:
** HowToPlay
*/

#pragma once
#include "ScenesInitializer.hpp"

class HowToPlay : public ScenesInitializer {
    public:
        /**
         * @brief Construct a new How To Play object
         * 
         */
        HowToPlay() = default;
        /**
         * @brief Destroy the How To Play object
         * 
         */
        ~HowToPlay() = default;
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

            registry.setActualScene(ecs::Scenes::HOWTOPLAY);

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
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 9, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 226, 50, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 3, 9);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 9), rect);
            //Buttons
                //back arrow
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 20, 20, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 6, 4);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 6), rect);
        };
};

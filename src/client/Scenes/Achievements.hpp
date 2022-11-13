/*
** EPITECH PROJECT, 2022
** Achievements
** File description:
** Achievements
*/

#pragma once
#include "ScenesInitializer.hpp"

class Achievements : public ScenesInitializer {
    public:
        /**
         * @brief Construct a new Achievements object
         * 
         */
        Achievements() = default;
        /**
         * @brief Destroy the Achievements object
         * 
         */
        ~Achievements() = default;
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
            std::size_t y = 50;
            std::size_t layer = 0;
            std::vector<std::string> achievements = {"Matrixed", "RAMPAGE!!!", "Mind HACKER!", "Nemesis", "BFF",
                                                    "World Warrior", "Is it what pain feels?", "Wall said!"};

            registry.setActualScene(ecs::Scenes::ACHIEVEMENTS);
            graphical.setActualGraphicsEntities(ecs::Scenes::ACHIEVEMENTS);

            //Backgrounds
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
                //Parallax
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, rect.at(2), 0, -80, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::PARALLAX);
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::PARALLAX, 0), rect);
            // for (auto &achievement : achievements) {
            //     //Backgrounds
            //     rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 0, 0);
            //     entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, y, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 1, 0);
            //     registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
            //     graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 0), rect);
            //     y += 50 + rect.at(3);
            //         //Text in
            //     rect = {rect.at(0) + rect.at(2)/2, rect.at(1) + rect.at(3)/2, 30};
            //     entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
            //     registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
            //     registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(5));
            //     registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::PSEUDO));
            //     graphical.addText(entity, "", rect);
            // }
            //Buttons
                //back arrow
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 20, 20, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 6, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 6), rect);
        };
};

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
            std::size_t tmp_y;
            std::size_t layer = 0;
            std::vector<std::string> achievements = {"Matrixed", "RAMPAGE!!!", "Xiting", "Mind HACKER!", "Nemesis", "BFF",
                                                    "World Warrior", "Is it what pain feels?", "Well said!"};

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
            for (std::size_t i = 0; i < achievements.size(); i++) {
                //Backgrounds
                layer = 2;
                rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BACKGROUND, 19, 0);
                entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, (1280 - rect.at(2))/2, y, 0, 0, rect.at(0), rect.at(1), rect.at(2), rect.at(3), layer, 19);
                registry.addComponent<ecs::Link>(registry.getEntityById(entity), ecs::Link(registry.spawnEntity()));
                registry.addComponent<ecs::Achievement>(registry.getEntityById(entity), ecs::Achievement(i));
                graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BACKGROUND, 19), rect);
                tmp_y = y;
                y += 10 + rect.at(3);
                layer++;
                    //Text in
                rect = {(1280 - rect.at(2))/2 + rect.at(2)/6 , tmp_y + rect.at(3)/2 - 35, 50};
                entity = registry.getComponents<ecs::Link>().at(entity).value().getLink();
                registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(rect.at(0), rect.at(1), 0, 0));
                registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(layer));
                registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
                registry.addComponent<ecs::Achievement>(registry.getEntityById(entity), ecs::Achievement(i));
                graphical.addText(entity, achievements.at(i), rect);
            }
            //Buttons
                //back arrow
            rect = sprites_manager.get_Animations_rect(ecs::EntityTypes::BUTTON, 6, 0);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 20, 20, rect.at(0), rect.at(1), rect.at(2), rect.at(3), 6, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOMENU);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            graphical.addSprite(entity, sprites_manager.get_Spritesheet(ecs::EntityTypes::BUTTON, 6), rect);
        };
};

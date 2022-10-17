/*
** EPITECH PROJECT, 2022
** Graphical
** File description:
** Graphical
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../Ecs/Enum.hpp"
#include "../../Ecs/Registry.hpp"
#include "SpritesManager.hpp"

namespace graphics
{
    class Graphical {
      public:
        Graphical();
        ~Graphical();

        /* Getter */
        /**
         * @brief Get the All Textures object
         *
         * @return std::unordered_map<std::string, sf::Texture>
         */
        std::unordered_map<std::string, sf::Texture> getAllTextures() const;
        /**
         * @brief Get the All Sprites object
         *
         * @return std::unordered_map<std::size_t, sf::Sprite>
         */
        std::unordered_map<std::size_t, sf::Sprite> getAllSprites() const;
        /**
         * @brief Get the Video Mode object
         *
         * @return sf::VideoMode
         */
        sf::VideoMode getVideoMode() const;
        /**
         * @brief Get the Event object
         *
         * @return sf::Event&
         */
        sf::Event &getEvent();
        /**
         * @brief Get the Window object
         *
         * @return sf::RenderWindow&
         */
        sf::RenderWindow &getWindow();

        /* Setter */
        /**
         * @brief Set the Video Mode object
         *
         * @param width
         * @param height
         */
        void setVideoMode(int width, int height);
        /**
         * @brief Set the Sprite Position object
         *
         * @param entity
         * @param posX
         * @param posY
         */
        void setSpritePosition(ecs::Entity entity, float posX, float posY);
        /**
         * @brief Set the Actual Sprites Entities object
         *
         * @param _scene
         */
        void setActualSpritesEntities(ecs::Scenes _scene);

        /* Other */
        /**
         * @brief
         *
         * @param sprites_manager
         */
        void addAllTextures(SpritesManager &sprites_manager);
        /**
         * @brief
         *
         * @param entity
         * @param spritesheet
         * @param rect
         */
        void addSprite(std::size_t entity, std::string spritesheet, std::vector<float> rect = {});
        /**
         * @brief
         *
         * @param registry
         */
        void draw(ecs::Registry &registry);
        /**
         * @brief
         *
         * @param registry
         */
        void handleEvents(ecs::Registry &registry);

      protected:
      private:
        /**
         * @brief
         *
         * @param registry
         */
        void _handleMouseButtonEvents(ecs::Registry &registry);

        sf::RenderWindow _window;
        sf::VideoMode _mode;
        sf::Event _event;
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::size_t, sf::Sprite> _unique_sprites_entities;
        std::unordered_map<std::size_t, sf::Sprite> _shared_sprites_entities;
        std::unordered_map<std::size_t, sf::Sprite> *_actual_sprites_entities;
    };
} // namespace graphics

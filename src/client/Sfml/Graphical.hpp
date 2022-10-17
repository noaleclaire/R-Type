/*
** EPITECH PROJECT, 2022
** Graphical
** File description:
** Graphical
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SpritesManager.hpp"
#include "../../Ecs/Registry.hpp"
#include "../../Ecs/Enum.hpp"

namespace graphics
{
    class Graphical {
      public:
        Graphical();
        ~Graphical();

        /* Getter */
        std::unordered_map<std::string, sf::Texture> getAllTextures() const;
        std::unordered_map<std::size_t, sf::Sprite> getAllSprites() const;
        sf::VideoMode getVideoMode() const;
        sf::Event &getEvent();
        sf::RenderWindow &getWindow();

        /* Setter */
        void setVideoMode(int width, int height);
        void setSpritePosition(ecs::Entity entity, float posX, float posY);
        void setActualSpritesEntities(ecs::Scenes _scene);

        /* Other */
        void addAllTextures(SpritesManager &sprites_manager);
        void addSprite(std::size_t entity, std::string spritesheet, std::vector<float> rect = {});
        void draw(ecs::Registry &registry);
        void handleEvents(ecs::Registry &registry);

      protected:
      private:
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

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

namespace graphics
{
    class Graphical {
        public:
            Graphical();
            ~Graphical();

            void addAllTextures(graphics::SpritesManager &sprites_manager);
            std::unordered_map<std::string, sf::Texture> getAllTextures() const;
            void addSprite(std::size_t entity, std::string spritesheet, std::vector<float> rect = {});
            std::unordered_map<std::size_t, sf::Sprite> getAllSprites() const;
            void setVideoMode(int width, int height);
            sf::VideoMode getVideoMode() const;
            sf::Event &getEvent();
            sf::RenderWindow &getWindow();
        protected:
        private:
            sf::RenderWindow _window;
            sf::VideoMode _mode;
            sf::Event _event;
            std::unordered_map<std::string, sf::Texture> _textures;
            std::unordered_map<std::size_t, sf::Sprite> _entities_sprites;
    };
}

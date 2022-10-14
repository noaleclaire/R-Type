/*
** EPITECH PROJECT, 2022
** Graphical
** File description:
** Graphical
*/

#include <filesystem>
#include "Graphical.hpp"
#include "../Exceptions/SfmlExceptionTexture.hpp"

namespace graphics
{
    Graphical::Graphical()
    {
        setVideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    }

    Graphical::~Graphical()
    {
    }

    void Graphical::addAllTextures(SpritesManager &sprites_manager)
    {
        sf::Texture texture;
        for (auto &it : sprites_manager.getTexturePath()) {
            if (!texture.loadFromFile(std::filesystem::current_path().append("assets/sprites/" + it))) {
                if (!texture.loadFromFile(std::filesystem::current_path().append("assets/sprites/missing_texture.png")))
                    throw SfmlExceptionTexture("Cannot load texture from file", "void Graphical::addAllTextures(SpritesManager &sprites_manager)");
            }
            _textures.insert(std::make_pair(it, texture));
        }
    }

    std::unordered_map<std::string, sf::Texture> Graphical::getAllTextures() const
    {
        return (_textures);
    }

    void Graphical::addSprite(std::size_t entity, std::string spritesheet, std::vector<float> rect)
    {
        float xScale = 1;
        float yScale = 1;

        _entities_sprites.insert(std::make_pair(entity, sf::Sprite(_textures.at(spritesheet))));
        if (_textures.at(spritesheet).getSize().x == 1200 && _textures.at(spritesheet).getSize().y == 1200) {
            xScale = rect.at(SpriteAnimAttributes::rect_width) / 1200;
            yScale = rect.at(SpriteAnimAttributes::rect_height) / 1200;
        } else {
            _entities_sprites.at(entity).setTextureRect(sf::IntRect(rect.at(SpriteAnimAttributes::rect_x),
            rect.at(SpriteAnimAttributes::rect_y), rect.at(SpriteAnimAttributes::rect_width),
            rect.at(SpriteAnimAttributes::rect_height)));
        }
        _entities_sprites.at(entity).setScale(sf::Vector2f(xScale, yScale));
    }

    std::unordered_map<std::size_t, sf::Sprite> Graphical::getAllSprites() const
    {
        return (_entities_sprites);
    }

    void Graphical::setVideoMode(int width, int height)
    {
        _mode = sf::VideoMode(width, height);
    }

    sf::VideoMode Graphical::getVideoMode() const
    {
        return (_mode);
    }
    sf::Event &Graphical::getEvent()
    {
        return (_event);
    }
    sf::RenderWindow &Graphical::getWindow()
    {
        return (_window);
    }
}

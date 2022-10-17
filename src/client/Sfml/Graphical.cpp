/*
** EPITECH PROJECT, 2022
** Graphical
** File description:
** Graphical
*/

#include "Graphical.hpp"
#include <filesystem>
#include "../../Ecs/Systems/Systems.hpp"
#include "../Exceptions/SfmlExceptionTexture.hpp"

namespace graphics
{
    Graphical::Graphical()
    {
        _actual_sprites_entities = &_unique_sprites_entities;
        // remettre ça mais rescale les sprites donc d'abord faire avec une fenêtre fix
        // setVideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
        setVideoMode(1280, 720);
    }

    Graphical::~Graphical()
    {
    }

    /* Getter */
    std::unordered_map<std::string, sf::Texture> Graphical::getAllTextures() const
    {
        return (_textures);
    }

    std::unordered_map<std::size_t, sf::Sprite> Graphical::getAllSprites() const
    {
        return (*_actual_sprites_entities);
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

    /* Setter */
    void Graphical::setVideoMode(int width, int height)
    {
        _mode = sf::VideoMode(width, height);
    }

    void Graphical::setSpritePosition(ecs::Entity entity, float posX, float posY)
    {
        _actual_sprites_entities->at(entity).setPosition(posX, posY);
    }

    /* Other */
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

    void Graphical::addSprite(std::size_t entity, std::string spritesheet, std::vector<float> rect)
    {
        float xScale = 1;
        float yScale = 1;

        _actual_sprites_entities->insert_or_assign(entity, sf::Sprite(_textures.at(spritesheet)));
        if (_textures.at(spritesheet).getSize().x == 1200 && _textures.at(spritesheet).getSize().y == 1200) {
            xScale = rect.at(SpriteAnimAttributes::rect_width) / 1200;
            yScale = rect.at(SpriteAnimAttributes::rect_height) / 1200;
        } else {
            _actual_sprites_entities->at(entity).setTextureRect(sf::IntRect(rect.at(SpriteAnimAttributes::rect_x), rect.at(SpriteAnimAttributes::rect_y),
                rect.at(SpriteAnimAttributes::rect_width), rect.at(SpriteAnimAttributes::rect_height)));
        }
        _actual_sprites_entities->at(entity).setScale(sf::Vector2f(xScale, yScale));
    }

    void Graphical::draw(ecs::Registry &registry)
    {
        _window.clear();
        ecs::Systems::Drawable(registry, registry.getComponents<ecs::Drawable>(), this);
        _window.display();
    }

    void Graphical::handleEvents(ecs::Registry &registry)
    {
        while (_window.pollEvent(_event)) {
            _handleMouseButtonEvents(registry);
            if (_event.type == sf::Event::Closed)
                _window.close();
        }
    }

    void Graphical::_handleMouseButtonEvents(ecs::Registry &registry)
    {
        if (_event.type == sf::Event::MouseButtonReleased) {
            if (_event.mouseButton.button == sf::Mouse::Button::Left)
                ecs::Systems::Clickable(registry, registry.getComponents<ecs::Clickable>(), this);
        }
    }

    void Graphical::setActualSpritesEntities(ecs::Scenes _scene)
    {
        if (_scene == ecs::Scenes::MENU || _scene == ecs::Scenes::SETTINGS)
            _actual_sprites_entities = &_unique_sprites_entities;
        else
            _actual_sprites_entities = &_shared_sprites_entities;
    }
} // namespace graphics

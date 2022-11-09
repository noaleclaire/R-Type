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
    float Graphical::world_current_time = 0;
    Graphical::Graphical()
    {
        _actual_sprites_entities = &_unique_sprites_entities;
        _actual_text_entities = &_text_entities;
        // remettre ça mais rescale les sprites donc d'abord faire avec une fenêtre fix
        // setVideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
        setVideoMode(1280, 720);
        _font.loadFromFile(std::filesystem::current_path().append("assets/fonts/VT323-Regular.ttf"));
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

    std::unordered_map<std::size_t, sf::RectangleShape> Graphical::getAllRectangleShapes() const
    {
        return (_rectangleshape_entities);
    }

    std::unordered_map<std::size_t, sf::Text> Graphical::getAllTexts() const
    {
        return (*_actual_text_entities);
    }

    sf::VideoMode Graphical::getVideoMode() const
    {
        return (_mode);
    }

    sf::RenderWindow &Graphical::getWindow()
    {
        return (_window);
    }

    sf::Event &Graphical::getEvent()
    {
        return (_event.getEvent());
    }

    std::string Graphical::getTextString(std::size_t entity)
    {
        return (_actual_text_entities->at(entity).getString());
    }

    /* Setter */
    void Graphical::setVideoMode(int width, int height)
    {
        _mode = sf::VideoMode(width, height);
    }

    void Graphical::setSpritePosition(std::size_t entity, float posX, float posY)
    {
        _actual_sprites_entities->at(entity).setPosition(posX, posY);
    }

    void Graphical::setRectangleShapePosition(std::size_t entity, float posX, float posY)
    {
        _rectangleshape_entities.at(entity).setPosition(posX, posY);
    }

    void Graphical::setRectangleShapeOutline(std::size_t entity, sf::Color color, std::size_t size)
    {
        _rectangleshape_entities.at(entity).setOutlineColor(color);
        _rectangleshape_entities.at(entity).setOutlineThickness(size);
    }

    void Graphical::setRectangleShapeColor(std::size_t entity, sf::Color color)
    {
        _rectangleshape_entities.at(entity).setFillColor(color);
    }

    /* Other */
    void Graphical::addAllTextures()
    {
        sf::Texture texture;
        for (auto &it : sprites_manager->getTexturePath()) {
            if (!texture.loadFromFile(std::filesystem::current_path().append("assets/sprites/" + it).string())) {
                if (!texture.loadFromFile(std::filesystem::current_path().append("assets/sprites/missing_texture.png").string()))
                    throw SfmlExceptionTexture("Cannot load texture from file", "void Graphical::addAllTextures(SpritesManager &sprites_manager)");
            }
            _textures.insert(std::make_pair(it, texture));
        }
        if (!texture.loadFromFile(std::filesystem::current_path().append("assets/sprites/missing_texture.png").string()))
            throw SfmlExceptionTexture("Cannot load texture from file", "void Graphical::addAllTextures(SpritesManager &sprites_manager)");
        _textures.insert(std::make_pair("missing_texture.png", texture));
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
    void Graphical::addRectangleShape(std::size_t entity, std::vector<float> rect, sf::Color color)
    {
        _rectangleshape_entities.insert_or_assign(entity, sf::RectangleShape(sf::Vector2f(rect.at(2), rect.at(3))));
        _rectangleshape_entities.at(entity).setFillColor(color);
        _rectangleshape_entities.at(entity).setPosition(sf::Vector2f(rect.at(0), rect.at(1)));
    }
    void Graphical::addText(std::size_t entity, std::string str, std::vector<float> rect, sf::Color color)
    {
        _actual_text_entities->insert_or_assign(entity, sf::Text(str, _font));
        _actual_text_entities->at(entity).setPosition(rect.at(0), rect.at(1));
        _actual_text_entities->at(entity).setCharacterSize(rect.at(2));
        _actual_text_entities->at(entity).setFillColor(color);
    }

    void Graphical::setRectangleShapeRect(std::size_t entity, float width, float height)
    {
        _rectangleshape_entities.at(entity).setSize(sf::Vector2f(width, height));
    }

    void Graphical::setTextString(std::size_t entity, std::string str)
    {
        _actual_text_entities->at(entity).setString(str);
    }

    void Graphical::handleEvents(ecs::Registry &registry)
    {
        _event.handleEvents(this, registry);
    }

    void Graphical::draw(ecs::Registry &registry)
    {
        _window.clear();
        ecs::Systems::Drawable(registry, registry.getComponents<ecs::Drawable>(), this);
        _window.display();
    }

    void Graphical::setActualGraphicsEntities(ecs::Scenes _scene)
    {
        if (_scene == ecs::Scenes::MENU || _scene == ecs::Scenes::SETTINGS || _scene == ecs::Scenes::LISTROOM ||
            _scene == ecs::Scenes::TYPEPSEUDO || _scene == ecs::Scenes::HOWTOPLAY) {
            _actual_sprites_entities = &_unique_sprites_entities;
            _actual_text_entities = &_text_entities;
        } else {
            _actual_sprites_entities = &_shared_sprites_entities;
            _actual_text_entities = &_shared_text_entities;
        }
    }

    void Graphical::getWorldClock()
    {
        Graphical::world_current_time = _world_clock.restart().asSeconds();
    }

    void Graphical::setHoverSprite(std::size_t entity)
    {
        sf::IntRect rect = _actual_sprites_entities->at(entity).getTextureRect();

        _actual_sprites_entities->at(entity).setTextureRect(sf::IntRect(rect.width, rect.top, rect.width, rect.height));
    }

    void Graphical::setPressedSprite(std::size_t entity)
    {
        sf::IntRect rect = _actual_sprites_entities->at(entity).getTextureRect();

        _actual_sprites_entities->at(entity).setTextureRect(sf::IntRect(rect.width * 2, rect.top, rect.width, rect.height));
    }

    void Graphical::setBasicSprite(std::size_t entity)
    {
        sf::IntRect rect = _actual_sprites_entities->at(entity).getTextureRect();

        _actual_sprites_entities->at(entity).setTextureRect(sf::IntRect(0, rect.top, rect.width, rect.height));
    }
    void Graphical::setTextureRectSprite(std::size_t entity, float x, float y, float width, float height)
    {
        _actual_sprites_entities->at(entity).setTextureRect(sf::IntRect(x, y, width, height));
    }
} // namespace graphics

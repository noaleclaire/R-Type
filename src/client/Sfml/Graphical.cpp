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
        // remettre ça mais rescale les sprites donc d'abord faire avec une fenêtre fix
        // setVideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
        setVideoMode(1280, 720);
        _font.loadFromFile(std::filesystem::current_path().append("assets/fonts/VT323-Regular.ttf").string());
        _music_entities[ecs::Music::CAVE].openFromFile(std::filesystem::current_path().append("assets/sounds/cave_music.ogg").string());
        _music_entities[ecs::Music::SPACE].openFromFile(std::filesystem::current_path().append("assets/sounds/space_music.ogg").string());
        _music_entities[ecs::Music::DESERT].openFromFile(std::filesystem::current_path().append("assets/sounds/desert_music.ogg").string());
        _music_entities[ecs::Music::SNOW].openFromFile(std::filesystem::current_path().append("assets/sounds/snow_music.ogg").string());
        _music_entities[ecs::Music::FOREST].openFromFile(std::filesystem::current_path().append("assets/sounds/forest_music.ogg").string());
        _music_entities[ecs::Music::MUSICMENU].openFromFile(std::filesystem::current_path().append("assets/sounds/snow_music.ogg").string());
        _music_entities[ecs::Music::BOSS].openFromFile(std::filesystem::current_path().append("assets/sounds/boss_music.ogg").string());
    }

    Graphical::~Graphical()
    {
    }

    /* Getter */
    std::unordered_map<std::string, sf::Texture> Graphical::getAllTextures() const
    {
        return (_textures);
    }

    std::unordered_map<std::size_t, sf::Sprite> &Graphical::getAllSprites()
    {
        try {
            _sprites_entities.at(_actual_scene);
        } catch (const std::out_of_range &e) {
            _sprites_entities.emplace(_actual_scene, std::unordered_map<std::size_t, sf::Sprite>());
            return (_sprites_entities.at(_actual_scene));
        }
        return (_sprites_entities.at(_actual_scene));
    }

    std::unordered_map<std::size_t, sf::RectangleShape> &Graphical::getAllRectangleShapes()
    {
        try {
            _rectangleshape_entities.at(_actual_scene);
        } catch (const std::out_of_range &e) {
            _rectangleshape_entities.emplace(_actual_scene, std::unordered_map<std::size_t, sf::RectangleShape>());
            return (_rectangleshape_entities.at(_actual_scene));
        }
        return (_rectangleshape_entities.at(_actual_scene));
    }

    std::unordered_map<std::size_t, sf::Text> &Graphical::getAllTexts()
    {
        try {
            _text_entities.at(_actual_scene);
        } catch (const std::out_of_range &e) {
            _text_entities.emplace(_actual_scene, std::unordered_map<std::size_t, sf::Text>());
            return (_text_entities.at(_actual_scene));
        }
        return (_text_entities.at(_actual_scene));
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
        return (_text_entities.at(_actual_scene).at(entity).getString());
    }

    sf::Music &Graphical::getActualMusic()
    {
        return (_music_entities.at(prev_music));
    }

    /* Setter */
    void Graphical::setVideoMode(int width, int height)
    {
        _mode = sf::VideoMode(width, height);
    }

    void Graphical::setSpritePosition(std::size_t entity, float posX, float posY)
    {
        _sprites_entities.at(_actual_scene).at(entity).setPosition(posX, posY);
    }

    void Graphical::setRectangleShapePosition(std::size_t entity, float posX, float posY)
    {
        _rectangleshape_entities.at(_actual_scene).at(entity).setPosition(posX, posY);
    }

    void Graphical::setRectangleShapeOutline(std::size_t entity, sf::Color color, std::size_t size)
    {
        _rectangleshape_entities.at(_actual_scene).at(entity).setOutlineColor(color);
        _rectangleshape_entities.at(_actual_scene).at(entity).setOutlineThickness(size);
    }

    void Graphical::setRectangleShapeColor(std::size_t entity, sf::Color color)
    {
        _rectangleshape_entities.at(_actual_scene).at(entity).setFillColor(color);
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

        try {
            _sprites_entities.at(_actual_scene);
        } catch (const std::out_of_range &e) {
            _sprites_entities.emplace(_actual_scene, std::unordered_map<std::size_t, sf::Sprite>());
        }
        _sprites_entities.at(_actual_scene).insert_or_assign(entity, sf::Sprite(_textures.at(spritesheet)));
        if (_textures.at(spritesheet).getSize().x == 1200 && _textures.at(spritesheet).getSize().y == 1200) {
            xScale = rect.at(SpriteAnimAttributes::rect_width) / 1200;
            yScale = rect.at(SpriteAnimAttributes::rect_height) / 1200;
        } else {
            _sprites_entities.at(_actual_scene).at(entity).setTextureRect(sf::IntRect(rect.at(SpriteAnimAttributes::rect_x), rect.at(SpriteAnimAttributes::rect_y),
                rect.at(SpriteAnimAttributes::rect_width), rect.at(SpriteAnimAttributes::rect_height)));
        }
        _sprites_entities.at(_actual_scene).at(entity).setScale(sf::Vector2f(xScale, yScale));
    }
    void Graphical::addRectangleShape(std::size_t entity, std::vector<float> rect, sf::Color color)
    {
        try {
            _rectangleshape_entities.at(_actual_scene);
        } catch (const std::out_of_range &e) {
            _rectangleshape_entities.emplace(_actual_scene, std::unordered_map<std::size_t, sf::RectangleShape>());
        }
        _rectangleshape_entities.at(_actual_scene).insert_or_assign(entity, sf::RectangleShape(sf::Vector2f(rect.at(2), rect.at(3))));
        _rectangleshape_entities.at(_actual_scene).at(entity).setFillColor(color);
        _rectangleshape_entities.at(_actual_scene).at(entity).setPosition(sf::Vector2f(rect.at(0), rect.at(1)));
    }
    void Graphical::addText(std::size_t entity, std::string str, std::vector<float> rect, sf::Color color)
    {
        try {
            _text_entities.at(_actual_scene);
        } catch (const std::out_of_range &e) {
            _text_entities.emplace(_actual_scene, std::unordered_map<std::size_t, sf::Text>());
        }
        _text_entities.at(_actual_scene).insert_or_assign(entity, sf::Text(str, _font));
        _text_entities.at(_actual_scene).at(entity).setPosition(rect.at(0), rect.at(1));
        _text_entities.at(_actual_scene).at(entity).setCharacterSize(rect.at(2));
        _text_entities.at(_actual_scene).at(entity).setFillColor(color);
    }

    void Graphical::setRectangleShapeRect(std::size_t entity, float width, float height)
    {
        _rectangleshape_entities.at(_actual_scene).at(entity).setSize(sf::Vector2f(width, height));
    }

    void Graphical::setTextString(std::size_t entity, std::string str)
    {
        _text_entities.at(_actual_scene).at(entity).setString(str);
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

    void Graphical::setActualGraphicsEntities(ecs::Scenes scene)
    {
        _actual_scene = scene;
    }

    void Graphical::getWorldClock()
    {
        Graphical::world_current_time = _world_clock.restart().asSeconds();
    }

    void Graphical::setHoverSprite(std::size_t entity)
    {
        sf::IntRect rect = _sprites_entities.at(_actual_scene).at(entity).getTextureRect();

        _sprites_entities.at(_actual_scene).at(entity).setTextureRect(sf::IntRect(rect.width, rect.top, rect.width, rect.height));
    }

    void Graphical::setPressedSprite(std::size_t entity)
    {
        sf::IntRect rect = _sprites_entities.at(_actual_scene).at(entity).getTextureRect();

        _sprites_entities.at(_actual_scene).at(entity).setTextureRect(sf::IntRect(rect.width * 2, rect.top, rect.width, rect.height));
    }

    void Graphical::setVolumeOfAllMusicEntities(float volume)
    {
        for (auto &it : _music_entities)
            it.second.setVolume(volume);
    }

    void Graphical::setActualMusic(ecs::Music music)
    {
        try
        {
            if (music != prev_music) {
                _music_entities.at(prev_music).stop();
                _music_entities.at(music).setLoop(true);
                _music_entities.at(music).play();
                prev_music = music;
            }
        }
        catch(const std::exception& e)
        {
        }
    }

    void Graphical::setBasicSprite(std::size_t entity)
    {
        sf::IntRect rect = _sprites_entities.at(_actual_scene).at(entity).getTextureRect();

        _sprites_entities.at(_actual_scene).at(entity).setTextureRect(sf::IntRect(0, rect.top, rect.width, rect.height));
    }
    void Graphical::setTextureRectSprite(std::size_t entity, float x, float y, float width, float height)
    {
        _sprites_entities.at(_actual_scene).at(entity).setTextureRect(sf::IntRect(x, y, width, height));
    }
} // namespace graphics

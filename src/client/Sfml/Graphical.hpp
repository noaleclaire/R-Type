/*
** EPITECH PROJECT, 2022
** Graphical
** File description:
** Graphical
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "../../Ecs/Enum.hpp"
#include "../../Ecs/Registry.hpp"
#include "Event.hpp"
#include "SpritesManager.hpp"

class CustomClient;
namespace graphics
{
    class Graphical {
      public:
        static float world_current_time;

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
        std::unordered_map<std::size_t, sf::Sprite> &getAllSprites();
        /**
         * @brief Get the All RectangleShape object
         *
         * @return std::unordered_map<std::size_t, sf::RectangleShape>
         */
        std::unordered_map<std::size_t, sf::RectangleShape> &getAllRectangleShapes();
        /**
         * @brief Get the All Text object
         *
         * @return std::unordered_map<std::size_t, sf::Text>
         */
        std::unordered_map<std::size_t, sf::Text> &getAllTexts();
        /**
         * @brief Get the Video Mode object
         *
         * @return sf::VideoMode
         */
        sf::VideoMode getVideoMode() const;
        /**
         * @brief Get the Window object
         *
         * @return sf::RenderWindow&
         */
        sf::RenderWindow &getWindow();
        /**
         * @brief Get the Event object
         *
         * @return sf::Event&
         */
        sf::Event &getEvent();
        /**
         * @brief Get the Text String object
         *
         * @param entity
         *
         * @return std::string
         */
        std::string getTextString(std::size_t entity);

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
        void setSpritePosition(std::size_t entity, float posX, float posY);
        /**
         * @brief Set the Sprite Position object
         *
         * @param entity
         * @param posX
         * @param posY
         */
        void setRectangleShapePosition(std::size_t entity, float posX, float posY);
        /**
         * @brief Set the Rectangle Shape Rect object
         *
         * @param entity
         * @param height
         * @param width
         */
        void setRectangleShapeRect(std::size_t entity, float width, float height);
        /**
         * @brief Set the Rectangle Shape Color object
         *
         * @param entity
         * @param color
         */
        void setRectangleShapeColor(std::size_t entity, sf::Color color);
        /**
         * @brief Set the Rectangle Shape Color object
         *
         * @param entity
         * @param color
         * @param size
         */
        void setRectangleShapeOutline(std::size_t entity, sf::Color color, std::size_t size);
        /**
         * @brief Set the Text String object
         *
         * @param entity
         * @param str
         */
        void setTextString(std::size_t entity, std::string str);
        /**
         * @brief Set the Actual Sprites Entities object
         *
         * @param _scene
         */
        void setActualGraphicsEntities(ecs::Scenes scene);
        /**
         * @brief Set the hover sprite for the entity
         *
         * @param entity
         */
        void setHoverSprite(std::size_t entity);
        /**
         * @brief Set the Pressed Sprite object
         *
         * @param entity
         */
        void setPressedSprite(std::size_t entity);
        /**
         * @brief Set the basic sprite for the entity
         *
         * @param entity
         */
        void setBasicSprite(std::size_t entity);
        /**
         * @brief Set the Actual Music
         * 
         * @param music 
         * @param stop_prev 
         */
        void setActualMusic(ecs::Music music);
        /**
         * @brief Get the Actual Music
         *
         */
        sf::Music &getActualMusic();
        /**
         * @brief Set the Texture Rect Sprite
         *
         * @param entity
         * @param x
         * @param y
         * @param width
         * @param height
         */
        void setTextureRectSprite(std::size_t entity, float x, float y, float width, float height);

        /* Other */
        /**
         * @brief
         *
         * @param sprites_manager
         */
        void addAllTextures();
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
         * @param entity
         * @param rect
         * @param color
         */
        void addRectangleShape(std::size_t entity, std::vector<float> rect = {}, sf::Color color = sf::Color::White);
        /**
         * @brief
         *
         * @param entity
         * @param str
         * @param rect
         * @param color
         */
        void addText(std::size_t entity, std::string str, std::vector<float> rect = {}, sf::Color color = sf::Color::White);
        /**
         * @brief
         *
         * @param registry
         */
        void handleEvents(ecs::Registry &registry);
        /**
         * @brief
         *
         * @param registry
         */
        void draw(ecs::Registry &registry);
        /**
         * @brief Get the World Clock
         *
         */
        void getWorldClock();

        CustomClient *client;
        SpritesManager *sprites_manager;
        ecs::Scenes _actual_scene;
        ecs::Music prev_music = ecs::Music::CAVE;

      protected:
      private:
        sf::RenderWindow _window;
        sf::VideoMode _mode;
        Event _event;
        sf::Clock _world_clock;
        sf::Font _font;
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<ecs::Scenes, std::unordered_map<std::size_t, sf::Sprite>> _sprites_entities;
        std::unordered_map<ecs::Scenes, std::unordered_map<std::size_t, sf::RectangleShape>> _rectangleshape_entities;
        std::unordered_map<ecs::Scenes, std::unordered_map<std::size_t, sf::Text>> _text_entities;
        std::unordered_map<ecs::Music, sf::Music> _music_entities;

    };
} // namespace graphics

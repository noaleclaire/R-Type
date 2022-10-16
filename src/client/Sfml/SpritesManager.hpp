/*
** EPITECH PROJECT, 2022
** SpritesManager
** File description:
** SpritesManager
*/

#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "../AYamlConfig.hpp"
#include "../MapMemberFunctionPointer.hpp"
#include <unordered_map>

#define NB_ANIM_ATTRIBUTES (6)

namespace graphics
{
    enum SpriteTypes { spaceship, monster };
    enum SpriteTypeAttributes { anim };
    enum SpriteAnimAttributes { rect_x, rect_y, rect_width, rect_height, nb_anim, next_anim };

    class SpritesManager : public AYamlConfig {
      public:
        /**
         * @brief Construct a new Sprites Manager object
         * 
         */
        SpritesManager();
        /**
         * @brief Destroy the Sprites Manager object
         * 
         */
        ~SpritesManager();
        /**
         * @brief 
         * 
         * @param sprite_config_word 
         * @param value 
         */
        void executeMapMemberFunctionPointer(std::string &sprite_config_word, std::string &value);
        /**
         * @brief Get the Sprite Type object
         * 
         * @param sprite_type 
         * @return graphics::SpriteTypes 
         */
        graphics::SpriteTypes getSpriteType(std::string &sprite_type) const;
        /**
         * @brief Get the Sprite Type object
         * 
         * @param sprite_type 
         * @return std::string const 
         */
        std::string const getSpriteType(graphics::SpriteTypes sprite_type) const;
        /**
         * @brief Get the Sprite Type Attribute object
         * 
         * @param sprite_type_attribute 
         * @return graphics::SpriteTypeAttributes 
         */

        graphics::SpriteTypeAttributes getSpriteTypeAttribute(std::string &sprite_type_attribute) const;
        /**
         * @brief Get the Sprite Type Attribute object
         * 
         * @param sprite_type_attribute 
         * @return std::string const 
         */
        std::string const getSpriteTypeAttribute(graphics::SpriteTypeAttributes sprite_type_attribute) const;
        /**
         * @brief Get the Sprite Anim Attribute object
         * 
         * @param sprite_anim_attribute 
         * @return graphics::SpriteAnimAttributes 
         */
        graphics::SpriteAnimAttributes getSpriteAnimAttribute(std::string &sprite_anim_attribute) const;
        /**
         * @brief Get the Sprite Anim Attribute object
         * 
         * @param sprite_anim_attribute 
         * @return std::string const 
         */
        std::string const getSpriteAnimAttribute(graphics::SpriteAnimAttributes sprite_anim_attribute) const;
        /**
         * @brief 
         * 
         * @param key_word 
         * @param texture_path 
         */
        void addTexturePath(std::string &key_word, std::string &texture_path);
        /**
         * @brief 
         * 
         * @param sprite_type 
         * @param sprite_type_id 
         */
        void addSpriteTypeId(std::string &sprite_type, std::string &sprite_type_id);
        /**
         * @brief 
         * 
         * @param sprite_type_anim 
         * @param sprite_type_anim_id 
         */
        void addSpriteAnim(std::string &sprite_type_anim, std::string &sprite_type_anim_id);
        /**
         * @brief 
         * 
         * @param anim_attribute_type 
         * @param anim_attribute_value 
         */
        void addSpriteAnimAttributes(std::string &anim_attribute_type, std::string &anim_attribute_value);
        /**
         * @brief Get the Texture Path object
         * 
         * @return std::vector<std::string> const 
         */
        std::vector<std::string> const getTexturePath() const;
        void printSpritesData();

      protected:
      private:
        typedef void (SpritesManager::*MAP_FPTR)(std::string &, std::string &);
        MapMemberFunctionPointer<MAP_FPTR> _map_fptr;
        void initMapFunctionPointer();

        struct SpriteData {
            std::string _spritesheet;
            std::pair<graphics::SpriteTypes, std::size_t> _sprite_type_and_id;
            std::unordered_map<std::size_t, std::vector<std::optional<std::size_t>>> _animations;
        };
        std::vector<SpriteData> _sprites_data;
        std::vector<std::string> _textures_path;

        std::string _spritesheet_tmp = "";
        graphics::SpriteTypes _sprite_type_tmp;
        long unsigned int _sprite_type_id_tmp;
        long unsigned int _sprite_type_anim_id_tmp;
    };
} // namespace graphics

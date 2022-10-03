/*
** EPITECH PROJECT, 2022
** SpritesManager
** File description:
** SpritesManager
*/

#pragma once
#include <functional>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>

#define NB_ANIM_ATTRIBUTES (5)

namespace graphics
{
    enum SpriteTypes { spaceship, monster };
    enum SpriteTypeAttributes { anim };
    enum SpriteAnimAttributes { rect_x, rect_y, rect_width, rect_height, nb_anim, next_anim };

    class SpritesManager {
      public:
        SpritesManager();
        ~SpritesManager();

        bool isSpriteTypes(std::string &sprite_type);
        bool isSpriteTypeAttributes(std::string &sprite_type_attribute);
        bool isSpriteAnimAttributes(std::string &sprite_anim_attribute);
        graphics::SpriteTypes getSpriteType(std::string &sprite_type) const;
        graphics::SpriteTypeAttributes getSpriteTypeAttribute(std::string &sprite_type_attribute) const;
        graphics::SpriteAnimAttributes getSpriteAnimAttribute(std::string &sprite_anim_attribute) const;
        void addTexturePath(std::string &texture_path);
        void addSpriteData1(std::string &spritesheet, std::string &sprite_type, std::string &sprite_type_id);
        void addSpriteData2(std::string &sprite_type, std::string &sprite_type_id, std::string &anim_id);
        void addSpriteData3(
            std::string &sprite_type, std::string &sprite_type_id, std::string &anim_id, std::string &anim_attribute_type, std::string &anim_attribute_value);

      protected:
      private:
        struct SpriteAttributes {
            std::string _spritesheet;
            std::pair<graphics::SpriteTypes, std::size_t> _sprite_type_and_id;
            std::unordered_map<std::size_t, std::vector<std::optional<std::size_t>>> _animations;
        };
        std::vector<std::string> _textures_path;
        std::vector<SpriteAttributes> _sprites_data;

        std::unordered_map<std::string, graphics::SpriteTypes> _matching_string_with_sprite_types{
            {"spaceship", graphics::SpriteTypes::spaceship}, {"monster", graphics::SpriteTypes::monster}};

        std::unordered_map<std::string, graphics::SpriteTypeAttributes> _matching_string_with_sprite_type_attributes{
            {"anim", graphics::SpriteTypeAttributes::anim}};

        std::unordered_map<std::string, graphics::SpriteAnimAttributes> _matching_string_with_sprite_anim_attributes{
            {"rect_x", graphics::SpriteAnimAttributes::rect_x}, {"rect_y", graphics::SpriteAnimAttributes::rect_y},
            {"rect_width", graphics::SpriteAnimAttributes::rect_width}, {"rect_height", graphics::SpriteAnimAttributes::rect_height},
            {"nb_anim", graphics::SpriteAnimAttributes::nb_anim}, {"next_anim", graphics::SpriteAnimAttributes::next_anim}};
    };
} // namespace graphics

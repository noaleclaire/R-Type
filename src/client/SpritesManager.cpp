/*
** EPITECH PROJECT, 2022
** SpritesManager
** File description:
** SpritesManager
*/

#include "SpritesManager.hpp"
#include <algorithm>
#include "Exceptions/ExceptionNotAnInteger.hpp"

namespace graphics
{
    SpritesManager::SpritesManager()
    {
    }

    SpritesManager::~SpritesManager()
    {
    }

    bool SpritesManager::isSpriteTypes(std::string &sprite_type)
    {
        auto res = _matching_string_with_sprite_types.find(sprite_type);

        if (res != _matching_string_with_sprite_types.end())
            return (true);
        return (false);
    }

    bool SpritesManager::isSpriteTypeAttributes(std::string &sprite_type_attribute)
    {
        auto res = _matching_string_with_sprite_type_attributes.find(sprite_type_attribute);

        if (res != _matching_string_with_sprite_type_attributes.end())
            return (true);
        return (false);
    }

    bool SpritesManager::isSpriteAnimAttributes(std::string &sprite_anim_attribute)
    {
        auto res = _matching_string_with_sprite_anim_attributes.find(sprite_anim_attribute);

        if (res != _matching_string_with_sprite_anim_attributes.end())
            return (true);
        return (false);
    }

    graphics::SpriteTypes SpritesManager::getSpriteType(std::string &sprite_type) const
    {
        return (_matching_string_with_sprite_types.at(sprite_type));
    }

    graphics::SpriteTypeAttributes SpritesManager::getSpriteTypeAttribute(std::string &sprite_type_attribute) const
    {
        return (_matching_string_with_sprite_type_attributes.at(sprite_type_attribute));
    }

    graphics::SpriteAnimAttributes SpritesManager::getSpriteAnimAttribute(std::string &sprite_anim_attribute) const
    {
        return (_matching_string_with_sprite_anim_attributes.at(sprite_anim_attribute));
    }

    void SpritesManager::addTexturePath(std::string &texture_path)
    {
        _textures_path.push_back(texture_path);
    }

    void SpritesManager::addSpriteData1(std::string &spritesheet, std::string &sprite_type, std::string &sprite_type_id)
    {
        std::size_t pos{};
        try {
            int _sprite_type_id{std::stoi(sprite_type_id, &pos)};
            _sprites_data.push_back({spritesheet, std::make_pair(getSpriteType(sprite_type), _sprite_type_id)});
        } catch (const std::invalid_argument &e) {
            throw ExceptionNotAnInteger("the id of the sprite : " + sprite_type + " is not an integer",
                "void SpritesManager::addSpriteData1(std::string &spritesheet, std::string &sprite_type, std::string &sprite_type_id)");
        }
    }

    void SpritesManager::addSpriteData2(std::string &sprite_type, std::string &sprite_type_id, std::string &anim_id)
    {
        std::size_t pos{};
        try {
            int _anim_id = {std::stoi(anim_id, &pos)};
            for (auto &it : _sprites_data) {
                if (it._sprite_type_and_id.first == getSpriteType(sprite_type) && it._sprite_type_and_id.second == std::stoi(sprite_type_id, &pos)) {
                    it._animations.emplace(_anim_id, std::vector<std::optional<std::size_t>>(NB_ANIM_ATTRIBUTES, std::nullopt));
                    break;
                }
            }
        } catch (const std::invalid_argument &e) {
            throw ExceptionNotAnInteger("the id of the anim of the sprite : " + sprite_type + " is not an integer",
                "void SpritesManager::addSpriteData2(std::string &sprite_type, std::string &sprite_type_id, std::string &anim_id)");
        }
    }

    void SpritesManager::addSpriteData3(
        std::string &sprite_type, std::string &sprite_type_id, std::string &anim_id, std::string &anim_attribute_type, std::string &anim_attribute_value)
    {
        std::size_t pos{};
        try {
            int _anim_attribute_value{std::stoi(anim_attribute_value, &pos)};
            for (auto &it : _sprites_data) {
                if (it._sprite_type_and_id.first == getSpriteType(sprite_type) && it._sprite_type_and_id.second == std::stoi(sprite_type_id, &pos)) {
                    it._animations.at(std::stoi(anim_id, &pos)).at(getSpriteAnimAttribute(anim_attribute_type)) = _anim_attribute_value;
                    break;
                }
            }
        } catch (const std::invalid_argument &e) {
            throw ExceptionNotAnInteger("the value of the anim attribute : " + anim_attribute_type + " is not an integer",
                "void SpritesManager::addSpriteData3(std::string &sprite_type, std::string &sprite_type_id, std::string &anim_attribute_type, std::string "
                "&anim_attribute_value)");
        }
    }
} // namespace graphics

/*
** EPITECH PROJECT, 2022
** SpritesManager
** File description:
** SpritesManager
*/

#include "SpritesManager.hpp"
#include <algorithm>
#include <iostream>
#include "../Exceptions/ExceptionBadAnyCast.hpp"
#include "../Exceptions/ExceptionNoAnimAttribute.hpp"
#include "../Exceptions/ExceptionNoSpriteAnim.hpp"
#include "../Exceptions/ExceptionNotANumber.hpp"

SpritesManager::SpritesManager()
{
    _sprites_config_words = {{std::make_pair("spritesheet", std::nullopt)},
        {std::make_pair("spaceship", ecs::EntityTypes::SPACESHIP), std::make_pair("monster", ecs::EntityTypes::MONSTER),
            std::make_pair("background", ecs::EntityTypes::BACKGROUND), std::make_pair("button", ecs::EntityTypes::BUTTON),
            std::make_pair("wall", ecs::EntityTypes::WALL)},
        {std::make_pair("anim", SpriteTypeAttributes::anim)},
        {std::make_pair("rect_x", SpriteAnimAttributes::rect_x), std::make_pair("rect_y", SpriteAnimAttributes::rect_y),
            std::make_pair("rect_width", SpriteAnimAttributes::rect_width), std::make_pair("rect_height", SpriteAnimAttributes::rect_height),
            std::make_pair("nb_anim", SpriteAnimAttributes::nb_anim), std::make_pair("next_anim", SpriteAnimAttributes::next_anim)}};

    initMapFunctionPointer();
}

SpritesManager::~SpritesManager()
{
}

void SpritesManager::initMapFunctionPointer()
{
    _map_fptr.insert("spritesheet", &SpritesManager::addTexturePath);

    _map_fptr.insert("spaceship", &SpritesManager::addSpriteTypeId);
    _map_fptr.insert("monster", &SpritesManager::addSpriteTypeId);
    _map_fptr.insert("background", &SpritesManager::addSpriteTypeId);
    _map_fptr.insert("button", &SpritesManager::addSpriteTypeId);
    _map_fptr.insert("wall", &SpritesManager::addSpriteTypeId);

    _map_fptr.insert("anim", &SpritesManager::addSpriteAnim);
    _map_fptr.insert("rect_x", &SpritesManager::addSpriteAnimAttributes);
    _map_fptr.insert("rect_y", &SpritesManager::addSpriteAnimAttributes);
    _map_fptr.insert("rect_width", &SpritesManager::addSpriteAnimAttributes);
    _map_fptr.insert("rect_height", &SpritesManager::addSpriteAnimAttributes);
    _map_fptr.insert("nb_anim", &SpritesManager::addSpriteAnimAttributes);
    _map_fptr.insert("next_anim", &SpritesManager::addSpriteAnimAttributes);
}

void SpritesManager::executeMapMemberFunctionPointer(std::string &sprite_config_word, std::string &value)
{
    _map_fptr.searchAndCall<void, SpritesManager *>(this, sprite_config_word, sprite_config_word, value);
}

ecs::EntityTypes SpritesManager::getSpriteType(std::string &sprite_type) const
{
    try {
        for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
            for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                if (_sprites_config_words.at(i).at(j).first.compare(sprite_type) == 0) {
                    std::any_cast<ecs::EntityTypes>(_sprites_config_words.at(i).at(j).second);
                    return (std::any_cast<ecs::EntityTypes>(_sprites_config_words.at(i).at(j).second));
                }
            }
        }
    } catch (const std::bad_any_cast &e) {
        throw ExceptionBadAnyCast("Cannot convert to SpriteTypes", "SpriteTypes SpritesManager::getSpriteType(std::string &sprite_type) const");
    }
    return (ecs::EntityTypes::SPACESHIP);
}

std::string const SpritesManager::getSpriteType(ecs::EntityTypes sprite_type) const
{
    for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
        for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
            try {
                if (std::any_cast<ecs::EntityTypes>(_sprites_config_words.at(i).at(j).second) == sprite_type)
                    return (_sprites_config_words.at(i).at(j).first);
            } catch (const std::bad_any_cast &e) {
                continue;
            }
        }
    }
    return ("");
}

SpriteTypeAttributes SpritesManager::getSpriteTypeAttribute(std::string &sprite_type_attribute) const
{
    try {
        for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
            for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                if (_sprites_config_words.at(i).at(j).first.compare(sprite_type_attribute) == 0) {
                    std::any_cast<SpriteTypeAttributes>(_sprites_config_words.at(i).at(j).second);
                    return (std::any_cast<SpriteTypeAttributes>(_sprites_config_words.at(i).at(j).second));
                }
            }
        }
    } catch (const std::bad_any_cast &e) {
        throw ExceptionBadAnyCast(
            "Cannot convert to SpriteTypeAttributes", "SpriteTypeAttributes SpritesManager::getSpriteTypeAttribute(std::string &sprite_type_attribute) const");
    }
    return (SpriteTypeAttributes::anim);
}

std::string const SpritesManager::getSpriteTypeAttribute(SpriteTypeAttributes sprite_type_attribute) const
{
    for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
        for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
            try {
                if (std::any_cast<SpriteTypeAttributes>(_sprites_config_words.at(i).at(j).second) == sprite_type_attribute)
                    return (_sprites_config_words.at(i).at(j).first);
            } catch (const std::bad_any_cast &e) {
                continue;
            }
        }
    }
    return ("");
}

SpriteAnimAttributes SpritesManager::getSpriteAnimAttribute(std::string &sprite_anim_attribute) const
{
    try {
        for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
            for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                if (_sprites_config_words.at(i).at(j).first.compare(sprite_anim_attribute) == 0) {
                    std::any_cast<SpriteAnimAttributes>(_sprites_config_words.at(i).at(j).second);
                    return (std::any_cast<SpriteAnimAttributes>(_sprites_config_words.at(i).at(j).second));
                }
            }
        }
    } catch (const std::bad_any_cast &e) {
        throw ExceptionBadAnyCast(
            "Cannot convert to SpriteAnimAttributes", "SpriteAnimAttributes SpritesManager::getSpriteAnimAttribute(std::string &sprite_anim_attribute) const");
    }
    return (SpriteAnimAttributes::next_anim);
}

std::string const SpritesManager::getSpriteAnimAttribute(SpriteAnimAttributes sprite_anim_attribute) const
{
    for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
        for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
            try {
                if (std::any_cast<SpriteAnimAttributes>(_sprites_config_words.at(i).at(j).second) == sprite_anim_attribute)
                    return (_sprites_config_words.at(i).at(j).first);
            } catch (const std::bad_any_cast &e) {
                continue;
            }
        }
    }
    return ("");
}

void SpritesManager::addTexturePath(std::string &key_word, std::string &texture_path)
{
    if (key_word.empty())
        return;
    _textures_path.push_back(texture_path);
    _spritesheet_tmp = texture_path;
}

void SpritesManager::addSpriteTypeId(std::string &sprite_type, std::string &sprite_type_id)
{
    std::size_t pos{};
    try {
        _sprite_type_id_tmp = std::stoi(sprite_type_id, &pos);
        _sprite_type_tmp = getSpriteType(sprite_type);
        _sprites_data.push_back(
            {_spritesheet_tmp, std::make_pair(_sprite_type_tmp, _sprite_type_id_tmp), std::unordered_map<std::size_t, std::vector<std::optional<int>>>{}});
    } catch (const std::invalid_argument &e) {
        throw ExceptionNotANumber(
            "the id of the sprite is not an integer", "void SpritesManager::addSpriteTypeId(std::string &sprite_type, std::string &sprite_type_id)");
    }
}

void SpritesManager::addSpriteAnim(std::string &sprite_type_anim, std::string &sprite_type_anim_id)
{
    if (sprite_type_anim.empty())
        return;
    std::size_t pos{};
    try {
        _sprite_type_anim_id_tmp = std::stoi(sprite_type_anim_id, &pos);
        for (auto &it : _sprites_data) {
            if (it._sprite_type_and_id.first == _sprite_type_tmp && it._sprite_type_and_id.second == _sprite_type_id_tmp) {
                it._animations.emplace(_sprite_type_anim_id_tmp, std::vector<std::optional<int>>(NB_ANIM_ATTRIBUTES, std::nullopt));
                break;
            }
        }
    } catch (const std::invalid_argument &e) {
        throw ExceptionNotANumber("the id of the anim of the sprite is not an integer",
            "void SpritesManager::addSpriteAnim(std::string &sprite_type_anim, std::string &sprite_type_anim_id)");
    }
}

void SpritesManager::addSpriteAnimAttributes(std::string &anim_attribute_type, std::string &anim_attribute_value)
{
    std::size_t pos{};
    try {
        int _anim_attribute_value{std::stoi(anim_attribute_value, &pos)};
        for (auto &it : _sprites_data) {
            if (it._sprite_type_and_id.first == _sprite_type_tmp && it._sprite_type_and_id.second == _sprite_type_id_tmp) {
                it._animations.at(_sprite_type_anim_id_tmp).at(getSpriteAnimAttribute(anim_attribute_type)) = _anim_attribute_value;
                break;
            }
        }
    } catch (const std::invalid_argument &e) {
        throw ExceptionNotANumber("the value of the anim attribute is not an integer",
            "void SpritesManager::addSpriteAnimAttributes(std::string &anim_attribute_type, std::string &anim_attribute_value)");
    }
}

std::vector<std::string> const SpritesManager::getTexturePath() const
{
    return (_textures_path);
}

void SpritesManager::printSpritesData()
{
    for (std::size_t i = 0; i < _sprites_data.size(); i++) {
        std::cout << getSpriteType(_sprites_data.at(i)._sprite_type_and_id.first) << " : " << _sprites_data.at(i)._sprite_type_and_id.second << std::endl;
        for (auto &it : _sprites_data.at(i)._animations) {
            std::cout << getSpriteTypeAttribute(SpriteTypeAttributes::anim) << " : " << it.first << std::endl;
            for (std::size_t j = 0; j < it.second.size(); j++) {
                if (it.second.at(j))
                    std::cout << getSpriteAnimAttribute(static_cast<SpriteAnimAttributes>(j)) << " : " << it.second.at(j).value() << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

std::vector<float> SpritesManager::get_Animations_rect(ecs::EntityTypes entity_type, std::size_t entity_id, std::size_t anim_id)
{
    std::vector<float> attrs;
    try {
        for (auto &it : _sprites_data) {
            if (it._sprite_type_and_id.first == entity_type && it._sprite_type_and_id.second == entity_id) {
                if (it._animations.at(anim_id).at(rect_x) && it._animations.at(anim_id).at(rect_y) && it._animations.at(anim_id).at(rect_width)
                    && it._animations.at(anim_id).at(rect_height)) {
                    attrs.push_back(it._animations.at(anim_id).at(rect_x).value());
                    attrs.push_back(it._animations.at(anim_id).at(rect_y).value());
                    attrs.push_back(it._animations.at(anim_id).at(rect_width).value());
                    attrs.push_back(it._animations.at(anim_id).at(rect_height).value());
                    return (attrs);
                } else
                    throw ExceptionNoAnimAttribute("No value for one or more of the anim attributes rect",
                        "std::size_t SpritesManager::get_Animations(ecs::EntityTypes entity_type, std::size_t entity_id, SpriteAnimAttributes attr)");
            }
        }
    } catch (const std::out_of_range &e) {
        throw ExceptionNoSpriteAnim("No sprite anim in SpriteData",
            "std::size_t SpritesManager::get_Animations(ecs::EntityTypes entity_type, std::size_t entity_id, SpriteAnimAttributes attr)");
    }
    return (attrs);
}

std::string SpritesManager::get_Spritesheet(ecs::EntityTypes entity_type, std::size_t entity_id)
{
    for (auto &it : _sprites_data) {
        if (it._sprite_type_and_id.first == entity_type && it._sprite_type_and_id.second == entity_id) {
            return (it._spritesheet);
        }
    }
    return ("");
}

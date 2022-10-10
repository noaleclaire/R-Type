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
#include "../Exceptions/ExceptionNotAnInteger.hpp"

namespace graphics
{
    SpritesManager::SpritesManager()
    {
        _sprites_config_words = {{std::make_pair("spritesheet", std::nullopt)},
            {std::make_pair("spaceship", graphics::SpriteTypes::spaceship), std::make_pair("monster", graphics::SpriteTypes::monster)},
            {std::make_pair("anim", graphics::SpriteTypeAttributes::anim)},
            {std::make_pair("rect_x", graphics::SpriteAnimAttributes::rect_x), std::make_pair("rect_y", graphics::SpriteAnimAttributes::rect_y),
                std::make_pair("rect_width", graphics::SpriteAnimAttributes::rect_width),
                std::make_pair("rect_height", graphics::SpriteAnimAttributes::rect_height), std::make_pair("nb_anim", graphics::SpriteAnimAttributes::nb_anim),
                std::make_pair("next_anim", graphics::SpriteAnimAttributes::next_anim)}};

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

    graphics::SpriteTypes SpritesManager::getSpriteType(std::string &sprite_type) const
    {
        try {
            for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
                for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                    if (_sprites_config_words.at(i).at(j).first.compare(sprite_type) == 0) {
                        std::any_cast<graphics::SpriteTypes>(_sprites_config_words.at(i).at(j).second);
                        return (std::any_cast<graphics::SpriteTypes>(_sprites_config_words.at(i).at(j).second));
                    }
                }
            }
        } catch (const std::bad_any_cast &e) {
            throw ExceptionBadAnyCast(
                "Cannot convert to graphics::SpriteTypes", "graphics::SpriteTypes SpritesManager::getSpriteType(std::string &sprite_type) const");
        }
        return (graphics::SpriteTypes::spaceship);
    }

    std::string const SpritesManager::getSpriteType(graphics::SpriteTypes sprite_type) const
    {
        for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
            for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                try {
                    if (std::any_cast<graphics::SpriteTypes>(_sprites_config_words.at(i).at(j).second) == sprite_type)
                        return (_sprites_config_words.at(i).at(j).first);
                } catch (const std::bad_any_cast &e) {
                    continue;
                }
            }
        }
        return ("");
    }

    graphics::SpriteTypeAttributes SpritesManager::getSpriteTypeAttribute(std::string &sprite_type_attribute) const
    {
        try {
            for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
                for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                    if (_sprites_config_words.at(i).at(j).first.compare(sprite_type_attribute) == 0) {
                        std::any_cast<graphics::SpriteTypeAttributes>(_sprites_config_words.at(i).at(j).second);
                        return (std::any_cast<graphics::SpriteTypeAttributes>(_sprites_config_words.at(i).at(j).second));
                    }
                }
            }
        } catch (const std::bad_any_cast &e) {
            throw ExceptionBadAnyCast("Cannot convert to graphics::SpriteTypeAttributes",
                "graphics::SpriteTypeAttributes SpritesManager::getSpriteTypeAttribute(std::string &sprite_type_attribute) const");
        }
        return (graphics::SpriteTypeAttributes::anim);
    }

    std::string const SpritesManager::getSpriteTypeAttribute(graphics::SpriteTypeAttributes sprite_type_attribute) const
    {
        for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
            for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                try {
                    if (std::any_cast<graphics::SpriteTypeAttributes>(_sprites_config_words.at(i).at(j).second) == sprite_type_attribute)
                        return (_sprites_config_words.at(i).at(j).first);
                } catch (const std::bad_any_cast &e) {
                    continue;
                }
            }
        }
        return ("");
    }

    graphics::SpriteAnimAttributes SpritesManager::getSpriteAnimAttribute(std::string &sprite_anim_attribute) const
    {
        try {
            for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
                for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                    if (_sprites_config_words.at(i).at(j).first.compare(sprite_anim_attribute) == 0) {
                        std::any_cast<graphics::SpriteAnimAttributes>(_sprites_config_words.at(i).at(j).second);
                        return (std::any_cast<graphics::SpriteAnimAttributes>(_sprites_config_words.at(i).at(j).second));
                    }
                }
            }
        } catch (const std::bad_any_cast &e) {
            throw ExceptionBadAnyCast("Cannot convert to graphics::SpriteAnimAttributes",
                "graphics::SpriteAnimAttributes SpritesManager::getSpriteAnimAttribute(std::string &sprite_anim_attribute) const");
        }
        return (graphics::SpriteAnimAttributes::next_anim);
    }

    std::string const SpritesManager::getSpriteAnimAttribute(graphics::SpriteAnimAttributes sprite_anim_attribute) const
    {
        for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
            for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                try {
                    if (std::any_cast<graphics::SpriteAnimAttributes>(_sprites_config_words.at(i).at(j).second) == sprite_anim_attribute)
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
            _sprites_data.push_back({_spritesheet_tmp, std::make_pair(_sprite_type_tmp, _sprite_type_id_tmp),
                std::unordered_map<std::size_t, std::vector<std::optional<std::size_t>>>{}});
        } catch (const std::invalid_argument &e) {
            throw ExceptionNotAnInteger(
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
                    it._animations.emplace(_sprite_type_anim_id_tmp, std::vector<std::optional<std::size_t>>(NB_ANIM_ATTRIBUTES, std::nullopt));
                    break;
                }
            }
        } catch (const std::invalid_argument &e) {
            throw ExceptionNotAnInteger("the id of the anim of the sprite is not an integer",
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
            throw ExceptionNotAnInteger("the value of the anim attribute is not an integer",
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
                std::cout << getSpriteTypeAttribute(graphics::anim) << " : " << it.first << std::endl;
                for (std::size_t j = 0; j < it.second.size(); j++) {
                    if (it.second.at(j))
                        std::cout << getSpriteAnimAttribute(static_cast<graphics::SpriteAnimAttributes>(j)) << " : " << it.second.at(j).value() << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }
} // namespace graphics

/*
** EPITECH PROJECT, 2022
** LevelManager
** File description:
** LevelManager
*/

#include "LevelManager.hpp"
#include "Exceptions/Exception.hpp"
#include <algorithm>
#include <iostream>

LevelManager::LevelManager()
{
    _sprites_config_words = {{std::make_pair("spaceship", ecs::EntityTypes::SPACESHIP), std::make_pair("monster", ecs::EntityTypes::MONSTER),
            std::make_pair("shot", ecs::EntityTypes::SHOT), std::make_pair("background", ecs::EntityTypes::BACKGROUND),
            std::make_pair("button", ecs::EntityTypes::BUTTON), std::make_pair("room", ecs::EntityTypes::ROOM),
            std::make_pair("wall", ecs::EntityTypes::WALL), std::make_pair("textbox", ecs::EntityTypes::TEXTBOX),
            std::make_pair("roommode", ecs::EntityTypes::ROOMMODE)},
        {std::make_pair("time", EntityAttributes::spawn_time), std::make_pair("position_x", EntityAttributes::position_x),
            std::make_pair("position_y", EntityAttributes::position_y), std::make_pair("velocity_x", EntityAttributes::velocity_x),
            std::make_pair("velocity_y", EntityAttributes::velocity_y), std::make_pair("shooter", EntityAttributes::shooter)}};

    initMapFunctionPointer();
}

LevelManager::~LevelManager()
{
}

void LevelManager::initMapFunctionPointer()
{
    _map_fptr.insert("spaceship", &LevelManager::addEntityTypeId);
    _map_fptr.insert("monster", &LevelManager::addEntityTypeId);
    _map_fptr.insert("shot", &LevelManager::addEntityTypeId);
    _map_fptr.insert("background", &LevelManager::addEntityTypeId);
    _map_fptr.insert("button", &LevelManager::addEntityTypeId);
    _map_fptr.insert("room", &LevelManager::addEntityTypeId);
    _map_fptr.insert("wall", &LevelManager::addEntityTypeId);
    _map_fptr.insert("textbox", &LevelManager::addEntityTypeId);
    _map_fptr.insert("roommode", &LevelManager::addEntityTypeId);

    _map_fptr.insert("time", &LevelManager::addEntityAttribute);
    _map_fptr.insert("position_x", &LevelManager::addEntityAttribute);
    _map_fptr.insert("position_y", &LevelManager::addEntityAttribute);
    _map_fptr.insert("velocity_x", &LevelManager::addEntityAttribute);
    _map_fptr.insert("velocity_y", &LevelManager::addEntityAttribute);
    _map_fptr.insert("shooter", &LevelManager::addEntityAttribute);
}

void LevelManager::executeMapMemberFunctionPointer(std::string &entity_config_word, std::string &value)
{
    _map_fptr.searchAndCall<void, LevelManager *>(this, entity_config_word, entity_config_word, value);
}

ecs::EntityTypes LevelManager::getEntityType(std::string &entity_type) const
{
    try {
        for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
            for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                if (_sprites_config_words.at(i).at(j).first.compare(entity_type) == 0) {
                    std::any_cast<ecs::EntityTypes>(_sprites_config_words.at(i).at(j).second);
                    return (std::any_cast<ecs::EntityTypes>(_sprites_config_words.at(i).at(j).second));
                }
            }
        }
    } catch (const std::bad_any_cast &e) {
        throw Exception("Cannot convert to EntityTypes", "ecs::EntityTypes LevelManager::getEntityType(std::string &entity_type) const");
    }
    return (ecs::EntityTypes::SPACESHIP);
}

std::string const LevelManager::getEntityType(ecs::EntityTypes sprite_type) const
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

EntityAttributes LevelManager::getEntityAttribute(std::string &entity_attribute) const
{
    try {
        for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
            for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
                if (_sprites_config_words.at(i).at(j).first.compare(entity_attribute) == 0) {
                    std::any_cast<EntityAttributes>(_sprites_config_words.at(i).at(j).second);
                    return (std::any_cast<EntityAttributes>(_sprites_config_words.at(i).at(j).second));
                }
            }
        }
    } catch (const std::bad_any_cast &e) {
        throw Exception(
            "Cannot convert to EntityAttributes", "EntityAttributes LevelManager::getEntityAttribute(std::string &entity_attribute) const");
    }
    return (EntityAttributes::spawn_time);
}

std::string const LevelManager::getEntityAttribute(EntityAttributes entity_attribute) const
{
    for (std::size_t i = 0; i < _sprites_config_words.size(); i++) {
        for (std::size_t j = 0; j < _sprites_config_words.at(i).size(); j++) {
            try {
                if (std::any_cast<EntityAttributes>(_sprites_config_words.at(i).at(j).second) == entity_attribute)
                    return (_sprites_config_words.at(i).at(j).first);
            } catch (const std::bad_any_cast &e) {
                continue;
            }
        }
    }
    return ("");
}

int LevelManager::getEntityAttributeValue(std::size_t entity, EntityAttributes entity_attribute) const
{
    return (_entity_data.at(entity)._attributes.at(entity_attribute).value());
}

std::vector<std::pair<ecs::EntityTypes, std::size_t>> LevelManager::getEntitiesTypeAndId() const
{
    std::vector<std::pair<ecs::EntityTypes, std::size_t>> allTypeAndId = {};

    for (auto &it : _entity_data) {
        allTypeAndId.push_back(it._entity_type_and_id);
    }
    return (allTypeAndId);
}

void LevelManager::addEntityTypeId(std::string &entity_type, std::string &entity_type_id)
{
    try {
        _entity_type_id_tmp = std::stoi(entity_type_id);
        _entity_type_tmp = getEntityType(entity_type);
        for (auto &it : _entity_data) {
            if (it._entity_type_and_id.first == _entity_type_tmp && it._entity_type_and_id.second == _entity_type_id_tmp)
                throw Exception("the id of this type of entity : " + entity_type + " already exists", "void LevelManager::addEntityTypeId(std::string &entity_type, std::string &entity_type_id)");
        }
        _entity_data.push_back({std::make_pair(_entity_type_tmp, _entity_type_id_tmp), std::vector<std::optional<int>>(NB_ENTITY_ATTRIBUTES, std::nullopt)});
    } catch (const std::invalid_argument &e) {
        throw Exception(
            "the id of the entity type : " + entity_type + " is not an integer", "void LevelManager::addEntityTypeId(std::string &entity_type, std::string &entity_type_id)");
    }
}

void LevelManager::addEntityAttribute(std::string &entity_attribute_type, std::string &entity_attribute_value)
{
    try {
        int _entity_attribute_value = std::stoi(entity_attribute_value);
        for (auto &it : _entity_data) {
            if (it._entity_type_and_id.first == _entity_type_tmp && it._entity_type_and_id.second == _entity_type_id_tmp) {
                it._attributes.at(getEntityAttribute(entity_attribute_type)) = _entity_attribute_value;
                break;
            }
        }
    } catch (const std::invalid_argument &e) {
        throw Exception("the value of the anim attribute is not an integer",
            "void SpritesManager::addSpriteAnimAttributes(std::string &anim_attribute_type, std::string &anim_attribute_value)");
    }
}

void LevelManager::printEntitiesData()
{
    for (auto &it : _entity_data) {
        std::cout << getEntityType(it._entity_type_and_id.first) << " : " << it._entity_type_and_id.second << std::endl;
        for (std::size_t j = 0; j < it._attributes.size(); j++) {
            if (it._attributes.at(j))
                std::cout << getEntityAttribute(static_cast<EntityAttributes>(j)) << " : " << it._attributes.at(j).value() << std::endl;
        }
    }
    std::cout << std::endl;
}
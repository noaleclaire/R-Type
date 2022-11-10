/*
** EPITECH PROJECT, 2022
** LevelManager
** File description:
** LevelManager
*/

#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "../Ecs/Enum.hpp"
#include "AYamlConfig.hpp"
#include "MapMemberFunctionPointer.hpp"
#include <unordered_map>

#define NB_ENTITY_ATTRIBUTES 6

enum EntityAttributes { spawn_time, position_x, position_y, velocity_x, velocity_y, shooter };

class LevelManager : public AYamlConfig {
  public:

    /**
     * @brief Construct a new Level Manager object
     *
     */
    LevelManager();
    /**
     * @brief Destroy the Level Manager object
     *
     */
    ~LevelManager();
    /**
     * @brief
     *
     * @param entity_config_word
     * @param value
     */
    void executeMapMemberFunctionPointer(std::string &entity_config_word, std::string &value);
    /**
     * @brief Get the Entity Type object
     *
     * @param entity_type
     * @return ecs::EntityTypes
     */
    ecs::EntityTypes getEntityType(std::string &entity_type) const;
    /**
     * @brief Get the Entity Type object
     *
     * @param entity_type
     * @return std::string const
     */
    std::string const getEntityType(ecs::EntityTypes entity_type) const;
    /**
     * @brief Get the Entity Attribute object
     *
     * @param entity_attribute
     * @return EntityAttributes
     */
    EntityAttributes getEntityAttribute(std::string &entity_attribute) const;
    /**
     * @brief Get the Entity Attribute object
     *
     * @param entity_attribute
     * @return std::string const
     */
    std::string const getEntityAttribute(EntityAttributes entity_attribute) const;
    /**
     * @brief Get the Entity Attribute value object
     *
     * @param entity
     * @param entity_attribute
     * @return float
     */
    int getEntityAttributeValue(std::size_t entity, EntityAttributes entity_attribute) const;
    /**
     * @brief Get all Entities Type and Id object
     *
     * @return std::vector<std::pair<ecs::EntityTypes, std::size_t>>
     */
    std::vector<std::pair<ecs::EntityTypes, std::size_t>> getEntitiesTypeAndId() const;
    /**
     * @brief
     *
     * @param entity_type
     * @param entity_type_id
     */
    void addEntityTypeId(std::string &entity_type, std::string &entity_type_id);
    /**
     * @brief
     *
     * @param entity_attribute_type
     * @param entity_attribute_value
     */
    void addEntityAttribute(std::string &entity_attribute_type, std::string &entity_attribute_value);
    /**
     * @brief
     *
     */
    void printEntitiesData();

  protected:
  private:
    typedef void (LevelManager::*MAP_FPTR)(std::string &, std::string &);
    MapMemberFunctionPointer<MAP_FPTR> _map_fptr;
    /**
     * @brief
     *
     */
    void initMapFunctionPointer();

    struct EntityData {
        std::pair<ecs::EntityTypes, std::size_t> _entity_type_and_id;
        std::vector<std::optional<int>> _attributes;
    };
    std::vector<EntityData> _entity_data;
    ecs::EntityTypes _entity_type_tmp;
    long unsigned int _entity_type_id_tmp;
};

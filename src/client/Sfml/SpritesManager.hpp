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
#include "../../Ecs/Registry.hpp"
#include "../../Utilities/AYamlConfig.hpp"
#include "../../Utilities/MapMemberFunctionPointer.hpp"
#include <unordered_map>

#define NB_ANIM_ATTRIBUTES (6)

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
     * @return ecs::EntityTypes
     */
    ecs::EntityTypes getSpriteType(std::string &sprite_type) const;
    /**
     * @brief Get the Sprite Type object
     *
     * @param sprite_type
     * @return std::string const
     */
    std::string const getSpriteType(ecs::EntityTypes sprite_type) const;
    /**
     * @brief Get the Sprite Type Attribute object
     *
     * @param sprite_type_attribute
     * @return SpriteTypeAttributes
     */

    SpriteTypeAttributes getSpriteTypeAttribute(std::string &sprite_type_attribute) const;
    /**
     * @brief Get the Sprite Type Attribute object
     *
     * @param sprite_type_attribute
     * @return std::string const
     */
    std::string const getSpriteTypeAttribute(SpriteTypeAttributes sprite_type_attribute) const;
    /**
     * @brief Get the Sprite Anim Attribute object
     *
     * @param sprite_anim_attribute
     * @return SpriteAnimAttributes
     */
    SpriteAnimAttributes getSpriteAnimAttribute(std::string &sprite_anim_attribute) const;
    /**
     * @brief Get the Sprite Anim Attribute object
     *
     * @param sprite_anim_attribute
     * @return std::string const
     */
    std::string const getSpriteAnimAttribute(SpriteAnimAttributes sprite_anim_attribute) const;
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
    /**
     * @brief Get the Animations rect object
     *
     * @param entity_type
     * @param entity_id
     * @param anim_id
     * @return std::vector<float>
     */
    std::vector<float> get_Animations_rect(ecs::EntityTypes entity_type, std::size_t entity_id, std::size_t anim_id);
    /**
     * @brief Get the Spritesheet object
     *
     * @param entity_type
     * @param entity_id
     * @return std::string
     */
    std::string get_Spritesheet(ecs::EntityTypes entity_type, std::size_t entity_id);
    /**
     * @brief
     *
     */
    void printSpritesData();

  protected:
  private:
    typedef void (SpritesManager::*MAP_FPTR)(std::string &, std::string &);
    MapMemberFunctionPointer<MAP_FPTR> _map_fptr;
    /**
     * @brief
     *
     */
    void initMapFunctionPointer();

    struct SpriteData {
        std::string _spritesheet;
        std::pair<ecs::EntityTypes, std::size_t> _sprite_type_and_id;
        std::unordered_map<std::size_t, std::vector<std::optional<int>>> _animations;
    };
    std::vector<SpriteData> _sprites_data;
    std::vector<std::string> _textures_path;

    std::string _spritesheet_tmp = "";
    ecs::EntityTypes _sprite_type_tmp;
    long unsigned int _sprite_type_id_tmp;
    long unsigned int _sprite_type_anim_id_tmp;
};

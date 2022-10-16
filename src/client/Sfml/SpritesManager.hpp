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
#include <unordered_map>
#include "../../Utilities/AYamlConfig.hpp"
#include "../../Utilities/MapMemberFunctionPointer.hpp"
#include "../../Ecs/Registry.hpp"

#define NB_ANIM_ATTRIBUTES (6)

enum SpriteTypeAttributes { anim };
enum SpriteAnimAttributes { rect_x, rect_y, rect_width, rect_height, nb_anim, next_anim };

class SpritesManager : public AYamlConfig {
  public:
    SpritesManager();
    ~SpritesManager();

    void executeMapMemberFunctionPointer(std::string &sprite_config_word, std::string &value);

    ecs::EntityTypes getSpriteType(std::string &sprite_type) const;
    std::string const getSpriteType(ecs::EntityTypes sprite_type) const;

    SpriteTypeAttributes getSpriteTypeAttribute(std::string &sprite_type_attribute) const;
    std::string const getSpriteTypeAttribute(SpriteTypeAttributes sprite_type_attribute) const;

    SpriteAnimAttributes getSpriteAnimAttribute(std::string &sprite_anim_attribute) const;
    std::string const getSpriteAnimAttribute(SpriteAnimAttributes sprite_anim_attribute) const;

    void addTexturePath(std::string &key_word, std::string &texture_path);
    void addSpriteTypeId(std::string &sprite_type, std::string &sprite_type_id);
    void addSpriteAnim(std::string &sprite_type_anim, std::string &sprite_type_anim_id);
    void addSpriteAnimAttributes(std::string &anim_attribute_type, std::string &anim_attribute_value);

    std::vector<std::string> const getTexturePath() const;
    std::vector<float> get_Animations_rect(ecs::EntityTypes entity_type, std::size_t entity_id);
    std::string get_Spritesheet(ecs::EntityTypes entity_type, std::size_t entity_id);
    void printSpritesData();

  protected:
  private:
    typedef void (SpritesManager::*MAP_FPTR)(std::string &, std::string &);
    MapMemberFunctionPointer<MAP_FPTR> _map_fptr;
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

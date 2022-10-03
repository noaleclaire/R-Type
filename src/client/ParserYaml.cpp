/*
** EPITECH PROJECT, 2022
** ParserYaml
** File description:
** ParserYaml
*/

#include "ParserYaml.hpp"
#include <filesystem>
#include <fstream>
#include <vector>
#include "Exceptions/ExceptionBadFileName.hpp"
#include "Exceptions/ExceptionFileNotFound.hpp"

void ParserYaml::ParseSpritesConfig(graphics::SpritesManager &manager)
{
    std::ifstream file(std::filesystem::current_path() / "assets/sprites/sprites_config.yaml", std::ios::in);
    std::string line;
    bool spritesheet_b = false;
    bool sprite_type_b = false;
    bool anim_b = false;
    std::string spritesheet = "";
    std::string sprite_type = "";
    std::string sprite_type_id = "";
    std::string anim_id = "";

    if (file.fail())
        throw ExceptionFileNotFound(
            "sprites_config.yaml not found in /assets/sprites", "void ParserYaml::ParseSpritesConfig(graphics::SpritesManager &manager)");
    while (getline(file, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
        if (line[0] == '#' || line.empty())
            continue;
        auto delimiterPos = line.find(":");
        auto name = line.substr(0, delimiterPos);
        auto value = line.substr(delimiterPos + 1);
        if (line.compare("spritesheet") == 0) {
            manager.addTexturePath(value);
            spritesheet_b = true;
            spritesheet = value;
            continue;
        }
        if (manager.isSpriteTypes(line) && spritesheet_b) {
            manager.addSpriteData1(spritesheet, line, value);
            sprite_type_b = true;
            sprite_type = line;
            sprite_type_id = value;
            continue;
        }
        if (manager.isSpriteTypeAttributes(line) && spritesheet_b && sprite_type_b) {
            manager.addSpriteData2(sprite_type, sprite_type_id, value);
            anim_b = true;
            anim_id = value;
            continue;
        }
        if (manager.isSpriteAnimAttributes(line) && spritesheet_b && sprite_type_b && anim_b) {
            manager.addSpriteData3(sprite_type, sprite_type_id, anim_id, line, value);
            continue;
        }
    }
}

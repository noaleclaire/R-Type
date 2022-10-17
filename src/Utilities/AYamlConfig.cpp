/*
** EPITECH PROJECT, 2022
** AYamlConfig
** File description:
** AYamlConfig
*/

#include "AYamlConfig.hpp"

AYamlConfig::AYamlConfig()
{
}

AYamlConfig::~AYamlConfig()
{
}

bool AYamlConfig::isAConfigWord(std::string &sprite_config_word, int idx)
{
    for (std::size_t j = 0; j < _sprites_config_words.at(idx).size(); j++) {
        if (_sprites_config_words.at(idx).at(j).first.compare(sprite_config_word) == 0)
            return (true);
    }
    return (false);
}

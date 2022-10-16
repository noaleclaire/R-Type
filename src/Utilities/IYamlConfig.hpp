/*
** EPITECH PROJECT, 2022
** IYamlConfig
** File description:
** IYamlConfig
*/

#pragma once
#include <string>

class IYamlConfig {
  public:
    virtual ~IYamlConfig(){};

    virtual bool isAConfigWord(std::string &sprite_config_word, int idx) = 0;
    virtual void executeMapMemberFunctionPointer(std::string &sprite_config_word, std::string &value) = 0;
};

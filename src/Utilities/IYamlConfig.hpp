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
    /**
     * @brief Destroy the IYamlConfig object
     *
     */
    virtual ~IYamlConfig(){};
    /**
     * @brief
     *
     * @param sprite_config_word
     * @param idx
     * @return true
     * @return false
     */
    virtual bool isAConfigWord(std::string &sprite_config_word, int idx) = 0;
    /**
     * @brief
     *
     * @param sprite_config_word
     * @param value
     */
    virtual void executeMapMemberFunctionPointer(std::string &sprite_config_word, std::string &value) = 0;
};

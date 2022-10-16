/*
** EPITECH PROJECT, 2022
** AYamlConfig
** File description:
** AYamlConfig
*/

#pragma once
#include <any>
#include <vector>
#include "IYamlConfig.hpp"

class AYamlConfig : public IYamlConfig {
  public:
    AYamlConfig();
    AYamlConfig(const AYamlConfig &other) = default;
    ~AYamlConfig();
    AYamlConfig &operator=(const AYamlConfig &other) = default;

    bool isAConfigWord(std::string &sprite_config_word, int idx) override;
    void executeMapMemberFunctionPointer(std::string &sprite_config_word, std::string &value) = 0;

  protected:
    std::vector<std::vector<std::pair<std::string, std::any>>> _sprites_config_words;

  private:
};

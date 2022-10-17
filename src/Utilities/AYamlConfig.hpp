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
    /**
     * @brief Construct a new AYamlConfig object
     *
     */
    AYamlConfig();
    /**
     * @brief Construct a new AYamlConfig object
     *
     * @param other
     */
    AYamlConfig(const AYamlConfig &other) = default;
    /**
     * @brief Destroy the AYamlConfig object
     *
     */
    ~AYamlConfig();
    /**
     * @brief
     *
     * @param other
     * @return AYamlConfig&
     */
    AYamlConfig &operator=(const AYamlConfig &other) = default;
    /**
     * @brief
     *
     * @param sprite_config_word
     * @param idx
     * @return true
     * @return false
     */
    bool isAConfigWord(std::string &sprite_config_word, int idx) override;
    /**
     * @brief
     *
     * @param sprite_config_word
     * @param value
     */
    void executeMapMemberFunctionPointer(std::string &sprite_config_word, std::string &value) = 0;

  protected:
    std::vector<std::vector<std::pair<std::string, std::any>>> _sprites_config_words;

  private:
};

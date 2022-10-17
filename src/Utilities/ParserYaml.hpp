/*
** EPITECH PROJECT, 2022
** ParserYaml
** File description:
** ParserYaml
*/

#pragma once
#include <string>
#include "IYamlConfig.hpp"

class ParserYaml {
  public:
    /**
     * @brief
     *
     * @param manager
     * @param filename
     */
    static void parseYaml(IYamlConfig &manager, const std::string filename);

  private:
    /**
     * @brief Get the Nb Tab Start Of Line object
     *
     * @param line
     * @return int
     */
    static int getNbTabStartOfLine(std::string &line);
};

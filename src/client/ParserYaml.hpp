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
    static void parseYaml(IYamlConfig &manager, const std::string filename);

  private:
    static int getNbTabStartOfLine(std::string &line);
};

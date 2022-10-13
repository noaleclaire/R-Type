/*
** EPITECH PROJECT, 2022
** ParserYaml
** File description:
** ParserYaml
*/

#include "ParserYaml.hpp"
#include <fstream>
#include <vector>
#include "Exceptions/ExceptionBadYamlWord.hpp"
#include "Exceptions/ExceptionFileNotFound.hpp"

int ParserYaml::getNbTabStartOfLine(std::string &line)
{
    int nb_tab = 0;

    for (std::size_t i = 0; i < line.size(); i++) {
        if (line.at(i) != '\t' && line.at(i) != ' ')
            break;
        if (line.at(i) == '\t' || line.at(i) == ' ')
            nb_tab++;
    }
    return (nb_tab);
}

void ParserYaml::parseYaml(IYamlConfig &manager, const std::string filename)
{
    std::ifstream file(filename, std::ios::in);
    std::string line;
    int nb_tab = 0;
    int tmp_nb_tab = 0;

    if (file.fail())
        throw ExceptionFileNotFound(filename + " not found", "void ParserYaml::parseYaml(IYamlConfig &manager, const std::string filename)");
    while (getline(file, line)) {
        if (line[0] == '#' || line.empty())
            continue;
        nb_tab = getNbTabStartOfLine(line);
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
        auto delimiterPos = line.find(":");
        auto name = line.substr(0, delimiterPos);
        auto value = line.substr(delimiterPos + 1);
        if (!manager.isAConfigWord(name, nb_tab))
            throw ExceptionBadYamlWord("this key word format doesn't exists", "void ParserYaml::parseYaml(IYamlConfig &manager, const std::string filename)");
        else {
            if (nb_tab <= tmp_nb_tab + 1)
                manager.executeMapMemberFunctionPointer(name, value);
            else
                throw ExceptionBadYamlWord("missing key word", "void ParserYaml::parseYaml(IYamlConfig &manager, const std::string filename)");
        }
        tmp_nb_tab = nb_tab;
    }
}

/*
** EPITECH PROJECT, 2022
** ParserUserInfo.cpp
** File description:
** ParserUserInfo.cpp
*/

#include "ParserUserInfo.hpp"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <cstring>

void ParserUserInfo::getUserInfo(UserInfo &obj)
{
    // Object to read from file
    std::ifstream file_obj;
 
    std::strcpy(obj.pseudo, "");
    obj.music_volume = 10;
    obj.sfx_volume = 10;
    for (int i = 0; i < 9; i++)
        obj.achievements.push_back(static_cast<int>(false));
    for (int i = 0; i < 5; i++) {
        obj.coop_high_score.push_back(0);
        obj.versus_high_score.push_back(0);
    }
    // Opening file in append mode
    file_obj.open(std::filesystem::current_path() / "user.cache", std::ios::in | std::ios::binary);
 
    // Reading from file into object "obj"
    if (file_obj.is_open()) {
        file_obj >> obj.pseudo >> obj.music_volume >> obj.sfx_volume >> obj.achievements.at(0)
        >> obj.achievements.at(1) >> obj.achievements.at(2) >> obj.achievements.at(3) >> obj.achievements.at(4)
        >> obj.achievements.at(5) >> obj.achievements.at(6) >> obj.achievements.at(7) >> obj.achievements.at(8)
        >> obj.coop_high_score.at(0) >> obj.coop_high_score.at(1) >> obj.coop_high_score.at(2) >> obj.coop_high_score.at(3)
        >> obj.coop_high_score.at(4) >> obj.versus_high_score.at(0) >> obj.versus_high_score.at(1) >> obj.versus_high_score.at(2)
        >> obj.versus_high_score.at(3) >> obj.versus_high_score.at(4);
    }

    if (file_obj.is_open())
        file_obj.close();
}

void ParserUserInfo::saveUserInfo(UserInfo &obj)
{
    // Object to write in file
    std::ofstream file_obj;
 
    // Opening file in append mode
    file_obj.open(std::filesystem::current_path() / "user.cache", std::ios::out | std::ios::binary);
 
    // Writing the object's data in file
    if (file_obj.is_open()) {
        file_obj << obj.pseudo << ' ' << obj.music_volume << ' ' << obj.sfx_volume << ' ' << obj.achievements.at(0)
        << ' ' << obj.achievements.at(1) << ' ' << obj.achievements.at(2) << ' ' << obj.achievements.at(3) << ' ' << obj.achievements.at(4)
        << ' ' << obj.achievements.at(5) << ' ' << obj.achievements.at(6) << ' ' << obj.achievements.at(7) << ' ' << obj.achievements.at(8)
        << ' ' << obj.coop_high_score.at(0) << ' ' << obj.coop_high_score.at(1) << ' ' << obj.coop_high_score.at(2) << ' ' << obj.coop_high_score.at(3)
        << ' ' << obj.coop_high_score.at(4) << ' ' << obj.versus_high_score.at(0) << ' ' << obj.versus_high_score.at(1) << ' ' << obj.versus_high_score.at(2)
        << ' ' << obj.versus_high_score.at(3) << ' ' << obj.versus_high_score.at(4);
    }

    if (file_obj.is_open())
        file_obj.close();
}

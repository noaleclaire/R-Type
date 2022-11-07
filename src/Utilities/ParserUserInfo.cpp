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

void ParserUserInfo::getUserInfo(UserInfo *obj)
{
    // Object to read from file
    std::ifstream file_obj;
 
    std::strcpy(obj->pseudo, "");
    // Opening file in append mode
    file_obj.open(std::filesystem::current_path() / "user.cache", std::ios::in);
 
    // Reading from file into object "obj"
    if (file_obj.is_open())
        file_obj >> (char *)obj;

    if (file_obj.is_open())
        file_obj.close();
}

void ParserUserInfo::saveUserInfo(UserInfo *obj)
{
    // Object to write in file
    std::ofstream file_obj;
 
    // Opening file in append mode
    file_obj.open(std::filesystem::current_path() / "user.cache", std::ios::out | std::ios::trunc);
 
    // Writing the object's data in file
    if (file_obj.is_open())
        file_obj << (char *)obj;

    if (file_obj.is_open())
        file_obj.close();
}

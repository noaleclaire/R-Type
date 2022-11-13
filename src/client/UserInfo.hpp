/*
** EPITECH PROJECT, 2022
** UserInfo
** File description:
** UserInfo
*/

#pragma once

#include <vector>

#define PSEUDO_SIZE 16

struct UserInfo {
    char pseudo[PSEUDO_SIZE];
    int music_volume;
    int sfx_volume;
    std::vector<int> achievements;
};

/*
** EPITECH PROJECT, 2022
** UserInfo
** File description:
** UserInfo
*/

#pragma once

#include <vector>
#include <string>

#define PSEUDO_SIZE 10

struct UserInfo {
    char pseudo[PSEUDO_SIZE];
    int music_volume;
    int sfx_volume;
    std::vector<int> achievements;
    std::vector<std::size_t> coop_high_score;
    std::vector<std::size_t> versus_high_score;
};

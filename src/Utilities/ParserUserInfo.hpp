/*
** EPITECH PROJECT, 2022
** ParserUserInfo.hpp
** File description:
** ParserUserInfo.hpp
*/

#pragma once

#include "../client/UserInfo.hpp"

class ParserUserInfo {
    public:
        static void getUserInfo(UserInfo *obj);
        static void saveUserInfo(UserInfo *obj);

    private:
};

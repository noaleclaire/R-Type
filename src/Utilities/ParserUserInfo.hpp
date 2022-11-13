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
        /**
         * @brief Get the User Info object
         * 
         * @param obj 
         */
        static void getUserInfo(UserInfo &obj);
        /**
         * @brief 
         * 
         * @param obj 
         */
        static void saveUserInfo(UserInfo &obj);

    private:
};

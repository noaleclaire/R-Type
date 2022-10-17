/*
** EPITECH PROJECT, 2022
** UnpackVariadic
** File description:
** UnpackVariadic
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <any>
#include <iostream>

class UnpackVariadic {
    public:
        template <class T>
        static void unpackVariadicArgs(T &&first)
        {
            unpack.push_back(first);
        }
        template <class T, class... Params>
        static void unpackVariadicArgs(T &&first, Params &&...args)
        {
            unpack.push_back(first);
            unpackVariadicArgs(args...);
        }
        static float getArgNb(std::any &arg)
        {
            try {
                return (std::any_cast<float>(arg));
            } catch (const std::bad_any_cast &e) {}
            try {
                return (std::any_cast<double>(arg));
            } catch (const std::bad_any_cast &e) {}
            try {
                return (std::any_cast<int>(arg));
            } catch (const std::bad_any_cast &e) {}
            try {
                return (std::any_cast<std::size_t>(arg));
            } catch (const std::bad_any_cast &e) {}
            throw std::bad_any_cast();
        }
        static char *getArgChar(std::any &arg)
        {
            try {
                return (std::any_cast<char *>(arg));
            } catch (const std::bad_any_cast &e) {}
            throw std::bad_any_cast();
        }
        static std::vector<std::any> unpack;
    protected:
    private:
};

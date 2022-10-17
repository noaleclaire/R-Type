/*
** EPITECH PROJECT, 2022
** UnpackVariadic
** File description:
** UnpackVariadic
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <any>
#include <iostream>
#include <vector>

class UnpackVariadic {
  public:
    /**
     * @brief
     *
     * @tparam T
     * @param first
     */
    template <class T> static void unpackVariadicArgs(T &&first)
    {
        unpack.push_back(first);
    }
    /**
     * @brief
     *
     * @tparam T
     * @tparam Params
     * @param first
     * @param args
     */
    template <class T, class... Params> static void unpackVariadicArgs(T &&first, Params &&...args)
    {
        unpack.push_back(first);
        unpackVariadicArgs(args...);
    }
    /**
     * @brief Get the Arg Nb object
     *
     * @param arg
     * @return float
     */
    static float getArgNb(std::any &arg)
    {
        try {
            return (std::any_cast<float>(arg));
        } catch (const std::bad_any_cast &e) {
        }
        try {
            return (std::any_cast<double>(arg));
        } catch (const std::bad_any_cast &e) {
        }
        try {
            return (std::any_cast<int>(arg));
        } catch (const std::bad_any_cast &e) {
        }
        try {
            return (std::any_cast<std::size_t>(arg));
        } catch (const std::bad_any_cast &e) {
        }
        throw std::bad_any_cast();
    }
    /**
     * @brief Get the Arg Char object
     *
     * @param arg
     * @return char*
     */
    static char *getArgChar(std::any &arg)
    {
        try {
            return (std::any_cast<char *>(arg));
        } catch (const std::bad_any_cast &e) {
        }
        throw std::bad_any_cast();
    }
    static std::vector<std::any> unpack;

  protected:
  private:
};

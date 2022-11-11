/*
** EPITECH PROJECT, 2022
** ScenesInitializer
** File description:
** ScenesInitializer
*/

#pragma once
#include "../../Ecs/Registry.hpp"
#include "../../Ecs/Factory.hpp"

class ScenesInitializer {
    public:
        /**
         * @brief Construct a new Scenes Initializer object
         * 
         */
        ScenesInitializer();
        /**
         * @brief Construct a new Scenes Initializer object
         * 
         * @param other 
         */
        ScenesInitializer(const ScenesInitializer &other) = delete;
        /**
         * @brief Destroy the Scenes Initializer object
         * 
         */
        ~ScenesInitializer();
        /**
         * @brief 
         * 
         * @param other 
         * @return ScenesInitializer& 
         */
        ScenesInitializer &operator=(const ScenesInitializer &other) = delete;

    protected:
    private:
};

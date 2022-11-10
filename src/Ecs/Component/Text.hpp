/*
** EPITECH PROJECT, 2022
** Text
** File description:
** Text
*/

#pragma once
#include <memory>
#include "AComponent.hpp"

#define BUFFER_SIZE 255

namespace ecs
{
    class Text : public AComponent {
        public:
        /**
         * @brief Construct a new Text object
         * 
         * @param text 
         */
            Text(char *text);
            /**
             * @brief Construct a new Text object
             * 
             */
            Text() = default;
            /**
             * @brief Construct a new Text object
             * 
             * @param other 
             */
            Text(const Text &other) = default;
            /**
             * @brief Destroy the Text object
             * 
             */
            ~Text() = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Text& 
             */
            Text &operator=(const Text &other) = default;
            /**
             * @brief Get the Text object
             * 
             * @return char* 
             */
            char *getText();
            /**
             * @brief Set the Text object
             * 
             * @param text 
             */
            void setText(char *text);

        protected:
        private:
            char _text[BUFFER_SIZE];
    };
}

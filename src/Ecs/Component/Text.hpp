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

#define BUFFER_SIZE 255

namespace ecs
{
    class Text : public AComponent {
        public:
            Text(char *text);
            Text() = default;
            Text(const Text &other) = default;
            ~Text() = default;
            Text &operator=(const Text &other) = default;

            char *getText();
            void setText(char *text);

        protected:
        private:
            char _text[BUFFER_SIZE];
    };
}

/*
** EPITECH PROJECT, 2022
** Text
** File description:
** Text
*/

#pragma once
#include <memory>
#include <cstring>
#include "AComponent.hpp"

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

            friend bool operator==(const Text &lhs, const Text &rhs)
            {
                return std::strcmp(lhs._text, rhs._text) == 0;
            }
        protected:
        private:
            char _text[BUFFER_SIZE];
    };
}

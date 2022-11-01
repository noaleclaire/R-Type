/*
** EPITECH PROJECT, 2022
** Text
** File description:
** Text
*/

#pragma once
#include <memory>

namespace ecs
{
    class Text {
        public:
            Text(char *text);
            Text() = default;
            Text(const Text &other) = default;
            ~Text() = default;
            Text &operator=(const Text &other) = default;

            char *getText() const;
            void setText(char *text);

        protected:
        private:
            char *_text;
    };
}

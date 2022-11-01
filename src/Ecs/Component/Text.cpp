/*
** EPITECH PROJECT, 2022
** Text
** File description:
** Text
*/

#include <cstring>
#include "Text.hpp"

namespace ecs
{
    Text::Text(char *text)
    {
        _text = new char[std::strlen(text) + 1];
        std::strcpy(_text, text);
    }

    char *Text::getText() const
    {
        return (_text);
    }

    void Text::setText(char *text)
    {
        delete _text;
        _text = new char[std::strlen(text) + 1];
        std::strcpy(_text, text);
    }
}

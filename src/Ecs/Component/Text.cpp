/*
** EPITECH PROJECT, 2022
** Text
** File description:
** Text
*/

#include <cstring>
#include <iostream>
#include "Text.hpp"

namespace ecs
{
    Text::Text(char *text)
    {
        std::strcpy(_text, text);
    }

    char *Text::getText()
    {
        return (_text);
    }

    void Text::setText(char *text)
    {
        std::strcpy(_text, text);
    }
}

/*
** EPITECH PROJECT, 2022
** TextBox.cpp
** File description:
** TextBox.cpp
*/

#include "TextBox.hpp"

namespace ecs
{
    TextBox::TextBox() : _selected(false)
    {
    }

    bool TextBox::isSelected() const
    {
        return (_selected);
    }

    void TextBox::select()
    {
        _selected = true;
    }

    void TextBox::unselect()
    {
        _selected = false;
    }
}
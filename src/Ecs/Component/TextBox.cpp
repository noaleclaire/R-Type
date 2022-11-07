/*
** EPITECH PROJECT, 2022
** TextBox.cpp
** File description:
** TextBox.cpp
*/

#include "TextBox.hpp"

namespace ecs
{
    TextBox::TextBox(std::size_t max_size) : _selected(false), _max_size(max_size)
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

    std::size_t TextBox::getMaxSize() const
    {
        return (_max_size);
    }

    void TextBox::setMaxSize(std::size_t max_size)
    {
        _max_size = max_size;
    }
}
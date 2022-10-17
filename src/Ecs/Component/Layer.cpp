/*
** EPITECH PROJECT, 2022
** Layer.cpp
** File description:
** Layer.cpp
*/

#include "Layer.hpp"

namespace ecs
{
    Layer::Layer(std::size_t layer) : _layer(layer)
    {
    }

    /* Getter */
    int Layer::getLayer() const
    {
        return (_layer);
    }

    /* Setter */
    void Layer::setLayer(std::size_t layer)
    {
        _layer = layer;
    }
} // namespace ecs

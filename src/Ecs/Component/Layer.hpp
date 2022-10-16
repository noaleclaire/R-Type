/*
** EPITECH PROJECT, 2022
** Layer.hpp
** File description:
** Layer.hpp
*/

#pragma once

#include "AComponent.hpp"
#include <string>

namespace ecs
{
    class Layer : public AComponent {
      public:
        Layer(std::size_t layer);
        Layer(const Layer &other) = default;
        ~Layer() = default;
        Layer &operator=(const Layer &other) = default;

        /* Getter */
        int getLayer() const;

        /* Setter */
        void setLayer(std::size_t layer);

      private:
        std::size_t _layer;
    };
} // namespace ecs

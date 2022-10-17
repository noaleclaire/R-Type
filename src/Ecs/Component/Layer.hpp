/*
** EPITECH PROJECT, 2022
** Layer.hpp
** File description:
** Layer.hpp
*/

#pragma once

#include <string>
#include "AComponent.hpp"

namespace ecs
{
    class Layer : public AComponent {
      public:
        /**
         * @brief Construct a new Layer object
         *
         */
        Layer() = default;
        /**
         * @brief Construct a new Layer object
         *
         * @param layer
         */
        Layer(std::size_t layer);
        /**
         * @brief Construct a new Layer object
         *
         * @param other
         */
        Layer(const Layer &other) = default;
        /**
         * @brief Destroy the Layer object
         *
         */
        ~Layer() = default;
        /**
         * @brief
         *
         * @param other
         * @return Layer&
         */
        Layer &operator=(const Layer &other) = default;

        /* Getter */
        /**
         * @brief Get the Layer object
         *
         * @return int
         */
        int getLayer() const;

        /* Setter */
        /**
         * @brief Set the Layer object
         *
         * @param layer
         */
        void setLayer(std::size_t layer);

      private:
        std::size_t _layer;
    };
} // namespace ecs

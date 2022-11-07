/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#pragma once
#include "../../client/Sfml/Graphical.hpp"
#include "../Component/SparseArray.hpp"
#include "../Registry.hpp"

namespace ecs
{
    class Systems {
      public:
        /**
         * @brief
         *
         * @param registry
         * @param drawable
         */
        static void Drawable(Registry &registry, SparseArray<ecs::Drawable> const &drawable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param clickable
         * @param graphical
         */
        static void ClickableReleased(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param clickable
         * @param graphical
         */
        static void ClickablePressed(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param clickable
         * @param graphical
         */
        static void ClickableHeld(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param position
         * @param graphical
         */
        static void Position(Registry &registry, SparseArray<ecs::Position> const &position, graphics::Graphical &graphical);
        /**
         * @brief
         *
         * @param registry
         * @param controllable
         * @param graphical
         */
        static void Controllable(Registry &registry, SparseArray<ecs::Controllable> &controllable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param parallaxe
         * @param graphical
         */
        static void Parallaxe(Registry &registry, SparseArray<ecs::Type> const &type);
        /**
         * @brief
         *
         * @param registry
         * @param textBox
         * @param graphical
         */
        static void TextBox(Registry &registry, SparseArray<ecs::TextBox> &textBox, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param textBox
         * @param graphical
         */
        static void Hover(Registry &registry, SparseArray<ecs::Hover> &hover, graphics::Graphical *graphical);

      private:
        static void changeVolume(Registry &registry, std::size_t entity, graphics::Graphical *graphical);
        static void unselectAllTextBoxes(Registry &registry, SparseArray<ecs::TextBox> &textBox);
    };
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** Event
** File description:
** Event
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../Ecs/Registry.hpp"

namespace graphics
{
    class Graphical;
    class Event {
      public:
        Event();
        ~Event();

        sf::Event &getEvent();
        void handleEvents(Graphical *graphical, ecs::Registry &registry);

      protected:
      private:
        void _handleMouseButtonEvents(Graphical *graphical, ecs::Registry &registry);
        void _handleKeyEvents(Graphical *graphical, ecs::Registry &registry);

        sf::Event _event;
    };
} // namespace graphics

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
        /**
         * @brief Construct a new Event object
         * 
         */
        Event();
        /**
         * @brief Destroy the Event object
         * 
         */
        ~Event();

        /**
         * @brief Get the Event object
         * 
         * @return sf::Event& 
         */
        sf::Event &getEvent();
        /**
         * @brief 
         * 
         * @param graphical 
         * @param registry 
         */
        void handleEvents(Graphical *graphical, ecs::Registry &registry);

      protected:
      private:
      /**
       * @brief 
       * 
       * @param graphical 
       * @param registry 
       */
        void _handleMouseButtonEvents(Graphical *graphical, ecs::Registry &registry);
        /**
         * @brief 
         * 
         * @param graphical 
         * @param registry 
         */
        void _handleKeyEvents(Graphical *graphical, ecs::Registry &registry);

        sf::Event _event;
        bool _leftMouseHeld;
    };
} // namespace graphics

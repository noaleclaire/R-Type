/*
** EPITECH PROJECT, 2022
** Event
** File description:
** Event
*/

#include "Event.hpp"
#include "../../Ecs/Systems/Systems.hpp"

namespace graphics
{
    Event::Event() : _leftMouseHeld(false)
    {
    }

    Event::~Event()
    {
    }

    sf::Event &Event::getEvent()
    {
        return (_event);
    }

    void Event::handleEvents(Graphical *graphical, ecs::Registry &registry)
    {
        while (graphical->getWindow().pollEvent(_event)) {
            _handleMouseButtonEvents(graphical, registry);
            _handleKeyEvents(graphical, registry);
            if (_event.type == sf::Event::Closed)
                graphical->getWindow().close();
            if (_event.type == sf::Event::TextEntered) {
                ecs::Systems::TextBox(registry, registry.getComponents<ecs::TextBox>(), graphical);
            }
        }
    }

    void Event::_handleMouseButtonEvents(Graphical *graphical, ecs::Registry &registry)
    {
        if (_event.type == sf::Event::MouseButtonPressed) {
            if (_event.mouseButton.button == sf::Mouse::Button::Left)
                _leftMouseHeld = true;
        }
        if (_leftMouseHeld)
                ecs::Systems::ClickableHeld(registry, registry.getComponents<ecs::Clickable>(), graphical);
        if (_event.type == sf::Event::MouseButtonReleased) {
            if (_event.mouseButton.button == sf::Mouse::Button::Left) {
                _leftMouseHeld = false;
                ecs::Systems::ClickableReleased(registry, registry.getComponents<ecs::Clickable>(), graphical);
            }
        }
    }

    void Event::_handleKeyEvents(Graphical *graphical, ecs::Registry &registry)
    {
        ecs::Systems::Controllable(registry, registry.getComponents<ecs::Controllable>(), graphical);
    }
} // namespace graphics

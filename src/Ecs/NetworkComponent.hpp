/*
** EPITECH PROJECT, 2022
** NetworkComponent
** File description:
** NetworkComponent
*/

#pragma once
#include "../Network/Message.hpp"

namespace ecs
{
    template <class Component, class T> class NetworkComponent {
      public:
        /**
         * @brief Create a Message object
         *
         * @param entity
         * @param component
         * @param header_id
         * @return network::Message<T>
         */
        static network::Message<T> createMessage(std::size_t entity, Component component, T header_id)
        {
            network::Message<T> message;
            message.header.id = header_id;
            message << entity << component;
            return (message);
        }
        /**
         * @brief Create a Component object
         *
         * @param message
         * @return std::pair<std::size_t, Component>
         */
        static std::pair<std::size_t, Component> createComponent(network::Message<T> &message)
        {
            std::size_t entity;
            Component component;
            message >> component >> entity;
            return (std::make_pair(entity, component));
        }
    };
} // namespace ecs

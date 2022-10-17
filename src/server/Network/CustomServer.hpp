/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#pragma once

#include "../../Network/UdpServerClient.hpp"
#include "../../Ecs/Registry.hpp"
#include "../../Ecs/NetworkComponent.hpp"
#include "../../Ecs/Enum.hpp"

class CustomServer : public network::UdpServerClient<network::CustomMessage> {
    public:
        CustomServer(boost::asio::io_context &io_context, unsigned short local_port);
        CustomServer(const CustomServer &other) = delete;
        ~CustomServer();
        CustomServer &operator=(const CustomServer &other) = delete;
    protected:
        void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;
    private:
        void _initGame();
        template <class Component>
        void _sendNetworkComponent(std::size_t entity, ecs::ComponentTypes type)
        {
            try {
                network::Message<network::CustomMessage> msg;
                msg.header.id = network::CustomMessage::ComponentType;
                msg << type;
                _registry.getComponents<Component>().at(entity);
                sendToAllClients(msg);
                sendToAllClients(ecs::NetworkComponent<Component, network::CustomMessage>::createMessage(entity,
                    _registry.getComponents<Component>().at(entity).value(), network::CustomMessage::SendGameComponent));
            } catch (const ecs::ExceptionComponentNull &e) {
                return;
            } catch (const ecs::ExceptionIndexComponent &e) {
                return;
            }
        }
        void _sendNetworkComponents(std::size_t entity);

        ecs::Registry _registry;
};

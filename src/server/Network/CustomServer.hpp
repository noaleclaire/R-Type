/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#pragma once

#include <chrono>
#include "../../Ecs/Enum.hpp"
#include "../../Ecs/NetworkComponent.hpp"
#include "../../Ecs/Registry.hpp"
#include "../../Network/UdpServerClient.hpp"

using namespace std::chrono_literals;

class CustomServer : public network::UdpServerClient<network::CustomMessage> {
  public:
    /**
     * @brief Construct a new Custom Server object
     *
     * @param io_context
     * @param local_port
     */
    CustomServer(boost::asio::io_context &io_context, unsigned short local_port);
    /**
     * @brief Construct a new Custom Server object
     *
     * @param other
     */
    CustomServer(const CustomServer &other) = delete;
    /**
     * @brief Destroy the Custom Server object
     *
     */
    ~CustomServer();
    /**
     * @brief
     *
     * @param other
     * @return CustomServer&
     */
    CustomServer &operator=(const CustomServer &other) = delete;

  protected:
    /**
     * @brief
     *
     * @param target_endpoint
     * @param msg
     */
    void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;

  private:
    void _initGame();
    template <class Component> void _sendNetworkComponent(std::size_t entity, ecs::ComponentTypes type)
    {
        try {
            network::Message<network::CustomMessage> msg;
            msg.header.id = network::CustomMessage::ComponentType;
            msg << type;
            _registry.getComponents<Component>().at(entity);
            sendToAllClients(msg);
            std::this_thread::sleep_for(5ms);
            sendToAllClients(ecs::NetworkComponent<Component, network::CustomMessage>::createMessage(
                entity, _registry.getComponents<Component>().at(entity).value(), network::CustomMessage::SendGameComponent));
            std::this_thread::sleep_for(5ms);
        } catch (const ecs::ExceptionComponentNull &e) {
            return;
        } catch (const ecs::ExceptionIndexComponent &e) {
            return;
        }
    }
    void _sendNetworkComponents(std::size_t entity);

    ecs::Registry _registry;
};

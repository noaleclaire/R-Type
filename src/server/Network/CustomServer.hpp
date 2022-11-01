/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#pragma once

#include "../../Network/UdpServerClient.hpp"
#include "../../Ecs/Registry.hpp"

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
    template <class T>
    void sendNetworkComponents(std::size_t entity, T id_msg, bool all_clients)
    {
        for (std::size_t i = 0; i < _registry.getNetMessageCreate().size(); i++) {
            try {
                network::Message<network::CustomMessage> message = _registry.getNetMessageCreate().at(i)(entity, id_msg, i);
                if (all_clients)
                    sendToAllClients(message);
                else
                    send(message);
                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
            } catch (const ecs::ExceptionComponentNull &e) {
                continue;
            } catch (const ecs::ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

   void addSceneRoomToVectorRoom(ecs::Scenes scene);

  protected:
    /**
     * @brief
     *
     * @param target_endpoint
     * @param msg
     */
    void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;

  private:
    ecs::Registry _registry;
    std::vector<ecs::Scenes> _rooms;
};

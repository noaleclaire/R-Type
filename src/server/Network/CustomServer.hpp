/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#pragma once

#include "../../Network/UdpServerClient.hpp"
#include "../../Ecs/Registry.hpp"
#include "../../Ecs/Exceptions/ExceptionComponentNull.hpp"
#include "../../Ecs/Exceptions/ExceptionIndexComponent.hpp"
#include "../Utilities/LevelManager.hpp"

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
    void sendNetworkComponents(std::size_t entity, T id_msg, udp::endpoint client_endpoint, bool all_clients = false, bool except_one = false)
    {
        for (std::size_t i = 0; i < _registry.getNetMessageCreate().size(); i++) {
            try {
                network::Message<network::CustomMessage> message = _registry.getNetMessageCreate().at(i)(entity, id_msg, i);
                if (all_clients && !except_one)
                    sendToAllClients(message);
                else if (all_clients && except_one)
                    sendToAllClientsExceptOne(message, client_endpoint);
                else if (!all_clients)
                    send(message, client_endpoint);
                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
            } catch (const ecs::ExceptionComponentNull &e) {
                continue;
            } catch (const ecs::ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

   void updateSceneRoomInVectorRoom(ecs::Scenes room_scene, bool private_room, std::string player_name, udp::endpoint client_endpoint);

  protected:
    /**
     * @brief
     *
     * @param target_endpoint
     * @param msg
     */
    void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;

  private:
    void _createRoom(network::Message<network::CustomMessage> &msg, udp::endpoint target_endpoint, bool private_room = false);
    void _getInfoForListRoomScene(network::Message<network::CustomMessage> &msg);
    void _joinRoom(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg);
    void _joinRoomById(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg);
    void _quitRoom(udp::endpoint target_endpoint);
    ecs::Registry _registry;
    /**
     * @brief
     * @param ecs::Scenes is the room scene at this range
     * @param bool this first bool is the indicator for if the room scene is already created or not
     * @param bool this second bool is the indicator for if the room scene is private or not
     * @param std::vector is a vector of pair which contains every endpoint of the players in this room scene
     *                    and the bool is the indicator for if the player is the host of this room or not
     */
    std::vector<std::tuple<ecs::Scenes, bool, bool, std::vector<std::pair<udp::endpoint, bool>>, std::string>> _rooms;
    std::vector<LevelManager> _levels;
};

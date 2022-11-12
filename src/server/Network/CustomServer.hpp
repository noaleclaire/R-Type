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
#include <chrono>
#include <memory>

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
    void sendNetworkComponents(ecs::Registry &registry, std::size_t entity, T id_msg, udp::endpoint client_endpoint, bool all_clients = false, bool except_one = false)
    {
        for (std::size_t i = 0; i < registry.getNetMessageCreate().size(); i++) {
            try {
                network::Message<network::CustomMessage> message = registry.getNetMessageCreate().at(i)(entity, id_msg, i);
                if (all_clients && !except_one)
                    sendToAllClients(message);
                else if (all_clients && except_one)
                    sendToAllClientsExceptOne(message, client_endpoint);
                else if (!all_clients) {
                    send(message, client_endpoint);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
            } catch (const ecs::ExceptionComponentNull &e) {
                continue;
            } catch (const ecs::ExceptionIndexComponent &e) {
                continue;
            }
        }
    }

    template <class T>
    void sendNetworkComponent(ecs::Registry &registry, std::size_t entity, T id_msg, udp::endpoint client_endpoint, std::size_t index, bool all_clients = false, bool except_one = false)
    {
        try {
            network::Message<network::CustomMessage> message = registry.getNetMessageCreate().at(index)(entity, id_msg, index);
            if (all_clients && !except_one)
                sendToAllClients(message);
            else if (all_clients && except_one)
                sendToAllClientsExceptOne(message, client_endpoint);
            else if (!all_clients)
                send(message, client_endpoint);
            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));
        } catch (const ecs::ExceptionComponentNull &e) {}
        catch (const ecs::ExceptionIndexComponent &e) {}
    }

   void updateSceneRoomInVectorRoom(ecs::Scenes room_scene, bool private_room, std::string player_name, udp::endpoint client_endpoint);

    /**
     * @brief Get the start time of the current scene
     *
     * @param scene
     * @return std::chrono::time_point<std::chrono::system_clock>
     */
    std::chrono::time_point<std::chrono::system_clock> getStartTime(ecs::Scenes scene) const;
    /**
     * @brief Get the last update time of the current scene
     *
     * @param scene
     * @return std::chrono::time_point<std::chrono::system_clock>
     */
    std::chrono::time_point<std::chrono::system_clock> getLastTime(ecs::Scenes scene) const;
    /**
     * @brief Set the last update time of the current scene
     *
     * @param scene
     * @param new_time
     */
    void setLastTime(ecs::Scenes scene, std::chrono::time_point<std::chrono::system_clock> new_time);
    /**
     * @brief Start times of the current scene
     *
     * @param scene
     */
    void startTimes(ecs::Scenes scene);

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
    void _createShot(network::Message<network::CustomMessage> &msg, udp::endpoint target_endpoint);
    void _getInfoForListRoomScene(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg);
    void _joinRoom(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg);
    void _joinRoomById(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg);
    void _updateRoom(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg);
    void _quitRoom(udp::endpoint target_endpoint);

    void _compareRegistries(udp::endpoint target_endpoint, ecs::Registry &registry, ecs::Registry &tmp_registry);

    /**
     * @brief
     * @param ecs::Scenes is the room scene at this range
     * @param ecs::Scenes is the game scene at this range
     * @param bool this first bool is the indicator for if the room scene is already created or not
     * @param bool this second bool is the indicator for if the room scene is private or not
     * @param std::vector is a vector of pair which contains every endpoint of the players in this scene
     *                    and the bool is the indicator for if the player is the host or not
     * @param std::string is the name of the host of the scene
     * @param bool is the mode of the scene (coop by default)
     * @param ecs::Registry is the Registry of one scene
     */
    std::vector<std::tuple<ecs::Scenes, ecs::Scenes, bool, bool, std::vector<std::pair<udp::endpoint, bool>>, std::string, bool, std::unique_ptr<ecs::Registry>>> _registries;
    std::unordered_map<udp::endpoint, int> _rooms_filter_mode;
    std::unordered_map<udp::endpoint, std::string> _players_names;

    std::vector<LevelManager> _levels;
    std::unordered_map<ecs::Scenes, std::chrono::time_point<std::chrono::system_clock>> _start_times;
    std::unordered_map<ecs::Scenes, std::chrono::time_point<std::chrono::system_clock>> _last_times;
};

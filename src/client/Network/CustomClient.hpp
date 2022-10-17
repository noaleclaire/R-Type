/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#pragma once

#include "../../Ecs/Enum.hpp"
#include "../../Ecs/Registry.hpp"
#include "../../Network/UdpServerClient.hpp"
#include "../Sfml/Graphical.hpp"
#include "../Sfml/SpritesManager.hpp"

class CustomClient : public network::UdpServerClient<network::CustomMessage> {
  public:
    /**
     * @brief Construct a new Custom Client object
     *
     * @param io_context
     * @param host
     * @param server_port
     */
    CustomClient(boost::asio::io_context &io_context, std::string host, unsigned short server_port);
    /**
     * @brief Construct a new Custom Client object
     *
     * @param other
     */
    CustomClient(const CustomClient &other) = delete;
    /**
     * @brief Destroy the Custom Client object
     *
     */
    ~CustomClient();
    /**
     * @brief
     *
     * @param other
     * @return CustomClient&
     */
    CustomClient &operator=(const CustomClient &other) = delete;
    /**
     * @brief
     *
     */
    void pingServer();
    /**
     * @brief
     *
     */
    void initGame();
    /**
     * @brief
     *
     */
    void clientDisconnect();
    ecs::Registry *registry;
    graphics::Graphical *graphical;
    SpritesManager *sprites_manager;

  protected:
    /**
     * @brief
     *
     * @param target_endpoint
     * @param msg
     */
    void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;

  private:
<<<<<<< HEAD
    void _setRectAndSpriteComponent();
    void _receivedGameComponent(network::Message<network::CustomMessage> &msg);
=======
    /**
     * @brief
     *
     * @param msg
     */
    void receivedGameComponent(network::Message<network::CustomMessage> &msg);
>>>>>>> d23f5a4a77bbc322d852438f958205849cdf756c
    ecs::ComponentTypes _actualType;
};

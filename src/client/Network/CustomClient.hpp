/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#pragma once

#include "../../Network/UdpServerClient.hpp"
#include "../../Ecs/Registry.hpp"
#include "../Sfml/Graphical.hpp"
#include "../Sfml/SpritesManager.hpp"
#include "../../Ecs/Enum.hpp"

class CustomClient : public network::UdpServerClient<network::CustomMessage> {
    public:
        CustomClient(boost::asio::io_context &io_context, std::string host, unsigned short server_port);
        CustomClient(const CustomClient &other) = delete;
        ~CustomClient();
        CustomClient &operator=(const CustomClient &other) = delete;
        void pingServer();
        void initGame();
        ecs::Registry *registry;
        graphics::Graphical *graphical;
        SpritesManager *sprites_manager;
        bool *all_data_received;
    protected:
        void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;
    private:
        void receivedGameComponent(network::Message<network::CustomMessage> &msg);
        ecs::ComponentTypes _actualType;
};

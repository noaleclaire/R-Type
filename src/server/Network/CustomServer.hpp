/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#pragma once

#include "../../Network/UdpServerClient.hpp"

class CustomServer : public network::UdpServerClient<network::CustomMessage> {
    public:
        CustomServer(boost::asio::io_context& io_context, unsigned short local_port);
        CustomServer(const CustomServer &other) = delete;
        ~CustomServer();
        CustomServer &operator=(const CustomServer &other) = delete;
    protected:
        void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;
};

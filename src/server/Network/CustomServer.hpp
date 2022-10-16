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
    /**
     * @brief Construct a new Custom Server object
     * 
     * @param io_context 
     * @param local_port 
     */
        CustomServer(boost::asio::io_context& io_context, unsigned short local_port);
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
};

/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#pragma once

#include "../../Network/UdpServerClient.hpp"

class CustomClient : public network::UdpServerClient<network::CustomMessage> {
    public:
    /**
     * @brief Construct a new Custom Client object
     * 
     * @param io_context 
     * @param host 
     * @param server_port 
     */
        CustomClient(boost::asio::io_context& io_context, std::string host, unsigned short server_port);
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
        void PingServer();
    protected:
    /**
     * @brief 
     * 
     * @param target_endpoint 
     * @param msg 
     */
        void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;
};

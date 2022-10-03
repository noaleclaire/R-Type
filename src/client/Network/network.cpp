/*
** EPITECH PROJECT, 2022
** b
** File description:
** b
*/

#include "network.hpp"

using boost::asio::ip::address;
using boost::asio::ip::udp;

boost::array<char, 1024> recv_buffer;

network_player::network_player()
{
}

network_player::~network_player()
{
}

void handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
{
    std::cout << "Received: '" << std::string(recv_buffer.begin(), recv_buffer.begin() + bytes_transferred) << "'\n";
}

void network_player::process_player(shared_memory_t *shr)
{
    while (1) {
        boost::asio::io_service io_service;
        boost::asio::ip::udp::socket socket(io_service);
        boost::asio::ip::udp::endpoint remote_endpoint;

        socket.open(udp::v4());
        socket.bind(udp::endpoint(address::from_string(IPADDRESS), SRVR_UDP_PORT));
        socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
            boost::bind(handle_receive, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        std::cout << "Receiving\n";
        io_service.run();
        std::cout << "Receiver exit\n";
    }
}

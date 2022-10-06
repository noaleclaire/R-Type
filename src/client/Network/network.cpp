/*
** EPITECH PROJECT, 2022
** b
** File description:
** b
*/

#include "network.hpp"
#include <iostream>
#include <csignal>
#include <atomic>
#include <string>

using boost::asio::ip::udp;

network_player::network_player()
{
}

network_player::~network_player()
{
}

void network_player::process_player(shared_memory_t *shr)
{
    boost::asio::io_context io_context;
    udp::resolver resolver(io_context);
    udp::endpoint receiver_endpoint = boost::asio::ip::udp::endpoint(
	boost::asio::ip::address::from_string("127.0.0.1"), 13251);
    udp::socket socket(io_context);
    socket.open(udp::v4());
    for(;;) {
        boost::array<char, 1> send_buf  = {{ 0 }};
        socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
        boost::array<char, 128> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(
            boost::asio::buffer(recv_buf), sender_endpoint);
        std::cout.write(recv_buf.data(), len);
    }

}
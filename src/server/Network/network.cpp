/*
** EPITECH PROJECT, 2022
** b
** File description:
** b
*/

#include "network.hpp"
using boost::asio::ip::udp;
using boost::asio::ip::address;

boost::array<char, 1024> recv_buffer;


Network::Network()
{
}

Network::~Network()
{
}

void Network::process_network(std::string in)
{
    boost::asio::io_service io_service(2);
    boost::asio::ip::udp::socket socket(io_service);
    boost::asio::ip::udp::endpoint remote_endpoint = udp::endpoint(address::from_string(IPADDRESS), SRVR_UDP_PORT);
    socket.open(boost::asio::ip::udp::v4());
    boost::system::error_code err;
    socket.send_to(boost::asio::buffer(in), remote_endpoint, 0, err);
    socket.close();
    printf("Sending Payload --- \n");
}
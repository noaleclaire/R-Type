/*
** EPITECH PROJECT, 2022
** b
** File description:
** b
*/

#include "network.hpp"

using boost::asio::ip::udp;

Network::Network()
{
}

Network::~Network()
{
}

std::string Network::make_daytime_string()
{
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}

void Network::process_network()
{
    boost::asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 13251));

    for (;;) {
      boost::array<char, 1> recv_buf;
      udp::endpoint remote_endpoint;
      socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

      std::string message = make_daytime_string();

      boost::system::error_code ignored_error;
      socket.send_to(boost::asio::buffer(message),
          remote_endpoint, 0, ignored_error);
    }
}
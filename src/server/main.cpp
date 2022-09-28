/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/


#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try
  {
    boost::asio::io_context io_context;

    udp::socket socket(io_context, udp::endpoint(udp::v4(), 13));

    for (;;)
    {
      boost::array<char, 1> recv_buf;
      udp::endpoint remote_endpoint;
      socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

      std::string message = make_daytime_string();

      socket.send_to(boost::asio::buffer(message),
          remote_endpoint, 0);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}


// #include "Ecs/ecs.hpp"
// #include "Network/network.hpp"
// #include "Ecs/Exceptions/Exception.hpp"
// #include <iostream>

// int main(void)
// {
//     try
//     {
//         my_ecs();
//         my_network();
//     } catch(const ecs::Exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         std::cerr << e.where() << std::endl;
//     }
//     return (0);
// }
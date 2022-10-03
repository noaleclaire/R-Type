/*
** EPITECH PROJECT, 2022
** net
** File description:
** net
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#define IPADDRESS     "127.0.0.1"
#define SRVR_UDP_PORT 10251

using boost::asio::ip::address;
using boost::asio::ip::udp;

class Network {
  public:
    Network();
    ~Network();
    void process_network(std::string mes);

  private:
};

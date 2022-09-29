/*
** EPITECH PROJECT, 2022
** net
** File description:
** net
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#define IPADDRESS "127.0.0.1"
#define SRVR_UDP_PORT  10251

using boost::asio::ip::udp;
using boost::asio::ip::address;

class Network
{
public:
    Network();
    ~Network();
    void process_network(std::string mes);
private:
};
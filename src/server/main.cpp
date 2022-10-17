/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "../Network/UdpServerClient.hpp"
#include "Network/CustomServer.hpp"

int main(int ac, char **av)
{
    static_cast<void>(av);
    static_cast<void>(ac);
    try {
        boost::asio::io_context io_context;
        CustomServer server(io_context, 1358);

        std::vector<std::thread> thread_group;
        for (std::size_t i = 0; i < std::thread::hardware_concurrency(); i++)
            thread_group.push_back(std::thread(bind(&boost::asio::io_context::run, boost::ref(io_context))));
        for (std::size_t i = 0; i < std::thread::hardware_concurrency(); i++)
            thread_group.at(i).join();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}

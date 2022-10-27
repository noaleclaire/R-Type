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
        unsigned short port = 1358;
        if (ac == 2) {
            std::size_t pos{};
            port = static_cast<unsigned short>(std::stoi(std::string(av[1]), &pos));
        }
        CustomServer server(io_context, port);
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

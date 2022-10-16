/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "../Ecs/Component/Position.hpp"
#include "../Network/UdpServerClient.hpp"
#include "Network/CustomServer.hpp"

int main(int ac, char **av)
{
    try {
        boost::asio::io_context io_context;
        CustomServer server(io_context, 1313);

        std::vector<std::thread> thread_group;
        for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++)
            thread_group.push_back(std::thread(bind(&boost::asio::io_context::run, boost::ref(io_context))));
        for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++)
            thread_group.at(i).join();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

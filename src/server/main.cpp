/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "Network/network.hpp"

int main(int ac, char **av)
{
    try {
        Network server;
        server.process_network();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}

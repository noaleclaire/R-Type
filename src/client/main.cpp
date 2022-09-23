/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "Sfml/window.hpp"
#include "Network/network.hpp"
#include <thread>

void process_client(char **av)
{
    shared_memory_t *shr = \
    (shared_memory_t *)malloc(sizeof(shared_memory_t));
    shr->_st = false;
    network_player net(std::atoi(av[1]));
    net.init_player();
    shr->fd = net.get_fd();
    shr->wait = 1;
    shr->name = av[2];
    std::thread f(&network_player::process_player, &net, shr);
    //window win;
    //win.launch_window(shr);
    f.join();
}

int main(int ac, char **av)
{
    if (ac == 2)
        std::cout << "Usage:\n./player port name" << std::endl;
    else if (ac == 3) {
        process_client(av);
    } else
        return (84);
}
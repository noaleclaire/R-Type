/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "Network/network.hpp"
#include "Sfml/window.hpp"

int main(int ac , char **av)
{
    if (ac == 2) {
        shared_memory_t *shr = \
        (shared_memory_t *)malloc(sizeof(shared_memory_t));
        network_player net;
        shr->name = av[1];
        std::thread f(&network_player::process_player, &net, shr);
        window win;
        win.launch_window(shr);
        f.join();
    } else
        return (84);
}

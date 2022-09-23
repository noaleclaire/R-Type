/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "Ecs/ecs.hpp"
#include "Network/network.hpp"

int main(int ac, char **av)
{
    if (ac == 2) {
        Network net(std::atoi(av[1]));
        net.init_network();
        net.process_network();
    } else
        return (84);
    return (0);
}
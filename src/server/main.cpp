/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "Network/network.hpp"

int main(int ac , char **av)
{
    if (ac == 2) {
        Network net;
        net.process_network(av[1]);
    } else
        return (84);
}
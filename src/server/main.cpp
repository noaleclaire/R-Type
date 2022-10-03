/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "Network/network.hpp"

int main(int ac, char **av)
{
    if (ac == 2) {
        Network net;
        net.process_network(av[1]);
    } else
        return (84);
}

// #include "Ecs/ecs.hpp"
// #include "Network/network.hpp"
// #include "Ecs/Exceptions/Exception.hpp"
// #include <iostream>

// int main(void)
// {
//     try
//     {
//         my_ecs();
//         my_network();
//     } catch(const ecs::Exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         std::cerr << e.where() << std::endl;
//     }
//     return (0);
// }

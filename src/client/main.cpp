/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "Network/network.hpp"
#include "Sfml/window.hpp"

int main(int ac, char **av)
{
    (void)av;
    if (ac == 2) {
        std::shared_ptr<void()> s;
        network_player net;
        std::thread f(&network_player::process_player, &net, s);
        window win;
        win.launch_window(s);
        f.join();
    } else
        return (84);
}

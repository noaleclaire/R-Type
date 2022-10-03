/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <filesystem>
#include <iostream>
#include "Exceptions/Exception.hpp"
#include "Exceptions/ExceptionDirectoryNotFound.hpp"
#include "Network/network.hpp"
#include "ParserYaml.hpp"
#include "Sfml/window.hpp"
#include "SpritesManager.hpp"

bool assetsFolderExists()
{
    if (!std::filesystem::is_directory(std::filesystem::current_path() / "assets"))
        throw ExceptionDirectoryNotFound("directory /assets not found", "bool assetsFolderExists()");
    if (!std::filesystem::is_directory(std::filesystem::current_path() / "assets/sprites"))
        throw ExceptionDirectoryNotFound("directory /sprites not found in /assets", "bool assetsFolderExists()");
    if (!std::filesystem::is_directory(std::filesystem::current_path() / "assets/sounds"))
        throw ExceptionDirectoryNotFound("directory /sounds not found in /assets", "bool assetsFolderExists()");
    if (!std::filesystem::is_directory(std::filesystem::current_path() / "assets/font"))
        throw ExceptionDirectoryNotFound("directory /font not found in /assets", "bool assetsFolderExists()");
}

int main(int ac, char **av)
{
    if (ac == 2) {
        try {
            assetsFolderExists();
            graphics::SpritesManager sprites_manager;
            ParserYaml::ParseSpritesConfig(sprites_manager);
        } catch (const Exception &e) {
            std::cerr << e.what() << std::endl;
            std::cerr << e.where() << std::endl;
            return (84);
        }
        shared_memory_t *shr = (shared_memory_t *)malloc(sizeof(shared_memory_t));
        network_player net;
        shr->name = av[1];
        std::thread f(&network_player::process_player, &net, shr);
        window win;
        win.launch_window(shr);
        f.join();
    } else
        return (84);
    return (0);
}

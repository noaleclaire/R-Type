/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "Exceptions/Exception.hpp"
#include "Exceptions/ExceptionDirectoryNotFound.hpp"
#include "Core.hpp"
#include "Network/CustomClient.hpp"

void assetsFolderExists()
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
    (void)av;
    (void)ac;
    std::ofstream errorLogsFile("ErrorLogs.txt");
    try {
        // assetsFolderExists();
        Core core;

        boost::asio::io_context io_context;
        CustomClient client(io_context, "127.0.0.1", 1313);
        std::thread thread_client(bind(&boost::asio::io_context::run, boost::ref(io_context)));

        for (int i = 0; i < 5; i++) {
            client.PingServer();
            std::cout << "test" << std::endl;
        }
        //le faire quand on quitte le jeu
        if (thread_client.joinable()) {
            io_context.stop();
            thread_client.join();
        }
        // }
    } catch (const Exception &e) {
        errorLogsFile << e.what() << std::endl;
        errorLogsFile << e.where() << std::endl;
        errorLogsFile.close();
        return (84);
    } catch (std::exception &e) {
        errorLogsFile << e.what() << std::endl;
        errorLogsFile << e.where() << std::endl;
        errorLogsFile.close();
        return (84);
    }
    return (0);
}

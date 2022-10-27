/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include "Core.hpp"
#include "Exceptions/Exception.hpp"
#include "Exceptions/ExceptionDirectoryNotFound.hpp"

void assetsFolderExists()
{
    if (!std::filesystem::is_directory(std::filesystem::current_path() / "assets"))
        throw ExceptionDirectoryNotFound("directory /assets not found", "bool assetsFolderExists()");
    if (!std::filesystem::is_directory(std::filesystem::current_path() / "assets/sprites"))
        throw ExceptionDirectoryNotFound("directory /sprites not found in /assets", "bool assetsFolderExists()");
    // if (!std::filesystem::is_directory(std::filesystem::current_path() / "assets/sounds"))
    //     throw ExceptionDirectoryNotFound("directory /sounds not found in /assets", "bool assetsFolderExists()");
    // if (!std::filesystem::is_directory(std::filesystem::current_path() / "assets/font"))
    //     throw ExceptionDirectoryNotFound("directory /font not found in /assets", "bool assetsFolderExists()");
}

int main(int ac, char **av)
{
    static_cast<void>(av);
    static_cast<void>(ac);
    std::ofstream errorLogsFile("ErrorLogs.txt");
    try {
        assetsFolderExists();
        boost::asio::io_context io_context;
        std::string host = "127.0.0.1";
        unsigned short port = 1358;
        if (ac == 2)
            host = std::string(av[1]);
        if (ac == 3) {
            std::size_t pos{};
            host = std::string(av[1]);
            port = static_cast<unsigned short>(std::stoi(std::string(av[2]), &pos));
        }
        Core core(io_context, host, port);
    } catch (const Exception &e) {
        errorLogsFile << e.what() << std::endl;
        errorLogsFile << e.where() << std::endl;
        errorLogsFile.close();
        return (84);
    } catch (std::exception &e) {
        errorLogsFile << e.what() << std::endl;
        errorLogsFile.close();
        return (84);
    }
    return (0);
}

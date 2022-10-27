/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <csignal>
#include "Exceptions/ExceptionFileNotFound.hpp"
#include "../Network/UdpServerClient.hpp"
#include "Network/CustomServer.hpp"

void signalHandler(int signum)
{
    static_cast<void>(signum);
    std::system("./setup_server.sh 0 > tmp.cache");
    std::cout << std::endl;
    std::cout << std::ifstream("tmp.cache").rdbuf();
    std::system("rm tmp.cache");
    exit(0);
}

void executeSystemSetupCmd()
{
    if (!std::filesystem::is_regular_file(std::filesystem::current_path() / "setup_server.sh"))
        throw ExceptionFileNotFound("setup_server.sh not found in : " + std::string(std::filesystem::current_path()), "void executeSystemSetupCmd()");
    std::system("chmod +x setup_server.sh");
    std::system("./setup_server.sh 1 > tmp.cache");
    std::cout << std::ifstream("tmp.cache").rdbuf();
    std::system("rm tmp.cache");
}

int main(int ac, char **av)
{
    static_cast<void>(av);
    static_cast<void>(ac);
    try {
        boost::asio::io_context io_context;
        unsigned short port = 1358;
        signal(SIGINT, signalHandler);
        executeSystemSetupCmd();
        if (ac == 2) {
            std::size_t pos{};
            port = static_cast<unsigned short>(std::stoi(std::string(av[1]), &pos));
        }
        CustomServer server(io_context, port);
        std::cout << "Server port : " << port << std::endl;
        std::vector<std::thread> thread_group;
        for (std::size_t i = 0; i < std::thread::hardware_concurrency(); i++)
            thread_group.push_back(std::thread(bind(&boost::asio::io_context::run, boost::ref(io_context))));
        for (std::size_t i = 0; i < std::thread::hardware_concurrency(); i++)
            thread_group.at(i).join();
    } catch (const ExceptionFileNotFound &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << e.where() << std::endl;
        return (84);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}

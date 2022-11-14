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
    #if OS_Windows
        std::system("Start-Process .\setup_server.bat 0 -Verb runAs");
        std::system("rm tmp.cache");
        exit(0);
    #else
        std::system("./setup_server.sh 0");
        std::system("rm tmp.cache");
        exit(0);
    #endif
}

void executeSystemSetupCmd()
{
    #if OS_Windows
        if (!std::filesystem::is_regular_file(std::filesystem::current_path().append("setup_server.bat")))
            throw ExceptionFileNotFound("setup_server.bat not found in : " + std::filesystem::current_path().string(), "void executeSystemSetupCmd()");
        std::string validation;
        std::cout << "You are about to stop your Firewall, continue? (yes/no):" << std::endl;
        std::cin >> validation;
        while (validation.compare("yes") != 0 && validation.compare("no") != 0) {
            std::cout << "You are about to stop your Firewall, continue? (yes/no):" << std::endl;
            std::cout << validation << std::endl;
            std::cin >> validation;
        }
        if (validation.compare("no") == 0)
            exit(0);
        std::system("Start-Process .\setup_server.bat 1 -Verb runAs");
        std::cout << std::ifstream("tmp.cache").rdbuf();
        std::cout.flush();
        std::system("rm .\tmp.cache");
    #else
        if (!std::filesystem::is_regular_file(std::filesystem::current_path().append("setup_server.sh")))
            throw ExceptionFileNotFound("setup_server.sh not found in : " + std::filesystem::current_path().string(), "void executeSystemSetupCmd()");
        std::string validation;
        std::cout << "You are about to stop your Firewall, continue? (yes/no):" << std::endl;
        std::cin >> validation;
        while (validation.compare("yes") != 0 && validation.compare("no") != 0) {
            std::cout << "You are about to stop your Firewall, continue? (yes/no):" << std::endl;
            std::cout << validation << std::endl;
            std::cin >> validation;
        }
        if (validation.compare("no") == 0)
            exit(0);
        std::system("chmod +x setup_server.sh");
        std::system("./setup_server.sh 1");
        std::cout << std::ifstream("tmp.cache").rdbuf();
        std::cout.flush();
        std::system("rm tmp.cache");
    #endif
}

int main(int ac, char **av)
{
    static_cast<void>(av);
    static_cast<void>(ac);
    try {
        boost::asio::io_context io_context;
        unsigned short port = 1358;
        std::signal(SIGINT, signalHandler);
        std::signal(SIGSEGV, signalHandler);
        std::signal(SIGABRT, signalHandler);
        std::signal(SIGTERM, signalHandler);
        if (ac == 2) {
            std::size_t pos{};
            port = static_cast<unsigned short>(std::stoi(std::string(av[1]), &pos));
        }
        executeSystemSetupCmd();
        std::cout << "Server port : " << port << std::endl;
        CustomServer server(io_context, port);
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

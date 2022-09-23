/*
** EPITECH PROJECT, 2022
** net
** File description:
** net
*/

#pragma once

#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include "shared.hpp"

class network_player
{
public:
    network_player(int port);
    ~network_player();
    void init_player(void);
    void process_player(shared_memory_t *shr);
    void handle_message(int fd, shared_memory_t *shr);
    void get_info_pokemon(char *input, shared_memory_t *s);
    void get_damage_pokemon(char *input, shared_memory_t *s);
    void get_name_pokemon(char *input, shared_memory_t *s);
    void get_info_stat_pokemon(std::string tmp, char *input, \
    shared_memory_t *s);
    char *get_input(int fd);
    bool get_start(void) const;
    int get_fd(void) const;
private:
    int _port;
    int _sock;
    int _id;
    fd_set read_fd_copy;
    fd_set read_fd_registered;
    struct sockaddr_in addr;
    bool _start;
    shared_memory_t *_s;
};

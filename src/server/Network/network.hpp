/*
** EPITECH PROJECT, 2022
** net
** File description:
** net
*/

#pragma once

#include <cstdio>

#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

typedef struct client_s {
    int id;
    int fd;
} client_t;

class Network
{
public:
    Network(int port);
    ~Network();
    void init_network(void);
    void process_network(void);
    void connexion_network(int i);
    void handle_new_client(int sck);
    char *get_input(int fd);
    int handle_input(client_t *client, char *buffer, int j);
    void send_start(void);
    void send_id(client_t *client);
private:
    char *_buffer;
    char *_tmp;
    int _size;
    int _port;
    int _sock;
    fd_set _read_fd_copy;
    fd_set _read_fd_registered;
    struct sockaddr_in _addr;
    int fd_max;
    int _new_clt;
    int _ret;
    int _nb_clients;
    client_t _cl[2];
};
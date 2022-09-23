/*
** EPITECH PROJECT, 2022
** b
** File description:
** b
*/

#include "network.hpp"

network_player::network_player(int port)
{
    this->_port = port;
}

network_player::~network_player()
{
}

void network_player::init_player(void)
{
    this->_sock = socket(PF_INET, SOCK_STREAM, 0);
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(this->_port);
    this->addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(this->_sock, (struct sockaddr*)&this->addr, \
    sizeof(this->addr)) < 0) {
        exit(84);
    }
}

char *network_player::get_input(int fd)
{
    char *buffer = new char [256];
    char *c = new char [1];
    int size = 0;

    if (fd < 0 || buffer == NULL)
        return NULL;
    while (c[0] != '\n') {
        c[0] = '\0';
        read(fd, c, 1);
        if (c[0] != '\n') {
            buffer[size] = c[0];
            size++;
        }
    }
    buffer[size] = '\0';
    return buffer;
}

void network_player::handle_message(int fd, shared_memory_t *s)
{
    char *input = get_input(fd);

    if (input[0] == 'I') {
        _id = input[3] - '0';
        dprintf(this->_sock, "READY\n");
    }
    if (input[0] == 'S') {
        _start = true;
        s->_st = true;
        s->wait = 0;
    }
}

void network_player::process_player(shared_memory_t *shr)
{
    dprintf(this->_sock, "ID\n");
    FD_ZERO(&this->read_fd_registered);
    FD_SET(this->_sock, &this->read_fd_registered);
    while (1) {
        read_fd_copy = read_fd_registered;
        if (select(FD_SETSIZE, &read_fd_copy, NULL, NULL, NULL) < 0)
            exit(84);
        else if (FD_ISSET(this->_sock, &this->read_fd_copy)) {
            handle_message(this->_sock, shr);
        }
    }
}

bool network_player::get_start(void) const
{
    return (_start);
}

int network_player::get_fd(void) const
{
    return (this->_sock);
}
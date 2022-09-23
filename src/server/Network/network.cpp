/*
** EPITECH PROJECT, 2022
** b
** File description:
** b
*/

#include "network.hpp"

#include "network.hpp"
#include <unistd.h>

Network::Network(int port)
{
    this->_port = port;
    this->_nb_clients = 0;
}

Network::~Network()
{
}

void Network::init_network(void)
{
    this->_sock = socket(PF_INET, SOCK_STREAM, 0);
    this->_addr.sin_family = AF_INET;
    this->_addr.sin_port = htons(this->_port);
    this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(this->_sock, (struct sockaddr *)&this->_addr, \
    sizeof(this->_addr)) != 0)
        exit(84);
    if (listen(this->_sock, 2) != 0)
        exit(84);
    FD_ZERO(&this->_read_fd_registered);
    FD_SET(this->_sock, &this->_read_fd_registered);
    this->fd_max = _sock;
}

void Network::handle_new_client(int sck)
{
    int acpt = -1;
    static int i = 0;
    socklen_t socklen;
    struct sockaddr_in c_in;

    acpt = accept(sck, (struct sockaddr *)&c_in, &socklen);
    if (acpt < 0)
        exit(84);
    FD_SET(acpt, &this->_read_fd_registered);
    this->_cl[i % 2].fd = acpt;
    i++;
}

char *Network::get_input(int fd)
{
    _buffer = new char [256];
    _tmp = new char [1];
    _size = 0;

    if (fd < 0 || _buffer == NULL)
        return NULL;
    while (_tmp[0] != '\n') {
        _tmp[0] = '\0';
        read(fd, _tmp, 1);
        if (_tmp[0] != '\n') {
            _buffer[_size] = _tmp[0];
            _size++;
        }
    }
    _buffer[_size] = '\0';
    return _buffer;
}

void Network::send_id(client_t *client)
{
    static int i = 0;
    
    i++;
    dprintf(client->fd, "ID %i\n", i);
}

void Network::send_start(void)
{
    static int i = 0;
    
    i++;
    if (i == 2) {
        dprintf(_cl[0].fd, "START\n");
        dprintf(_cl[1].fd, "START\n");
    }
}

int Network::handle_input(client_t *client, char *buffer, int j)
{
    if (buffer[0] == 'I' && buffer[1] == 'D') {
        if (client[0].fd == j) {
            send_id(&client[0]);
        } if (client[1].fd == j) {
            send_id(&client[1]);
        }
    }
    if (buffer[0] == 'R' && buffer[1] == 'E')
        send_start();
    return (0);
}

void Network::connexion_network(int i)
{
    if (i == this->_sock) {
        if (_nb_clients < 2) {
            handle_new_client(i);
            _nb_clients++;     
        }
    } else {
        if (handle_input(this->_cl, get_input(i), i) < 0) {
            FD_CLR(i, &this->_read_fd_copy);
        }
    }
}

void Network::process_network(void)
{
    while (1) {
        this->_read_fd_copy = this->_read_fd_registered;
        if (select(FD_SETSIZE, \
        &this->_read_fd_copy, NULL, NULL, NULL) < 0)
            exit(84);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &this->_read_fd_copy)) {
                connexion_network(i);
            }
        }
    }
}
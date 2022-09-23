/*
** EPITECH PROJECT, 2022
** s
** File description:
** s
*/

#pragma once

typedef struct shared_memory_s {
    int port;
    int fd;
    bool _st;
    int wait;
    std::string name;
} shared_memory_t;
/*
** EPITECH PROJECT, 2022
** Enum
** File description:
** Enum
*/

#include "Enum.hpp"

namespace ecs {
    std::chrono::time_point<std::chrono::system_clock> Enum::ping_latency = std::chrono::system_clock::now();
    int Enum::ping_latency_ms = 10;
}

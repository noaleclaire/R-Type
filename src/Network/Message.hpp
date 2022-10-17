/*
** EPITECH PROJECT, 2022
** Message
** File description:
** Message
*/

#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <cstring>
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace network
{
    enum CustomMessage : uint32_t {
        PingServer,
        SwitchToGame,
        SendGameComponent,
        ComponentType,
        AllGameComponentSent
    };
    template <class T>
    struct Header {
        T id;
        uint32_t size = 0;

        template <class U>
        friend std::vector<uint8_t> &operator << (std::vector<uint8_t> &header, const U &data)
        {
            static_assert(std::is_standard_layout<U>::value, "Data is too complex to be pushed into vector");
            std::size_t i = header.size();
            header.resize(header.size() + sizeof(U));
            std::memcpy(header.data() + i, &data, sizeof(U));
            return (header);
        }

        template <class U>
        friend std::vector<uint8_t> &operator >> (std::vector<uint8_t> &header, U &data)
        {
            static_assert(std::is_standard_layout<U>::value, "Data is too complex to be pulled from vector");
            std::size_t i = header.size() - sizeof(U);
            std::memcpy(&data, header.data() + i, sizeof(U));
            header.resize(i);
            return (header);
        }
    };
    template <class T>
    struct Message {
        Header<T> header{};
        std::vector<uint8_t> body;

        std::size_t size() const
        {
            return (body.size());
        }

        friend std::ostream &operator << (std::ostream &os, const Message<T> &msg)
        {
            os << "message type: " << static_cast<int>(msg.header.id) << " size: " << msg.header.size << std::endl;
            return (os);
        }

        template <class U>
        friend Message<T> &operator << (Message<T> &msg, const U &data)
        {
            static_assert(std::is_standard_layout<U>::value, "Data is too complex to be pushed into vector");
            std::size_t i = msg.body.size();
            msg.body.resize(msg.body.size() + sizeof(U));
            std::memcpy(msg.body.data() + i, &data, sizeof(U));
            msg.header.size = msg.size();
            return (msg);
        }

        template <class U>
        friend Message<T> &operator >> (Message<T> &msg, U &data)
        {
            static_assert(std::is_standard_layout<U>::value, "Data is too complex to be pulled from vector");
            std::size_t i = msg.body.size() - sizeof(U);
            std::memcpy(&data, msg.body.data() + i, sizeof(U));
            msg.body.resize(i);
            msg.header.size = msg.size();
            return (msg);
        }
    };
}

/*
** EPITECH PROJECT, 2022
** Message
** File description:
** Message
*/

#pragma once
#include <boost/asio.hpp>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

using boost::asio::ip::udp;

namespace network
{
    enum CustomMessage : uint32_t { PingServer, SwitchToGame, SendGameComponent, ComponentType, AllGameComponentSent, RemoveClient };
    template <class T> struct Header {
        T id;
        uint32_t size = 0;
        /**
         * @brief
         *
         * @tparam U
         * @param header
         * @param data
         * @return std::vector<uint8_t>&
         */
        template <class U> friend std::vector<uint8_t> &operator<<(std::vector<uint8_t> &header, const U &data)
        {
            static_assert(std::is_standard_layout<U>::value, "Data is too complex to be pushed into vector");
            std::size_t i = header.size();
            header.resize(header.size() + sizeof(U));
            std::memcpy(header.data() + i, &data, sizeof(U));
            return (header);
        }
        /**
         * @brief
         *
         * @tparam U
         * @param header
         * @param data
         * @return std::vector<uint8_t>&
         */
        template <class U> friend std::vector<uint8_t> &operator>>(std::vector<uint8_t> &header, U &data)
        {
            static_assert(std::is_standard_layout<U>::value, "Data is too complex to be pulled from vector");
            std::size_t i = header.size() - sizeof(U);
            std::memcpy(&data, header.data() + i, sizeof(U));
            header.resize(i);
            return (header);
        }
    };
    template <class T> struct Message {
        Header<T> header{};
        std::vector<uint8_t> body;
        /**
         * @brief
         *
         * @return std::size_t
         */
        std::size_t size() const
        {
            return (body.size());
        }
        /**
         * @brief
         *
         * @param os
         * @param msg
         * @return std::ostream&
         */
        friend std::ostream &operator<<(std::ostream &os, const Message<T> &msg)
        {
            os << "message type: " << static_cast<int>(msg.header.id) << " size: " << msg.header.size << std::endl;
            return (os);
        }
        /**
         * @brief
         *
         * @tparam U
         * @param msg
         * @param data
         * @return Message<T>&
         */
        template <class U> friend Message<T> &operator<<(Message<T> &msg, const U &data)
        {
            static_assert(std::is_standard_layout<U>::value, "Data is too complex to be pushed into vector");
            std::size_t i = msg.body.size();
            msg.body.resize(msg.body.size() + sizeof(U));
            std::memcpy(msg.body.data() + i, &data, sizeof(U));
            msg.header.size = msg.size();
            return (msg);
        }
        /**
         * @brief
         *
         * @tparam U
         * @param msg
         * @param data
         * @return Message<T>&
         */
        template <class U> friend Message<T> &operator>>(Message<T> &msg, U &data)
        {
            static_assert(std::is_standard_layout<U>::value, "Data is too complex to be pulled from vector");
            std::size_t i = msg.body.size() - sizeof(U);
            std::memcpy(&data, msg.body.data() + i, sizeof(U));
            msg.body.resize(i);
            msg.header.size = msg.size();
            return (msg);
        }
    };
} // namespace network

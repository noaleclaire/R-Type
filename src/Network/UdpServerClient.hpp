/*
** EPITECH PROJECT, 2022
** UdpServerClient
** File description:
** UdpServerClient
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include "Message.hpp"
#include "Queue.hpp"

using boost::asio::ip::udp;

namespace network
{
    template <class T> class UdpServerClient;

    template <class T> struct UdpSession : std::enable_shared_from_this<UdpSession<T>> {
        /**
         * @brief Construct a new Udp Session object
         *
         * @param instance
         */
        UdpSession(UdpServerClient<T> *instance) : _instance(instance)
        {
        }
        /**
         * @brief
         *
         * @param error
         */
        void handleRequestReadHeader(const boost::system::error_code &error)
        {
            if (!error) {
                if (_recv_msg.header.size > 0) {
                    if (_instance->_owner_type == UdpServerClient<T>::Owner::SERVER)
                        _instance->getOrAddClientEndpoint(_remote_endpoint);
                    _recv_msg.body.resize(_recv_msg.header.size);
                    _instance->readBody(this->shared_from_this());
                } else {
                    if (_instance->_owner_type == UdpServerClient<T>::Owner::SERVER)
                        _instance->getOrAddClientEndpoint(_remote_endpoint);
                    _instance->onMessage(_remote_endpoint, _recv_msg);
                    _instance->readHeader();
                }
            } else {
                if (_instance->_owner_type == UdpServerClient<T>::Owner::CLIENT)
                    _instance->_socket.close();
            }
        };
        /**
         * @brief
         *
         * @param error
         */
        void handleRequestReadBody(const boost::system::error_code &error)
        {
            if (!error) {
                _instance->onMessage(_remote_endpoint, _recv_msg);
            } else {
                if (_instance->_owner_type == UdpServerClient<T>::Owner::CLIENT)
                    _instance->_socket.close();
            }
        }
        /**
         * @brief
         *
         * @param error
         */
        void handleSentWriteHeader(const boost::system::error_code &error, std::size_t)
        {
            if (!error) {
                if (_send_msg.body.size() > 0)
                    _instance->writeBody(this->shared_from_this());
                // else {
                //     if (!_send_msg.empty() && _send_msg.front().second == _remote_endpoint)
                //         _instance->writeHeader(this->shared_from_this());
                // }
            } else {
                if (_instance->_owner_type == UdpServerClient<T>::Owner::CLIENT)
                    _instance->_socket.close();
            }
        }
        /**
         * @brief
         *
         * @param error
         */
        void handleSentWriteBody(const boost::system::error_code &error, std::size_t)
        {
            if (!error) {
                return;
                // if (!_send_msg.empty() && _send_msg.front().second == _remote_endpoint)
                //     _instance->writeHeader(this->shared_from_this());
            } else {
                if (_instance->_owner_type == UdpServerClient<T>::Owner::CLIENT)
                    _instance->_socket.close();
            }
        }

        udp::endpoint _remote_endpoint;
        Message<T> _recv_msg;
        Message<T> _send_msg;
        UdpServerClient<T> *_instance;
    };
    /**
     * @brief
     *
     * @tparam T
     */
    template <class T> class UdpServerClient {
        typedef std::shared_ptr<UdpSession<T>> shared_session;

      public:
        enum Owner { SERVER, CLIENT };
        /**
         * @brief Construct a new Udp Server Client object
         *
         * @param io_context
         * @param local_port
         * @param owner_type
         */
        UdpServerClient(boost::asio::io_context &io_context, unsigned short local_port, Owner owner_type = Owner::SERVER)
            : _socket(io_context, udp::endpoint(udp::v4(), local_port)), _strand(io_context), _owner_type(owner_type)
        {
            readHeader();
        }
        /**
         * @brief Construct a new Udp Server Client object
         *
         * @param io_context
         * @param host
         * @param server_port
         * @param owner_type
         */
        UdpServerClient(boost::asio::io_context &io_context, std::string host, unsigned short server_port, Owner owner_type = Owner::CLIENT)
            : _socket(io_context), _strand(io_context), _owner_type(owner_type)
        {
            udp::resolver resolver(io_context);
            _server_endpoint = udp::endpoint(boost::asio::ip::address::from_string(host), server_port);
            _socket.open(udp::v4());
            readHeader();
        }
        /**
         * @brief Destroy the Udp Server Client object
         *
         */
        ~UdpServerClient() = default;
        /**
         * @brief
         *
         * @param msg
         */
        void send(const Message<T> &msg)
        {
            // bool writingMsg = !_sendMsg.empty();
            // _sendMsg.push_back(std::make_pair(msg, _server_endpoint));
            // if (!writingMsg)
            writeHeader(msg, _server_endpoint);
        };
        /**
         * @brief
         *
         * @param msg
         * @param target_endpoint
         */
        void send(const Message<T> &msg, udp::endpoint target_endpoint)
        {
            // _sendMsg.push_back(std::make_pair(msg, target_endpoint));
            if (hasClientEndpoint(target_endpoint))
                writeHeader(msg, target_endpoint);
        };
        /**
         * @brief
         *
         * @param msg
         * @param target_endpoint
         */
        void sendToAllClientsExceptOne(const Message<T> &msg, udp::endpoint target_endpoint)
        {
            if (_owner_type == Owner::SERVER) {
                for (auto &client_endpoint : _clients_endpoint)
                    if (client_endpoint != target_endpoint)
                        send(msg, client_endpoint);
            }
        };
        /**
         * @brief
         *
         * @param msg
         */
        void sendToAllClients(const Message<T> &msg)
        {
            static int i = 0;
            if (_owner_type == Owner::SERVER) {
                for (auto &client_endpoint : _clients_endpoint) {
                    std::cout << i << std::endl;
                    i++;
                    send(msg, client_endpoint);
                }
            }
        };

      protected:
        /**
         * @brief
         *
         * @param target_endpoint
         * @param msg
         */
        virtual void onMessage(udp::endpoint target_endpoint, Message<T> &msg)
        {
            static_cast<void>(target_endpoint);
            static_cast<void>(msg);
        }

        std::vector<udp::endpoint> _clients_endpoint;

      private:
        /**
         * @brief
         *
         */
        void readHeader()
        {
            auto session = std::make_shared<UdpSession<T>>(this);

            _socket.async_receive_from(boost::asio::buffer(&session->_recv_msg.header, sizeof(Header<T>)), session->_remote_endpoint,
                _strand.wrap(boost::bind(
                    &UdpServerClient::handleReceiveReadHeader, this, session, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
        }
        /**
         * @brief
         *
         * @param session
         */
        void readBody(shared_session const &session)
        {
            _socket.async_receive_from(boost::asio::buffer(session->_recv_msg.body.data(), session->_recv_msg.body.size()), session->_remote_endpoint,
                _strand.wrap(boost::bind(
                    &UdpServerClient::handleReceiveReadBody, this, session, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
            readHeader();
        }
        void handleReceiveReadHeader(shared_session session, const boost::system::error_code &ec, std::size_t /*bytes_transferred*/)
        {
            boost::asio::post(_socket.get_executor(), boost::bind(&UdpSession<T>::handleRequestReadHeader, session, ec));
        }
        void handleReceiveReadBody(shared_session session, const boost::system::error_code &ec, std::size_t /*bytes_transferred*/)
        {
            boost::asio::post(_socket.get_executor(), boost::bind(&UdpSession<T>::handleRequestReadBody, session, ec));
        }
        /**
         * @brief
         *
         * @param target_endpoint
         */
        void writeHeader(const Message<T> &msg, udp::endpoint target_endpoint)
        {
            auto session = std::make_shared<UdpSession<T>>(this);

            session->_remote_endpoint = target_endpoint;
            session->_send_msg = msg;
            boost::asio::post(_socket.get_executor(), _strand.wrap(boost::bind(&UdpServerClient::writeHeaderStrand, this, session)));
        }
        /**
         * @brief
         *
         * @param session
         */
        void writeHeader(shared_session const &session)
        {
            boost::asio::post(_socket.get_executor(), _strand.wrap(boost::bind(&UdpServerClient::writeHeaderStrand, this, session)));
        }
        /**
         * @brief
         *
         * @param session
         */
        void writeHeaderStrand(shared_session const &session)
        {
            _socket.async_send_to(boost::asio::buffer(&session->_send_msg.header, sizeof(Header<T>)), session->_remote_endpoint,
                _strand.wrap(boost::bind(
                    &UdpSession<T>::handleSentWriteHeader, session, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
        }
        /**
         * @brief
         *
         * @param session
         */
        void writeBody(shared_session const &session)
        {
            boost::asio::post(_socket.get_executor(), _strand.wrap(boost::bind(&UdpServerClient::writeBodyStrand, this, session)));
        }
        /**
         * @brief
         *
         * @param session
         */
        void writeBodyStrand(shared_session const &session)
        {
            _socket.async_send_to(boost::asio::buffer(session->_send_msg.body.data(), session->_send_msg.body.size()), session->_remote_endpoint,
                _strand.wrap(
                    boost::bind(&UdpSession<T>::handleSentWriteBody, session, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
        }
        /**
         * @brief Get Or Add the Client Endpoint object
         *
         * @param client_endpoint
         * @return udp::endpoint
         */
        udp::endpoint getOrAddClientEndpoint(udp::endpoint client_endpoint)
        {
            for (auto &it : _clients_endpoint) {
                if (it == client_endpoint)
                    return (it);
            }
            _clients_endpoint.push_back(client_endpoint);
            return (_clients_endpoint.back());
        }
        bool hasClientEndpoint(udp::endpoint client_endpoint)
        {
            for (auto &it : _clients_endpoint) {
                if (it == client_endpoint)
                    return (true);
            }
            return (false);
        }

        udp::socket _socket;
        boost::asio::io_context::strand _strand;
        Owner _owner_type = Owner::SERVER;
        udp::endpoint _server_endpoint;

        friend struct UdpSession<T>;
    };
} // namespace network

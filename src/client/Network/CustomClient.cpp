/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#include "CustomClient.hpp"
#include "../../Ecs/Component/Position.hpp"

CustomClient::CustomClient(boost::asio::io_context& io_context, std::string host, unsigned short server_port) :
    network::UdpServerClient<network::CustomMessage>(io_context, host, server_port, Owner::CLIENT)
{
}

CustomClient::~CustomClient()
{
}

void CustomClient::PingServer()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::PingServer;
    component::Position pos(3, 4);
    // std::cout << pos.getXPosition() << std::endl;
    // std::cout << pos.getYPosition() << std::endl;
    msg << pos;
    // std::cout << pos.getXPosition() << std::endl;
    // std::cout << pos.getYPosition() << std::endl;
    std::cout << "void PingServer()" << std::endl;
    send(msg);
}

void CustomClient::onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    static_cast<void>(target_endpoint);
    std::cout << "ici2" << std::endl;
    switch (msg.header.id)
    {
        case network::CustomMessage::PingServer:
        {
            std::cout << "[" << msg.header.id << "]: Server Ping\n";
            component::Position pos(3, 4);
            std::cout << pos.getXPosition() << std::endl;
            std::cout << pos.getYPosition() << std::endl;
            msg >> pos;
            std::cout << pos.getXPosition() << std::endl;
            std::cout << pos.getYPosition() << std::endl;
            std::cout << "int main(int ac, char **av)" << std::endl;
            // component::Position pos(1, 2);
            // std::cout << pos.getXPosition() << std::endl;
            // std::cout << pos.getYPosition() << std::endl;
            // msg >> pos;
            // std::cout << pos.getXPosition() << std::endl;
            // std::cout << pos.getYPosition() << std::endl;
            // std::cout << "void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override" << std::endl;
            // pos.setXPosition(1);
            // pos.setYPosition(2);
            // msg << pos;
            // // Simply bounce message back to client
            // send(msg, target_endpoint);
        }
        break;

    // case network::CustomMsgTypes::MessageAll:
    // {
    //     std::cout << "[" << client->GetID() << "]: Message All\n";

    //     // Construct a new message and send it to all clients
    //     olc::net::message<CustomMsgTypes> msg;
    //     msg.header.id = CustomMsgTypes::ServerMessage;
    //     msg << client->GetID();
    //     MessageAllClients(msg, client);

    // }
    // break;
    }
}
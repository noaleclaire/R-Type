/*
** EPITECH PROJECT, 2022
** CustomServer
** File description:
** CustomServer
*/

#include "CustomServer.hpp"
#include "../../Ecs/Component/Position.hpp"

CustomServer::CustomServer(boost::asio::io_context& io_context, unsigned short local_port) :
    network::UdpServerClient<network::CustomMessage>(io_context, local_port, Owner::SERVER)
{
}

CustomServer::~CustomServer()
{
}

void CustomServer::onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    std::cout << "ici" << std::endl;
    switch (msg.header.id)
    {
        case network::CustomMessage::PingServer:
        {
            // std::cout << "[" << clientId << "]: Server Ping\n";

            component::Position pos(1, 2);
            std::cout << pos.getXPosition() << std::endl;
            std::cout << pos.getYPosition() << std::endl;
            msg >> pos;
            std::cout << pos.getXPosition() << std::endl;
            std::cout << pos.getYPosition() << std::endl;
            std::cout << "void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override" << std::endl;
            pos.setXPosition(1);
            pos.setYPosition(2);
            msg << pos;
            // Simply bounce message back to client
            send(msg, target_endpoint);
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
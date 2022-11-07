/*
** EPITECH PROJECT, 2022
** Room
** File description:
** Room
*/

#pragma once
#include <chrono>
#include <sstream>
#include <iomanip>
#include "ScenesInitializer.hpp"
#include "../../Network/UdpServerClient.hpp"

using time_point = std::chrono::system_clock::time_point;

class CustomServer;
class Room : public ScenesInitializer {
    public:
        Room() = default;
        ~Room() = default;

        static void initScene(CustomServer *server, ecs::Registry &registry, ecs::Scenes which_room, udp::endpoint client_endpoint, bool private_room)
        {
            std::size_t entity;
            registry.setActualScene(which_room);

            network::Message<network::CustomMessage> message;
            message.header.id = network::CustomMessage::GetRoomScene;
            message << which_room;
            server->send(message, client_endpoint);
            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));

            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, 0, 0, 0, 0, 1, 0);
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 1280, 0, -80, 0, 0, 0, 0, 0, 1, 0);
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint);
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 500, 0, -60, 0, 0, 0, 0, 0, 2, 1);
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint);

            std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm tm = *std::gmtime(&tt);
            std::string format = "UTC: %Y-%m-%d %H:%M:%S";
            std::stringstream ss;
            ss << std::put_time(&tm, format.c_str());
            std::size_t hash = std::hash<std::string>{}(ss.str());
            std::string str_hash = std::to_string(hash);
            str_hash.erase(str_hash.begin(), std::next(str_hash.begin(), 10));
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>(str_hash.c_str())));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMID));
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint);

            server->updateSceneRoomInVectorRoom(which_room, private_room, client_endpoint);
        }
};

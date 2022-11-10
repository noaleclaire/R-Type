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
        /**
         * @brief Construct a new Room object
         * 
         */
        Room() = default;
        /**
         * @brief Destroy the Room object
         * 
         */
        ~Room() = default;
        /**
         * @brief 
         * 
         * @param server 
         * @param registry 
         * @param which_room 
         * @param client_endpoint 
         * @param private_room 
         * @param player_name 
         */
        static void initScene(CustomServer *server, ecs::Registry &registry, ecs::Scenes which_room, udp::endpoint client_endpoint, bool private_room, std::string player_name)
        {
            std::size_t entity;

            server->updateSceneRoomInVectorRoom(which_room, private_room, player_name, client_endpoint);

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

            std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm tm = *std::gmtime(&tt);
            std::string format = "UTC: %Y-%m-%d %H:%M:%S";
            std::stringstream ss;
            ss << std::put_time(&tm, format.c_str());
            std::size_t hash = std::hash<std::string>{}(ss.str());
            std::string str_hash = std::to_string(hash);
            while (str_hash.size() > ROOM_ID_SIZE)
                str_hash.pop_back();
            str_hash = "Room ID: " + str_hash;
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>(str_hash.c_str())));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(0, 0, 30, 0));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMID));
            server->sendNetworkComponents<network::CustomMessage>(entity, network::CustomMessage::SendComponent, client_endpoint);
        }
};

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
            message.header.id = network::CustomMessage::GetScene;
            message << which_room;
            server->send(message, client_endpoint);
            std::this_thread::sleep_for(std::chrono::milliseconds(TRANSFER_TIME_COMPONENT));

            //Backgrounds
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, 0, 0, 0, 0, 1, 0);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //Parallax
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 0, 0, -80, 0, 0, 0, 0, 0, 1, 0);
            registry.getComponents<ecs::Type>().at(entity).value().setEntityType(ecs::EntityTypes::PARALLAX);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
            //Logo
                //logo lobby
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 260, 28, 0, 0, 0, 0, 0, 0, 2, 14);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
            //Zone
                //bg lobby mode frame
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 87, 154, 0, 0, 0, 0, 0, 0, 3, 15);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //bg lobby player frame
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 25, 116, 0, 0, 0, 0, 0, 0, 2, 16);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //bg planet level info
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 920, 522, 0, 0, 0, 0, 0, 0, 2, 17);
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);

            //Buttons
                //back arrow
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 34, 31, 0, 0, 0, 0, 6, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::QUITROOM);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //lobby start button
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 25, 634, 0, 0, 0, 0, 12, 2);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::TOGAME);
            registry.addComponent<ecs::Hover>(registry.getEntityById(entity), ecs::Hover());
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //arrow switch mode 1
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 311, 165, 0, 0, 0, 0, 13, 3);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::SWITCHROOMMODE);
            registry.removeComponent<ecs::Pressed>(registry.getEntityById(entity));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //arrow switch mode 2
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 47, 165, 0, 0, 0, 0, 14, 3);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::SWITCHROOMMODE);
            registry.removeComponent<ecs::Drawable>(registry.getEntityById(entity));
            registry.removeComponent<ecs::Pressed>(registry.getEntityById(entity));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);

            //Roommodes
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Position>(registry.getEntityById(entity), ecs::Position(126, 161));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(0, 0, 0, 0));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(4));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMMODE, 0));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);

            //Room ID
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
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(935, 110, 40, 0));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(2));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMID));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);

            //Text
                //start game text
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("START GAME")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(78, 632, 60, 0));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::TEXT));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
            setTextToWaitingHost(registry, entity);
                //player name 1
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>(player_name.c_str())));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(99, 253, 60, 0));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLAYERSNAME));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //player name 2
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(99, 313, 60, 0));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLAYERSNAME));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //player name 3
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(99, 373, 60, 0));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLAYERSNAME));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //player name 4
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(99, 433, 60, 0));
            registry.addComponent<ecs::Drawable>(registry.getEntityById(entity), ecs::Drawable());
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLAYERSNAME));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //info black hole
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("Black Hole")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 550, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLANETINFO));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //info rock planet
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("Dark Cave")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 550, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLANETINFO));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //info fire planet
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("Desert Eagle")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 550, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLANETINFO));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //info ice planet
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("Ice Edge")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 550, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLANETINFO));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //info forest planet
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("Magic Forest")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 550, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMPLANETINFO));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //highscore black hole
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 610, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMHIGHSCORE));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //highscore rock planet
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 610, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMHIGHSCORE));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //highscore fire planet
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 610, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMHIGHSCORE));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //highscore ice planet
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 610, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMHIGHSCORE));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //highscore forest planet
            entity = registry.spawnEntity();
            registry.addComponent<ecs::Text>(registry.getEntityById(entity), ecs::Text(const_cast<char *>("")));
            registry.addComponent<ecs::Rectangle>(registry.getEntityById(entity), ecs::Rectangle(980, 610, 50, 0));
            registry.addComponent<ecs::Layer>(registry.getEntityById(entity), ecs::Layer(3));
            registry.addComponent<ecs::Type>(registry.getEntityById(entity), ecs::Type(ecs::EntityTypes::ROOMHIGHSCORE));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);

            //Planets
                //sun
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BACKGROUND, 552, 254, 0, 0, 0, 0, 0, 0, 3, 18);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //black hole
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 430, 205, 0, 0, 0, 0, 16, 3);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::SELECTPLANET);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            registry.addComponent<ecs::Planet>(registry.getEntityById(entity), ecs::Planet(1, false));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //rock planet
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 600, 485, 0, 0, 0, 0, 17, 3);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::SELECTPLANET);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            registry.addComponent<ecs::Planet>(registry.getEntityById(entity), ecs::Planet(2, false));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //fire planet
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 738, 168, 0, 0, 0, 0, 18, 3);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::SELECTPLANET);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            registry.addComponent<ecs::Planet>(registry.getEntityById(entity), ecs::Planet(3, false));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //ice planet
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 776, 365, 0, 0, 0, 0, 19, 3);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::SELECTPLANET);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            registry.addComponent<ecs::Planet>(registry.getEntityById(entity), ecs::Planet(4, false));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
                //forest planet
            entity = ecs::Factory::createEntity(registry, ecs::EntityTypes::BUTTON, 446, 375, 0, 0, 0, 0, 20, 3);
            registry.getComponents<ecs::Clickable>().at(entity).value().setFunction(ecs::Clickable::Function::SELECTPLANET);
            registry.addComponent<ecs::Animation>(registry.getEntityById(entity), ecs::Animation());
            registry.addComponent<ecs::Planet>(registry.getEntityById(entity), ecs::Planet(5, false));
            server->sendNetworkComponents<network::CustomMessage>(registry, entity, network::CustomMessage::SendComponent, client_endpoint);
        }
        /**
         * @brief Set the Text Component To Waiting Host
         *
         * @param registry
         * @param entity
         */
        static void setTextToWaitingHost(ecs::Registry &registry, std::size_t entity)
        {
            if (registry.getComponents<ecs::Type>().at(entity).value().getEntityType() == ecs::EntityTypes::TEXT) {
                registry.getComponents<ecs::Text>().at(entity).value().setText(const_cast<char *>("waiting for host..."));
                registry.getComponents<ecs::Rectangle>().at(entity).value().setXRectangle(48);
                registry.getComponents<ecs::Rectangle>().at(entity).value().setYRectangle(644);
                registry.getComponents<ecs::Rectangle>().at(entity).value().setWidthRectangle(40);
            }
        }
        /**
         * @brief Set the Text Component to Start Game
         *
         * @param registry
         * @param entity
         */
        static void setTextToStartGame(ecs::Registry &registry, std::size_t entity)
        {
            if (registry.getComponents<ecs::Type>().at(entity).value().getEntityType() == ecs::EntityTypes::TEXT) {
                registry.getComponents<ecs::Text>().at(entity).value().setText(const_cast<char *>("START GAME"));
                registry.getComponents<ecs::Rectangle>().at(entity).value().setXRectangle(78);
                registry.getComponents<ecs::Rectangle>().at(entity).value().setYRectangle(632);
                registry.getComponents<ecs::Rectangle>().at(entity).value().setWidthRectangle(60);
            }
        }
};

/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#include <typeindex>
#include "CustomClient.hpp"
#include "../../Ecs/Exceptions/Exception.hpp"
#include "../Exceptions/Exception.hpp"

CustomClient::CustomClient(boost::asio::io_context &io_context, std::string host, unsigned short server_port)
    : network::UdpServerClient<network::CustomMessage>(io_context, host, server_port)
{
}

CustomClient::~CustomClient()
{
}

void CustomClient::pingServer()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::PingServer;
    send(msg);
}

void CustomClient::initGame(ecs::Scenes room)
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::SwitchToGame;
    msg << room;
    send(msg);
}

void CustomClient::createPublicRoom()
{
    ecs::Text player_name_class(const_cast<char *>(user_info->pseudo));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::CreatePublicRoom;
    msg << player_name_class;
    send(msg);
}

void CustomClient::createPrivateRoom()
{
    ecs::Text player_name_class(const_cast<char *>(user_info->pseudo));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::CreatePrivateRoom;
    msg << player_name_class;
    send(msg);
}

void CustomClient::initListRoom()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::InitListRoom;
    msg << -1;
    send(msg);
}

void CustomClient::joinRoom()
{
    ecs::Text player_name_class(const_cast<char *>(user_info->pseudo));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::JoinRoom;
    msg << player_name_class;
    msg << *actual_scene;
    send(msg);
}

void CustomClient::joinRoomById(int id_room)
{
    ecs::Text player_name_class(const_cast<char *>(user_info->pseudo));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::JoinRoomById;
    msg << player_name_class;
    msg << id_room;
    send(msg);
}

void CustomClient::quitRoom()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::QuitRoomServer;
    send(msg);
}

void CustomClient::switchRoomMode()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::SwitchRoomMode;
    send(msg);
}

void CustomClient::filterByRoomModeVersus()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::InitListRoom;
    msg << 1;
    send(msg);
}

void CustomClient::filterByRoomModeCoop()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::InitListRoom;
    msg << 0;
    send(msg);
}

void CustomClient::clientDisconnect()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::RemoveClient;
    send(msg);
}

void CustomClient::onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg)
{
    static_cast<void>(target_endpoint);
    switch (msg.header.id) {
        case network::CustomMessage::GetRoomScene: {
            ecs::Scenes scene;
            msg >> scene;
            registry->setActualScene(scene);
            graphical->setActualGraphicsEntities(scene);
        } break;
        case network::CustomMessage::SendComponent: {
            std::size_t index_component_create = 0;
            std::size_t entity = 0;
            msg >> index_component_create;
            msg >> entity;
            registry->getNetComponentCreate().at(index_component_create)(msg);
            _tmp_entities_registry.push_back(registry->getEntityById(entity));
        } break;
        case network::CustomMessage::AllComponentSent: {
            _setRectAndSpriteComponent();
            _setTextComponent();
            _setParallax();
            _tmp_entities_registry.clear();
        } break;
        case network::CustomMessage::UpdateListRoom: {
            _setupListRoomScene(msg);
        } break;
        case network::CustomMessage::QuitRoomClient: {
            ecs::Scenes room_scene;
            msg >> room_scene;
            _killEntities(room_scene);
        } break;
        case network::CustomMessage::MaxRoomLimit: {
            _setErrorMessage("Max Number Of Rooms Were Already Be Created");
        } break;
        case network::CustomMessage::MaxPlayersInRoom: {
            _setErrorMessage("Max Number Of Players In This Room Reached");
        } break;
        case network::CustomMessage::RoomDoesntExists: {
            _setErrorMessage("This Room Doesn't Exists");
        } break;
        case network::CustomMessage::NotEnoughPlayer: {
            _setErrorMessage("Not Enough Player In This Room");
        } break;
        default: break;
    }
}

void CustomClient::_setupListRoomScene(network::Message<network::CustomMessage> &msg)
{
    ecs::Scenes tmp_scene = non_shareable_registry->getActualScene();
    non_shareable_registry->setActualScene(ecs::Scenes::LISTROOM);
    graphical->setActualGraphicsEntities(ecs::Scenes::LISTROOM);
    std::size_t nb_rooms = 0;
    std::size_t tmp_nb_rooms = 0;
    ecs::Scenes room_scene;
    std::size_t entity_link_id;
    std::vector<float> rect;
    msg >> nb_rooms;
    for (auto &it : non_shareable_registry->getEntities()) {
        try {
            if (non_shareable_registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::ROOM) {
                non_shareable_registry->removeComponent<ecs::Drawable>(it);
                non_shareable_registry->removeComponent<ecs::CompoScene>(it);
                entity_link_id = non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink();
                non_shareable_registry->removeComponent<ecs::Drawable>(non_shareable_registry->getEntityById(entity_link_id));
                non_shareable_registry->removeComponent<ecs::Text>(non_shareable_registry->getEntityById(entity_link_id));
                non_shareable_registry->removeComponent<ecs::Drawable>(
                    non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink())
                );
            }
        } catch (const ecs::Exception &e) {
            continue;
        }
    }
    for (auto &it : non_shareable_registry->getEntities()) {
        try {
            if (tmp_nb_rooms == nb_rooms)
                break;
            if (non_shareable_registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::ROOM) {
                non_shareable_registry->addComponent<ecs::Drawable>(it, ecs::Drawable());
                msg >> room_scene;
                non_shareable_registry->addComponent<ecs::CompoScene>(it, ecs::CompoScene(room_scene));
                entity_link_id = non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink();
                non_shareable_registry->addComponent<ecs::Drawable>(non_shareable_registry->getEntityById(entity_link_id), ecs::Drawable());
                ecs::Text info_text;
                msg >> info_text;
                non_shareable_registry->addComponent<ecs::Text>(non_shareable_registry->getEntityById(entity_link_id), ecs::Text());
                non_shareable_registry->getComponents<ecs::Text>().at(entity_link_id).value().setText(info_text.getText());
                graphical->addText(entity_link_id, non_shareable_registry->getComponents<ecs::Text>().at(entity_link_id).value().getText(),
                {non_shareable_registry->getComponents<ecs::Rectangle>().at(entity_link_id).value().getXRectangle(),
                non_shareable_registry->getComponents<ecs::Rectangle>().at(entity_link_id).value().getYRectangle(),
                non_shareable_registry->getComponents<ecs::Rectangle>().at(entity_link_id).value().getWidthRectangle()});
                non_shareable_registry->addComponent<ecs::Drawable>(
                    non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()), ecs::Drawable()
                );
                bool roommode_id;
                msg >> roommode_id;
                non_shareable_registry->getComponents<ecs::Type>().at(
                    non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()
                ).value().setEntityID(roommode_id);
                rect = sprites_manager->get_Animations_rect(
                non_shareable_registry->getComponents<ecs::Type>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getEntityType(),
                non_shareable_registry->getComponents<ecs::Type>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getEntityID(), 0);

                non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().setXRectangle(rect.at(0));
                non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().setYRectangle(rect.at(1));
                non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().setWidthRectangle(rect.at(2));
                non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().setHeightRectangle(rect.at(3));
                graphical->addSprite(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink(),
                    sprites_manager->get_Spritesheet(
                        non_shareable_registry->getComponents<ecs::Type>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getEntityType(),
                        non_shareable_registry->getComponents<ecs::Type>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getEntityID()),
                    rect
                );
                graphical->setSpritePosition(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink(),
                non_shareable_registry->getComponents<ecs::Position>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getXPosition(),
                non_shareable_registry->getComponents<ecs::Position>().at(non_shareable_registry->getComponents<ecs::Link>().at(entity_link_id).value().getLink()).value().getYPosition());
                tmp_nb_rooms++;
            }

        } catch (const ecs::Exception &e) {
            continue;
        }
    }
    non_shareable_registry->setActualScene(tmp_scene);
    graphical->setActualGraphicsEntities(*actual_scene);
}

void CustomClient::_setRectAndSpriteComponent()
{
    std::vector<float> rect;

    for (auto &it : _tmp_entities_registry) {
        try {
            rect = sprites_manager->get_Animations_rect(
                registry->getComponents<ecs::Type>().at(it).value().getEntityType(), registry->getComponents<ecs::Type>().at(it).value().getEntityID(), 0);
            registry->getComponents<ecs::Rectangle>().at(it).value().setXRectangle(rect.at(0));
            registry->getComponents<ecs::Rectangle>().at(it).value().setYRectangle(rect.at(1));
            registry->getComponents<ecs::Rectangle>().at(it).value().setWidthRectangle(rect.at(2));
            registry->getComponents<ecs::Rectangle>().at(it).value().setHeightRectangle(rect.at(3));
            graphical->addSprite(it,
                sprites_manager->get_Spritesheet(
                    registry->getComponents<ecs::Type>().at(it).value().getEntityType(), registry->getComponents<ecs::Type>().at(it).value().getEntityID()),
                rect);
            graphical->setSpritePosition(it, registry->getComponents<ecs::Position>().at(it).value().getXPosition(), registry->getComponents<ecs::Position>().at(it).value().getYPosition());
        } catch (const ecs::Exception &e) {
            continue;
        } catch (const Exception &e) {
            continue;
        }
    }
}

void CustomClient::_setTextComponent()
{
    for (auto &it : _tmp_entities_registry) {
        try {
            graphical->addText(it, registry->getComponents<ecs::Text>().at(it).value().getText(),
            {registry->getComponents<ecs::Rectangle>().at(it).value().getXRectangle(),
            registry->getComponents<ecs::Rectangle>().at(it).value().getYRectangle(),
            registry->getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle()});
        } catch (const ecs::Exception &e) {
            continue;
        }
    }
}

void CustomClient::_setParallax()
{
    float x = 0;
    std::size_t entity_id = 0;
    for (auto &it : _tmp_entities_registry) {
        try {
            if (registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::BACKGROUND) {
                entity_id = registry->getComponents<ecs::Type>().at(it).value().getEntityID();
                x = registry->getComponents<ecs::Rectangle>().at(it).value().getWidthRectangle();
            } else if (registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::PARALLAX
            && registry->getComponents<ecs::Type>().at(it).value().getEntityID() == entity_id)
                registry->getComponents<ecs::Position>().at(it).value().setXPosition(x);
        } catch (const ecs::Exception &e) {
            continue;
        }
    }
}

void CustomClient::_setErrorMessage(std::string msg_error)
{
    error_msg_server = true;
    txt_error_msg_server = msg_error;
}

void CustomClient::_killEntities(ecs::Scenes scene)
{
    registry->setActualScene(scene);
    graphical->setActualGraphicsEntities(scene);
    for (auto &it : registry->getEntities())
        registry->killEntity(it);
    graphical->getAllSprites().clear();
    graphical->getAllRectangleShapes().clear();
    graphical->getAllTexts().clear();
}
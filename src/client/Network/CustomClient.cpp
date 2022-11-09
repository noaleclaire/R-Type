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

void CustomClient::initGame()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::SwitchToGame;
    send(msg);
}

void CustomClient::createPublicRoom(char *player_name)
{
    ecs::Text player_name_class(const_cast<char *>(player_name));
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::CreatePublicRoom;
    msg << player_name_class;
    send(msg);
}

void CustomClient::createPrivateRoom()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::CreatePrivateRoom;
    send(msg);
}

void CustomClient::initListRoom()
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::InitListRoom;
    send(msg);
}

void CustomClient::joinRoom(ecs::Scenes scene)
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::JoinRoom;
    msg << scene;
    send(msg);
}

void CustomClient::joinRoomById(int id_room)
{
    network::Message<network::CustomMessage> msg;
    msg.header.id = network::CustomMessage::JoinRoomById;
    msg << id_room;
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
        } break;
        case network::CustomMessage::SendComponent: {
            std::size_t index_component_create = 0;
            msg >> index_component_create;
            registry->getNetComponentCreate().at(index_component_create)(msg);
        } break;
        case network::CustomMessage::AllComponentSent: {
            _setRectAndSpriteComponent();
            _setTextComponent();
        } break;
        case network::CustomMessage::UpdateListRoom: {
            _setupListRoomScene(msg);
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
        default: break;
    }
}

void CustomClient::_setupListRoomScene(network::Message<network::CustomMessage> &msg)
{
    ecs::Scenes tmp_scene = non_shareable_registry->getActualScene();
    non_shareable_registry->setActualScene(ecs::Scenes::LISTROOM);
    std::size_t nb_rooms = 0;
    std::size_t tmp_nb_rooms = 0;
    ecs::Scenes room_scene;
    msg >> nb_rooms;
    for (auto &it : non_shareable_registry->getEntities()) {
        try {
            if (non_shareable_registry->getComponents<ecs::Type>().at(it).value().getEntityType() == ecs::EntityTypes::ROOM) {
                non_shareable_registry->removeComponent<ecs::Drawable>(it);
                non_shareable_registry->removeComponent<ecs::CompoScene>(it);
                non_shareable_registry->removeComponent<ecs::Drawable>(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink()));
                non_shareable_registry->removeComponent<ecs::Text>(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink()));
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
                tmp_nb_rooms++;
                non_shareable_registry->addComponent<ecs::Drawable>(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink()), ecs::Drawable());
                ecs::Text info_text;
                msg >> info_text;
                non_shareable_registry->addComponent<ecs::Text>(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink()), ecs::Text());
                non_shareable_registry->getComponents<ecs::Text>().at(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink())).value().setText(info_text.getText());
                graphical->addText(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink()),
                non_shareable_registry->getComponents<ecs::Text>().at(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink())).value().getText(),
                {non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink())).value().getXRectangle(),
                non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink())).value().getYRectangle(),
                non_shareable_registry->getComponents<ecs::Rectangle>().at(non_shareable_registry->getEntityById(non_shareable_registry->getComponents<ecs::Link>().at(it).value().getLink())).value().getWidthRectangle()});
            }

        } catch (const ecs::Exception &e) {
            continue;
        }
    }
    non_shareable_registry->setActualScene(tmp_scene);
}

void CustomClient::_setRectAndSpriteComponent()
{
    std::vector<float> rect;

    for (auto &it : registry->getEntities()) {
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
    for (auto &it : registry->getEntities()) {
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

void CustomClient::_setErrorMessage(std::string msg_error)
{
    error_msg_server = true;
    txt_error_msg_server = msg_error;
}

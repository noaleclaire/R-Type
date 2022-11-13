/*
** EPITECH PROJECT, 2022
** Core
** File description:
** Core
*/

#include <filesystem>
#include "Core.hpp"
#include "../Utilities/ParserUserInfo.hpp"
#include "../Ecs/Systems/Systems.hpp"
#include "../Utilities/ParserYaml.hpp"
#include "Exceptions/Exception.hpp"
#include "Scenes/Menu.hpp"
#include "Scenes/Settings.hpp"
#include "Scenes/ListRoom.hpp"
#include "Scenes/TypePseudo.hpp"
#include "Scenes/HowToPlay.hpp"
#include "Scenes/Achievements.hpp"

ecs::Scenes Core::actual_scene = ecs::Scenes::MENU;
std::string Core::new_pseudo = "";
std::string Core::room_id = "";
std::size_t Core::level_id = 0;
std::size_t Core::score = 0;
int Core::new_music_volume = 10;
int Core::new_sfx_volume = 10;

Core::Core(boost::asio::io_context &io_context, std::string host, unsigned short server_port) : _io_context(io_context), _client(io_context, host, server_port)
{
    ParserYaml::parseYaml(_sprites_manager, std::filesystem::current_path().append("assets/sprites/sprites_config.yaml").string());
    ParserUserInfo::getUserInfo(_user_info);

    Core::new_music_volume = _user_info.music_volume;
    Core::new_sfx_volume = _user_info.sfx_volume;

    _graphical.sprites_manager = &_sprites_manager;
    _graphical.addAllTextures();

    _actual_registry = &_unique_registry;

    TypePseudo::initScene(_unique_registry, _sprites_manager, _graphical);
    HowToPlay::initScene(_unique_registry, _sprites_manager, _graphical);
    Settings::initScene(_unique_registry, _sprites_manager, _graphical);
    ListRoom::initScene(_unique_registry, _sprites_manager, _graphical);
    Menu::initScene(_unique_registry, _sprites_manager, _graphical);
    Achievements::initScene(_unique_registry, _sprites_manager, _graphical);

    _client.registry = &_shared_registry;
    _client.non_shareable_registry = &_unique_registry;
    _client_thread = std::thread(bind(&boost::asio::io_context::run, boost::ref(io_context)));
    _client.pingServer();
    _client.graphical = &_graphical;
    _client.sprites_manager = &_sprites_manager;
    _client.user_info = &_user_info;
    _client.actual_scene = &Core::actual_scene;

    _graphical.client = &_client;

    _gameLoop();
}

Core::~Core()
{
}

void Core::_setActualRegistry()
{
    if (Core::actual_scene == ecs::Scenes::MENU || Core::actual_scene == ecs::Scenes::SETTINGS || Core::actual_scene == ecs::Scenes::LISTROOM ||
        Core::actual_scene == ecs::Scenes::TYPEPSEUDO || Core::actual_scene == ecs::Scenes::HOWTOPLAY || Core::actual_scene == ecs::Scenes::ACHIEVEMENTS)
        _actual_registry = &_unique_registry;
    else
        _actual_registry = &_shared_registry;
}

void Core::_switchScenesCreateRoom()
{
    if (_last_scene != ecs::Scenes::PUBLICROOM && Core::actual_scene == ecs::Scenes::PUBLICROOM) {
        _client.createPublicRoom();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = ecs::Scenes::MENU;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualGraphicsEntities(Core::actual_scene);
        } else
            Core::actual_scene = _actual_registry->getActualScene();
    }
    if (_last_scene != ecs::Scenes::PRIVATEROOM && Core::actual_scene == ecs::Scenes::PRIVATEROOM) {
        _client.createPrivateRoom();
        std::this_thread::sleep_for(std::chrono::milliseconds(205)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = ecs::Scenes::MENU;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualGraphicsEntities(Core::actual_scene);
        } else
            Core::actual_scene = _actual_registry->getActualScene();
    }
}

void Core::_switchScenesJoinRoom()
{
    if ((_last_scene != ecs::Scenes::ROOM1 && Core::actual_scene == ecs::Scenes::ROOM1) ||
    (_last_scene != ecs::Scenes::ROOM2 && Core::actual_scene == ecs::Scenes::ROOM2) ||
    (_last_scene != ecs::Scenes::ROOM3 && Core::actual_scene == ecs::Scenes::ROOM3)) {
        _actual_registry->setActualScene(Core::actual_scene);
        _client.joinRoom();
        std::this_thread::sleep_for(std::chrono::milliseconds(205)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = ecs::Scenes::LISTROOM;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualGraphicsEntities(Core::actual_scene);
        }
    }
    if (_last_scene != ecs::Scenes::JOINROOMBYID && Core::actual_scene == ecs::Scenes::JOINROOMBYID) {
        _client.joinRoomById(std::stoi(Core::room_id));
        std::this_thread::sleep_for(std::chrono::milliseconds(205)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = ecs::Scenes::LISTROOM;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualGraphicsEntities(Core::actual_scene);
        } else
            Core::actual_scene = _actual_registry->getActualScene();
    }
}

void Core::_switchScenes()
{
    if (_last_scene != ecs::Scenes::TYPEPSEUDO && Core::actual_scene == ecs::Scenes::TYPEPSEUDO)
        _actual_registry->setActualScene(Core::actual_scene);
    if (_last_scene != ecs::Scenes::MENU && Core::actual_scene == ecs::Scenes::MENU)
        _actual_registry->setActualScene(Core::actual_scene);
    if (_last_scene != ecs::Scenes::HOWTOPLAY && Core::actual_scene == ecs::Scenes::HOWTOPLAY)
        _actual_registry->setActualScene(Core::actual_scene);
    if (_last_scene != ecs::Scenes::ACHIEVEMENTS && Core::actual_scene == ecs::Scenes::ACHIEVEMENTS) {
        _actual_registry->setActualScene(Core::actual_scene);
        ecs::Systems::setUserInfoInAchievements(*_actual_registry, _graphical, &_user_info);
    }
    if (_last_scene != ecs::Scenes::SETTINGS && Core::actual_scene == ecs::Scenes::SETTINGS) {
        _actual_registry->setActualScene(Core::actual_scene);
        ecs::Systems::setUserInfoInSettings(*_actual_registry, _graphical, _user_info.pseudo, _user_info.music_volume, _user_info.sfx_volume);
    }
    if (_last_scene != ecs::Scenes::LISTROOM && Core::actual_scene == ecs::Scenes::LISTROOM) {
        _actual_registry->setActualScene(Core::actual_scene);
        _client.initListRoom();
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
    }
    if (_last_scene != ecs::Scenes::QUITROOM && Core::actual_scene == ecs::Scenes::QUITROOM) {
        _client.quitRoom();
        std::cout << "ere" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        Core::actual_scene = ecs::Scenes::LISTROOM;
        _setActualRegistry();
        _actual_registry->setActualScene(Core::actual_scene);
        _graphical.setActualGraphicsEntities(Core::actual_scene);
        _client.initListRoom();
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
    }

    _switchScenesJoinRoom();
    _switchScenesCreateRoom();

    if (_last_scene != ecs::Scenes::GAME && Core::actual_scene == ecs::Scenes::GAME) {
        _client.getGame(_last_scene, Core::level_id);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        if (_client.error_msg_server) {
            std::cout << _client.txt_error_msg_server << std::endl; // handle this text message to print it on the screen
            _client.error_msg_server = false;
            Core::actual_scene = _last_scene;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualGraphicsEntities(Core::actual_scene);
        }
    }
    if (_client.game_scene == ecs::Scenes::GAME1 || _client.game_scene == ecs::Scenes::GAME2
    || _client.game_scene == ecs::Scenes::GAME3) {
        Core::actual_scene = _client.game_scene;
        _actual_registry->setActualScene(Core::actual_scene);
        _graphical.setActualGraphicsEntities(Core::actual_scene);
        _client.initGame();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // do calc (TRANSFER_TIME_COMPONENT * nb_components in current scene) + 50 (ms)
        _client.game_scene = ecs::Scenes::GAME;
        switch (Core::level_id)
        {
            case 0:
                _graphical.setActualMusic(ecs::Music::SPACE);
                break;
            case 1:
                _graphical.setActualMusic(ecs::Music::CAVE);
                break;
            case 2:
                _graphical.setActualMusic(ecs::Music::DESERT);
                break;
            case 3:
                _graphical.setActualMusic(ecs::Music::SNOW);
                break;
            case 4:
                _graphical.setActualMusic(ecs::Music::FOREST);
                break;
            default:
                break;
        }
    }
    if (_client.game_scene == ecs::Scenes::RETURNTOGAME) {
        std::cout << "tes" << _actual_registry->getActualScene() << std::endl;
        try {
            for (auto &it : _actual_registry->getEntities())
                _actual_registry->killEntity(it);
            _graphical.getAllSprites().clear();
            _graphical.getAllRectangleShapes().clear();
            _graphical.getAllTexts().clear();
            Core::actual_scene = _client.tmp_scene;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualGraphicsEntities(Core::actual_scene);
            _client.game_scene = ecs::Scenes::GAME;
        } catch (const ecs::Exception &e) {
            Core::actual_scene = ecs::Scenes::MENU;
            _setActualRegistry();
            _actual_registry->setActualScene(Core::actual_scene);
            _graphical.setActualGraphicsEntities(Core::actual_scene);
            _client.game_scene = ecs::Scenes::GAME;
        }
    }

    _switchMusic();
    _last_scene = Core::actual_scene;
}

void Core::_switchMusic()
{
    if (Core::actual_scene == ecs::Scenes::MENU && (_last_scene != ecs::Scenes::SETTINGS && _last_scene != ecs::Scenes::LISTROOM &&
        _last_scene != ecs::Scenes::TYPEPSEUDO && _last_scene != ecs::Scenes::HOWTOPLAY && _last_scene != ecs::Scenes::ACHIEVEMENTS))
            _graphical.setActualMusic(ecs::Music::MUSICMENU, false);
}

void Core::_updateUserInfo()
{
    if (std::strcmp(_user_info.pseudo, "") == 0 && Core::new_pseudo == "") {
        Core::actual_scene = ecs::Scenes::TYPEPSEUDO;
    }
    if (Core::new_pseudo.size() > 0) {
        std::strcpy(_user_info.pseudo, Core::new_pseudo.c_str());
        Core::new_pseudo = "";
    }
    if (Core::new_music_volume > - 1) {
        _user_info.music_volume = Core::new_music_volume;
        Core::new_music_volume = - 1;
    }
    if (Core::new_sfx_volume > - 1) {
        _user_info.sfx_volume = Core::new_sfx_volume;
        Core::new_sfx_volume = - 1;
    }
}

void Core::_updateComponentsServer()
{
    while (1) {
        if (_update_time == -1)
            break;
        if (_update_time >= 20 && _client.is_host == true) {
            for (auto &it : _actual_registry->getEntities())
                _client.sendNetworkComponents<network::CustomMessage>(it, network::CustomMessage::SendComponent);
            _update_time = 0;
        }
    }
}

void Core::_updatePingLatency()
{
    // while (1) {
    //     if (_ping_latency == -1)
    //         break;
    //     if (_ping_latency >= 44) {
    //         _client.pingServer();
    //         _ping_latency = 0;
    //     }
    // }
}

void Core::_gameStop()
{
    _client.clientDisconnect();
    std::this_thread::sleep_for(std::chrono::milliseconds(DISCONNECTION_TIME));
    _io_context.stop();
    if (_client_thread.joinable())
        _client_thread.join();
    // _ping_latency = -1;
    // if (_update_ping_latency.joinable())
    //     _update_ping_latency.join();
    _update_time = -1;
    if (_update_components_server.joinable())
        _update_components_server.join();
}

void Core::_gameLoop()
{
    _graphical.getWindow().create(_graphical.getVideoMode(), ""); // sf::Style::None
    _graphical.getWindow().setFramerateLimit(60);
    _actual_registry->setActualScene(actual_scene);
    // _update_ping_latency = std::thread(&Core::_updatePingLatency, this);
    _update_components_server = std::thread(&Core::_updateComponentsServer, this);
    _graphical.setActualMusic(ecs::Music::MUSICMENU);
    _graphical.getActualMusic().setVolume(Core::new_music_volume);
    try {
        while (_graphical.getWindow().isOpen()) {
            // _ping_latency += graphics::Graphical::world_current_time;
            _update_time += graphics::Graphical::world_current_time;
            _updateUserInfo();
            _graphical.getWorldClock();
            _setActualRegistry();
            _graphical.setActualGraphicsEntities(Core::actual_scene);
            _switchScenes();
            _graphical.handleEvents(*_actual_registry);
            ecs::Systems::Shot(*_actual_registry, _actual_registry->getComponents<ecs::Controllable>(), &_client);
            ecs::Systems::Position(*_actual_registry, _actual_registry->getComponents<ecs::Position>(), _graphical);
            ecs::Systems::Collider(*_actual_registry, _actual_registry->getComponents<ecs::Collider>(), _graphical);
            ecs::Systems::Parallaxe(*_actual_registry, _actual_registry->getComponents<ecs::Type>());
            ecs::Systems::Animation(*_actual_registry, _sprites_manager, _graphical);
            ecs::Systems::Achievement(&_user_info);
            _graphical.draw(*_actual_registry);
        }
    } catch (const Exception &e) {
        _gameStop();
        throw e;
    } catch (std::exception &e) {
        _gameStop();
        throw e;
    }
    _gameStop();
    ParserUserInfo::saveUserInfo(_user_info);
}

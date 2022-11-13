/*
** EPITECH PROJECT, 2022
** CustomClient
** File description:
** CustomClient
*/

#pragma once

#include "../../Network/UdpServerClient.hpp"
#include "../../Ecs/Registry.hpp"
#include "../Sfml/Graphical.hpp"
#include "../Sfml/SpritesManager.hpp"
#include "../UserInfo.hpp"

class CustomClient : public network::UdpServerClient<network::CustomMessage> {
  public:
    /**
     * @brief Construct a new Custom Client object
     *
     * @param io_context
     * @param host
     * @param server_port
     */
    CustomClient(boost::asio::io_context &io_context, std::string host, unsigned short server_port);
    /**
     * @brief Construct a new Custom Client object
     *
     * @param other
     */
    CustomClient(const CustomClient &other) = delete;
    /**
     * @brief Destroy the Custom Client object
     *
     */
    ~CustomClient();
    /**
     * @brief
     *
     * @param other
     * @return CustomClient&
     */
    CustomClient &operator=(const CustomClient &other) = delete;
    /**
     * @brief
     *
     */
    void pingServer();
    /**
     * @brief
     *
     */
    void initGame();
    /**
     * @brief
     *
     * @param room
     */
    void getGame(ecs::Scenes room, std::size_t level_id);
    /**
     * @brief
     *
     */
    void createPublicRoom();
    /**
     * @brief
     *
     */
    void createPrivateRoom();
    /**
     * @brief
     *
     */
    void initListRoom();
    /**
     * @brief
     *
     * @param scene
     */
    void joinRoom();
    /**
     * @brief
     *
     * @param id_room
     */
    void joinRoomById(int id_room);
    /**
     * @brief
     *
     */
    void quitRoom();
    /**
     * @brief
     *
     */
    void createShot(std::size_t linked_entity, ecs::Scenes scene);
    /**
     * @brief
     *
     */
    void switchRoomMode();
    /**
     * @brief
     *
     */
    void filterByRoomModeVersus();
    /**
     * @brief
     *
     */
    void filterByRoomModeCoop();
    /**
     * @brief
     *
     */
    void clientDisconnect();
    /**
     * @brief
     *
     * @param key
     * @param pressed
     * @param entity
     * @param compo
     */
    void sendPlayerPos(int key, bool pressed, std::size_t entity, ecs::Position &pos, ecs::Rectangle &rect);
    /**
     * @brief
     *
     * @tparam T
     * @param registry
     * @param entity
     * @param id_msg
     */
    template <class T>
    void sendNetworkComponents(std::size_t entity, T id_msg)
    {
        for (std::size_t i = 0; i < registry->getNetMessageCreate().size(); i++) {
            try {
                network::Message<T> message = registry->getNetMessageCreate().at(i)(entity, id_msg, i);
                message << registry->getActualScene();
                send(message);
                std::this_thread::sleep_for(std::chrono::milliseconds(ecs::Enum::ping_latency_ms));
            } catch (const ecs::ExceptionComponentNull &e) {
                continue;
            } catch (const ecs::ExceptionIndexComponent &e) {
                continue;
            }
        }
    }
    ecs::Registry *registry;
    ecs::Registry *non_shareable_registry;
    graphics::Graphical *graphical;
    SpritesManager *sprites_manager;
    UserInfo *user_info;
    ecs::Scenes *actual_scene;
    ecs::Scenes game_scene = ecs::Scenes::GAME;
    bool is_host = false;
    bool error_msg_server = false;
    std::string txt_error_msg_server;

  protected:
    /**
     * @brief
     *
     * @param target_endpoint
     * @param msg
     */
    void onMessage(udp::endpoint target_endpoint, network::Message<network::CustomMessage> &msg) override;

  private:
    /**
     * @brief
     *
     * @param msg_error
     */
    void _setErrorMessage(std::string msg_error);
    /**
     * @brief
     *
     */
    void _setupListRoomScene(network::Message<network::CustomMessage> &msg);
    /**
     * @brief
     *
     */
    void _setRectAndSpriteComponent();
    /**
     * @brief
     *
     */
    void _setTextComponent();
    /**
     * @brief
     *
     */
    void _setParallax();
    /**
     * @brief
     *
     * @param scene
     */
    void _killEntities(ecs::Scenes scene);
    void _killOneEntity(std::size_t entity);

    std::vector<ecs::Entity> _tmp_entities_registry;
};

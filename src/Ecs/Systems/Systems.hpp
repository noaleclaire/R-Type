/*
** EPITECH PROJECT, 2022
** Systems
** File description:
** Systems
*/

#pragma once
#include "../../client/Sfml/Graphical.hpp"
#include "../Component/SparseArray.hpp"
#include "../Registry.hpp"
#include "../../client/Network/CustomClient.hpp"

namespace ecs
{
    class Systems {
      public:
        /**
         * @brief
         *
         * @param registry
         * @param drawable
         */
        static void Drawable(Registry &registry, SparseArray<ecs::Drawable> const &drawable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param clickable
         * @param graphical
         */
        static void ClickableReleased(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param clickable
         * @param graphical
         */
        static void ClickablePressed(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param clickable
         * @param graphical
         */
        static void ClickableHeld(Registry &registry, SparseArray<ecs::Clickable> const &clickable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param position
         * @param graphical
         */
        static void Position(Registry &registry, SparseArray<ecs::Position> const &position, graphics::Graphical &graphical);
        /**
         * @brief
         *
         * @param registry
         * @param controllable
         * @param graphical
         */
        static void Controllable(Registry &registry, SparseArray<ecs::Controllable> &controllable, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param parallaxe
         * @param graphical
         */
        static void Parallaxe(Registry &registry, SparseArray<ecs::Type> const &type);
        /**
         * @brief
         *
         * @param registry
         * @param textBox
         * @param graphical
         */
        static void TextBox(Registry &registry, SparseArray<ecs::TextBox> &textBox, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param textBox
         * @param graphical
         */
        static void Hover(Registry &registry, SparseArray<ecs::Hover> &hover, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param graphical
         * @param pseudo
         * @param music_volume
         * @param sfx_volume
         */
        static void setUserInfoInSettings(Registry &registry, graphics::Graphical &graphical, std::string pseudo, int music_volume, int sfx_volume);
        /**
         * @brief
         *
         * @param registry
         * @param sprites_manager
         * @param graphical
         */
        static void Animation(Registry &registry, SpritesManager &sprites_manager, graphics::Graphical &graphical);
        /**
         * @brief System handling shots in client side
         *
         * @param registry
         * @param controllable
         * @param client
         */
        static void Shot(Registry &registry, SparseArray<ecs::Controllable> &controllable, CustomClient *client);
        /**
         * @brief
         *
         * @param registry
         * @param graphical
         */
        static void Killable(Registry &registry, graphics::Graphical &graphical);
        /**
         * @brief
         *
         * @param registry
         * @param collider
         */
        static void Collider(Registry &registry, SparseArray<ecs::Collider> &collider, graphics::Graphical &graphical);
        /**
         * @brief
         *
         * @param user_info
         */
        static void Achievement(UserInfo *user_info);
        /**
         * @brief
         *
         * @param registry
         * @param achievement
         * @param graphical
         */
        static void Achievement(Registry &registry, SparseArray<ecs::Achievement> &achievement, graphics::Graphical &graphical);
        /**
         * @brief Set the User Info In Achievements
         *
         * @param registry
         * @param graphical
         * @param user_info
         */
        static void setUserInfoInAchievements(Registry &registry, graphics::Graphical &graphical, UserInfo *user_info);
        static void updateWindowSize(Registry &registry, std::pair<float, float> new_factor);
        static void updateScoreDisplay(Registry &registry, SparseArray<ecs::Text> &text, graphics::Graphical &graphical);

      private:
        /**
         * @brief Create a shot
         *
         * @param registry
         * @param entity
         * @param client
         */
        static void _createShot(Registry &registry, std::size_t linked_entity, CustomClient *client);
        /**
         * @brief Calcul and return the volume based on two shapes
         *
         * @param registry
         * @param entity
         * @param graphical
         */
        static int _changeVolume(Registry &registry, std::size_t entity, graphics::Graphical *graphical);
        /**
         * @brief Unselect all textbox in the scene
         *
         * @param registry
         * @param textBox
         */
        static void _unselectAllTextBoxes(Registry &registry, SparseArray<ecs::TextBox> &textBox);
        /**
         * @brief Unselect all planet in the scene
         *
         * @param registry
         * @param planet
         * @param graphical
         */
        static void _unselectAllPlanet(Registry &registry, SparseArray<ecs::Planet> &planet, graphics::Graphical *graphical);
        /**
         * @brief
         *
         * @param registry
         * @param entity
         * @param graphical
         */
        static void _sendKillEntity(Registry &registry, std::size_t entity, graphics::Graphical &graphical, ecs::EntityTypes type);
    };
} // namespace ecs

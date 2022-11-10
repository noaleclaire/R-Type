/*
** EPITECH PROJECT, 2022
** CompoScene
** File description:
** CompoScene
*/

#pragma once
#include "../Enum.hpp"
#include "AComponent.hpp"

namespace ecs {
    class CompoScene : public AComponent {
        public:
            /**
             * @brief Construct a new Compo Scene object
             * 
             */
            CompoScene() = default;
            /**
             * @brief Construct a new Compo Scene object
             * 
             * @param scene 
             */
            CompoScene(ecs::Scenes scene)
            {
                _scene = scene;
            };
            /**
             * @brief Construct a new Compo Scene object
             * 
             * @param other 
             */
            CompoScene(const CompoScene &other) = default;
            /**
             * @brief Destroy the Compo Scene object
             * 
             */
            ~CompoScene() = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return CompoScene& 
             */
            CompoScene &operator=(const CompoScene &other) = default;
            /**
             * @brief Set the Scene object
             * 
             * @param scene 
             */
            void setScene(ecs::Scenes scene)
            {
                _scene = scene;
            };
            /**
             * @brief Get the Scene object
             * 
             * @return ecs::Scenes 
             */
            ecs::Scenes getScene() const
            {
                return (_scene);
            };

        protected:
        private:
            ecs::Scenes _scene;
    };
}

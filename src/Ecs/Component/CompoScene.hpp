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
            CompoScene() = default;
            CompoScene(ecs::Scenes scene)
            {
                _scene = scene;
            };
            CompoScene(const CompoScene &other) = default;
            ~CompoScene() = default;
            CompoScene &operator=(const CompoScene &other) = default;

            void setScene(ecs::Scenes scene)
            {
                _scene = scene;
            };
            ecs::Scenes getScene() const
            {
                return (_scene);
            };

        protected:
        private:
            ecs::Scenes _scene;
    };
}

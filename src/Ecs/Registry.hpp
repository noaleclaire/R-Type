/*
** EPITECH PROJECT, 2022
** registry.hpp
** File description:
** registry.hpp
*/

#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <optional>
#include <typeindex>
#include <vector>
#include "Component/SparseArray.hpp"
#include "Component/component.hpp"
#include "Entities/Entity.hpp"
#include "Enum.hpp"
#include "Exceptions/ExceptionEntityUnobtainable.hpp"
#include "Exceptions/ExceptionIndexComponent.hpp"
#include "Exceptions/ExceptionSparseArrayUnobtainable.hpp"
#include <unordered_map>

namespace ecs
{
    class Registry {
      public:
        Registry()
        {
            registerComponents<ecs::Clickable>();
            registerComponents<ecs::Collider>();
            registerComponents<ecs::Controllable>();
            registerComponents<ecs::Drawable>();
            registerComponents<ecs::Type>();
            registerComponents<ecs::Killable>();
            registerComponents<ecs::Layer>();
            registerComponents<ecs::Position>();
            registerComponents<ecs::Shootable>();
            registerComponents<ecs::Shooter>();
            registerComponents<ecs::Rectangle>();
        };
        ~Registry() = default;
        /**
         * @brief
         *
         * @tparam Component
         * @return SparseArray<Component>&
         */
        template <class Component> SparseArray<Component> &registerComponents()
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
            } catch (const std::out_of_range &e) {
                _components_arrays.emplace(std::type_index(typeid(Component)), SparseArray<Component>());
            }
            _components_eraser.push_back([&](Entity &entity) {
                try {
                    std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).erase(entity);
                } catch (const ExceptionIndexComponent &e) {
                    throw ExceptionIndexComponent("Cannot erase this component, bad index", "_components_eraser -> [&](Entity &entity)");
                }
            });
            return (std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))));
        }
        /**
         * @brief Get the Components object
         *
         * @tparam Component
         * @return SparseArray<Component>&
         */
        template <class Component> SparseArray<Component> &getComponents()
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable(
                    "Cannot find the SparseArray of this component type", "template <class Component> SparseArray<Component> &getComponents()");
            }
            return (std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))));
        }
        /**
         * @brief Get the Components object
         *
         * @tparam Component
         * @return SparseArray<Component> const
         */
        template <class Component> SparseArray<Component> const getComponents() const
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable(
                    "Cannot find the SparseArray of this component type", "template <class Component> SparseArray<Component> const getComponents() const");
            }
            return (const_cast<SparseArray<Component>>(std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component))))));
        }
        /**
         * @brief
         *
         * @tparam Component
         * @param to
         * @param c
         * @return SparseArray<Component>::reference_type
         */
        template <typename Component> typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &&c)
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
                std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).insert_at(to, std::forward<Component>(c));
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component> typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &&c)");
            }
            return (std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).at(to));
        }
        /**
         * @brief
         *
         * @tparam Component
         * @param to
         * @param c
         * @return SparseArray<Component>::reference_type
         */
        template <typename Component> typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &c)
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
                std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).insert_at(to, c);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component> typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &c)");
            }
            return (std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).at(to));
        }
        /**
         * @brief
         *
         * @tparam Component
         * @param to
         * @param c
         * @return SparseArray<Component>::reference_type
         */
        template <typename Component> typename SparseArray<Component>::reference_type addComponent(std::size_t const &to, Component &&c)
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
                std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).insert_at(to, std::forward<Component>(c));
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component> typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &&c)");
            }
            return (std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).at(to));
        }
        /**
         * @brief
         *
         * @tparam Component
         * @param to
         * @param c
         * @return SparseArray<Component>::reference_type
         */
        template <typename Component> typename SparseArray<Component>::reference_type addComponent(std::size_t const &to, Component &c)
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
                std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).insert_at(to, c);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component> typename SparseArray<Component>::reference_type addComponent(Entity const &to, Component &c)");
            }
            return (std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).at(to));
        }
        /**
         * @brief
         *
         * @tparam Component
         * @tparam Params
         * @param to
         * @param args
         * @return SparseArray<Component>::reference_type
         */
        template <typename Component, typename... Params> typename SparseArray<Component>::reference_type emplaceComponent(Entity const &to, Params &&...args)
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
                std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).emplace_at(to, args...);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component, typename ... Params> typename SparseArray<Component>::reference_type emplaceComponent(Entity const &to, "
                    "Params &&... args)");
            }
            return (std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).at(to));
        }
        /**
         * @brief
         *
         * @tparam Component
         * @tparam Params
         * @param to
         * @param args
         * @return SparseArray<Component>::reference_type
         */
        template <typename Component, typename... Params>
        typename SparseArray<Component>::reference_type emplaceComponent(std::size_t const &to, Params &&...args)
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
                std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).emplace_at(to, args...);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component, typename ... Params> typename SparseArray<Component>::reference_type emplaceComponent(Entity const &to, "
                    "Params &&... args)");
            }
            return (std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).at(to));
        }
        /**
         * @brief
         *
         * @tparam Component
         * @param from
         */
        template <typename Component> void removeComponent(Entity const &from)
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
                std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).erase(from);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable(
                    "Cannot find the SparseArray of this component type", "template <typename Component> void removeComponent(Entity const &from)");
            }
        }
        /**
         * @brief
         *
         * @tparam Component
         * @param from
         */
        template <typename Component> void removeComponent(std::size_t const &from)
        {
            try {
                _components_arrays.at(std::type_index(typeid(Component)));
                std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component)))).erase(from);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable(
                    "Cannot find the SparseArray of this component type", "template <typename Component> void removeComponent(Entity const &from)");
            }
        }
        /**
         * @brief
         *
         * @param label
         * @return Entity&
         */
        Entity &spawnEntity()
        {
            try {
                _entities.at(_actual_scene);
            } catch (const std::out_of_range &e) {
                _entities.emplace(_actual_scene, std::vector<Entity>());
            }
            std::optional<std::size_t> id = std::nullopt;
            for (int i = _dead_entities.size() - 1; i >= 0; i--) {
                id = _dead_entities.at(i);
                _dead_entities.pop_back();
                break;
            }
            Entity entity(id);
            _entities.at(_actual_scene).push_back(entity);
            return (_entities.at(_actual_scene).back());
        };
        /**
         * @brief
         *
         * @param entity
         */
        void killEntity(Entity &entity)
        {
            _dead_entities.push_back(entity.getId());
            for (auto &it : _components_eraser) {
                try {
                    it(entity);
                } catch (const ExceptionIndexComponent &e) {
                    continue;
                }
            }
            for (std::size_t i = 0; i < _entities.at(_actual_scene).size(); i++) {
                if (_entities.at(_actual_scene).at(i).getId() == entity.getId()) {
                    _entities.at(_actual_scene).erase(std::next(_entities.at(_actual_scene).begin(), i));
                    break;
                }
            }
        };
        /**
         * @brief Get the Entity By Id object
         *
         * @param id
         * @return Entity&
         */
        Entity &getEntityById(std::size_t id)
        {
            for (std::size_t i = 0; i < _entities.at(_actual_scene).size(); i++) {
                if (_entities.at(_actual_scene).at(i).getId() == id)
                    return (_entities.at(_actual_scene).at(i));
            }
            throw ExceptionEntityUnobtainable("Cannot find an entity with this id", "Entity &getEntityById(std::size_t id)");
        };
        /**
         * @brief Get the Entities object
         *
         * @return std::vector<Entity>
         */
        std::vector<Entity> getEntities() const
        {
            try {
                if (_entities.at(_actual_scene).size() == 0) {
                    throw Exception("_entities vector is empty", "std::vector<Entity> getEntities() const");
                }
            } catch (const std::out_of_range &e) {
                throw Exception("_entities vector doesn't exist", "std::vector<Entity> getEntities() const");
            }
            return (_entities.at(_actual_scene));
        };
        /**
         * @brief
         *
         * @param id
         * @return Entity&
         */
        Entity &addEntity(std::size_t id)
        {
            try {
                _entities.at(_actual_scene);
            } catch (const std::out_of_range &e) {
                _entities.emplace(_actual_scene, std::vector<Entity>());
            }
            for (auto &it : _entities.at(_actual_scene)) {
                if (id == it.getId())
                    return (it);
            }
            Entity entity(id);
            _entities.at(_actual_scene).push_back(entity);
            return (_entities.at(_actual_scene).back());
        }
        /**
         * @brief Set the Actual Scene object
         *
         * @param scene
         */
        void setActualScene(ecs::Scenes scene)
        {
            _actual_scene = scene;
        };
        /**
         * @brief Get the Actual Scene object
         *
         * @return ecs::Scenes
         */
        ecs::Scenes getActualScene() const
        {
            return (_actual_scene);
        };

        std::unordered_map<ecs::Scenes, std::vector<Entity>> _entities;

      private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(Entity &)>> _components_eraser;
        std::vector<std::size_t> _dead_entities;
        ecs::Scenes _actual_scene = ecs::Scenes::MENU;
    };
} // namespace ecs

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
#include "Exceptions/ExceptionEntityUnobtainable.hpp"
#include "Exceptions/ExceptionIndexComponent.hpp"
#include "Exceptions/ExceptionSparseArrayUnobtainable.hpp"
#include <unordered_map>

namespace ecs
{
    enum Scenes { MENU, PAUSE, SETTINGS, GAME, WIN };

    class Registry {
      public:
        Registry()
        {
            registerComponents<component::Collider>();
            registerComponents<component::Controllable>();
            registerComponents<component::Drawable>();
            registerComponents<component::Killable>();
            registerComponents<component::Position>();
            registerComponents<component::Shootable>();
            registerComponents<component::Shooter>();
            registerComponents<component::Velocity>();
            registerComponents<component::Rectangle>();
        };
        ~Registry() = default;
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
        Entity &getEntityById(std::size_t id)
        {
            for (std::size_t i = 0; i < _entities.at(_actual_scene).size(); i++) {
                if (_entities.at(_actual_scene).at(i).getId() == id)
                    return (_entities.at(_actual_scene).at(i));
            }
            throw ExceptionEntityUnobtainable("Cannot find an entity with this id", "Entity &getEntityById(std::size_t id)");
        };
        std::vector<Entity> getEntities() const
        {
            return (_entities.at(_actual_scene));
        };
        void setActualScene(ecs::Scenes scene)
        {
            _actual_scene = scene;
        };
        ecs::Scenes getActualScene() const
        {
            return (_actual_scene);
        };

      private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(Entity &)>> _components_eraser;
        std::unordered_map<ecs::Scenes, std::vector<Entity>> _entities;
        std::vector<std::size_t> _dead_entities;
        ecs::Scenes _actual_scene = ecs::Scenes::MENU;
    };
} // namespace ecs

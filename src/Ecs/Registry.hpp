/*
** EPITECH PROJECT, 2022
** registry.hpp
** File description:
** registry.hpp
*/

#pragma once

#include <any>
#include <optional>
#include <typeindex>
#include <vector>
#include "Component/SparseArray.hpp"
#include "Entities/Entity.hpp"
#include "Exceptions/ExceptionEntityLabelExists.hpp"
#include "Exceptions/ExceptionEntityUnobtainable.hpp"
#include "Exceptions/ExceptionIndexComponent.hpp"
#include "Exceptions/ExceptionSparseArrayUnobtainable.hpp"
#include <unordered_map>

namespace ecs
{
    enum Scenes { MENU, PAUSE, SETTINGS, GAME, WIN };

    class Registry {
      public:
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
            return (_components_arrays.at(std::type_index(typeid(Component))));
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
                    "Cannot find the SparseArray of this component type", "template <class Component> SparseArray<Component> &get_components()");
            }
            return (_components_arrays.at(std::type_index(typeid(Component))));
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
                    "Cannot find the SparseArray of this component type", "template <class Component> SparseArray<Component> const get_components() const");
            }
            return (const_cast<SparseArray<Component>>(_components_arrays.at(std::type_index(typeid(Component)))));
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
                _components_arrays.at(std::type_index(typeid(Component))).insert_at(to, std::forward<Component>(c));
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component> typename SparseArray<Component>::reference_type add_component(Entity const &to, Component &&c)");
            }
            return (_components_arrays.at(std::type_index(typeid(Component))).at(to));
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
                _components_arrays.at(std::type_index(typeid(Component))).insert_at(to, c);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component> typename SparseArray<Component>::reference_type add_component(Entity const &to, Component &c)");
            }
            return (_components_arrays.at(std::type_index(typeid(Component))).at(to));
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
                _components_arrays.at(std::type_index(typeid(Component))).emplace_at(to, args...);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable("Cannot find the SparseArray of this component type",
                    "template <typename Component, typename ... Params> typename SparseArray<Component>::reference_type emplace_component(Entity const &to, "
                    "Params &&... args)");
            }
            return (_components_arrays.at(std::type_index(typeid(Component))).at(to));
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
                _components_arrays.at(std::type_index(typeid(Component))).erase(from);
            } catch (const std::out_of_range &e) {
                throw ExceptionSparseArrayUnobtainable(
                    "Cannot find the SparseArray of this component type", "template <typename Component> void remove_component(Entity const &from)");
            }
        }
        /**
         * @brief 
         * 
         * @param label 
         * @return Entity& 
         */
        Entity &spawnEntity(std::string label)
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
            for (std::size_t i = 0; i < _entities.at(_actual_scene).size(); i++) {
                if (_entities.at(_actual_scene).at(i).getLabel().compare(label) == 0)
                    throw ExceptionEntityLabelExists("An entity with this label already exists", "Entity &spawn_entity(std::string label)");
            }
            Entity entity(id);
            entity.setLabel(label);
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
            for (auto &it : _components_arrays)
                it.second.erase(entity);
            for (std::size_t i = 0; i < _entities.at(_actual_scene).size(); i++) {
                if (_entities.at(_actual_scene).at(i).getLabel().compare(entity.getLabel()) == 0)
                    _entities.at(_actual_scene).erase(std::next(_entities.at(_actual_scene).begin(), i));
            }
            entity.setLabel("");
        };
        /**
         * @brief Get the Entity By Label object
         * 
         * @param label 
         * @return Entity& 
         */
        Entity &getEntityByLabel(std::string label)
        {
            for (std::size_t i = 0; i < _entities.at(_actual_scene).size(); i++) {
                if (_entities.at(_actual_scene).at(i).getLabel().compare(label) == 0)
                    return (_entities.at(_actual_scene).at(i));
            }
            throw ExceptionEntityUnobtainable("Cannot find an entity with this label", "Entity &get_entity_by_label(std::string label)");
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
            throw ExceptionEntityUnobtainable("Cannot find an entity with this id", "Entity &get_entity_by_id(std::size_t id)");
        };
        /**
         * @brief Get the Entities object
         * 
         * @return std::vector<Entity> 
         */
        std::vector<Entity> getEntities() const
        {
            return (_entities.at(_actual_scene));
        };
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

      private:
        std::unordered_map<std::type_index, SparseArray<std::any>> _components_arrays;
        std::unordered_map<ecs::Scenes, std::vector<Entity>> _entities;
        std::vector<std::size_t> _dead_entities;
        ecs::Scenes _actual_scene = ecs::Scenes::MENU;
    };
} // namespace ecs

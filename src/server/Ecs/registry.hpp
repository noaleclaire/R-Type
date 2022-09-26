/*
** EPITECH PROJECT, 2022
** registry.hpp
** File description:
** registry.hpp
*/

#pragma once

#include "sparse_array.hpp"
#include "entity_t.hpp"
#include <unordered_map>
#include <any>
#include <vector>
#include <typeindex>
#include <functional>

class registry {
    public:
        template <class Component>
        sparse_array<Component> &register_component()
        {
            if (!_components_arrays.at(std::type_index(typeid(Component)))) {
                _components_arrays[std::type_index(typeid(Component))] = sparse_array<Component>();
            }
            return (_components_arrays.at(std::type_index(typeid(Component))));
        };
        template <class Component>
        sparse_array<Component> &get_components()
        {
            try
            {
                _components_arrays.at(std::type_index(typeid(Component)));
            }
            catch(const std::exception& e)
            {
                throw;
            }
            return (*_components_arrays.at(std::type_index(typeid(Component))));
        };
        template <class Component>
        sparse_array<Component> const get_components() const
        {
            try
            {
                _components_arrays.at(std::type_index(typeid(Component)));
            }
            catch(const std::exception& e)
            {
                throw;
            }
            return (const_cast<sparse_array<Component>>(_components_arrays.at(std::type_index(typeid(Component)))));
        };

        entity_t spawn_entity()
        {
            ;
        };
        entity_t entity_from_index(std::size_t idx)
        {
            ;
        };
        void kill_entity(entity_t const &e)
        {
            ;
        };
        template <typename Component>
        typename sparse_array<Component>::reference_type add_component(entity_t const &to, Component &&c)
        {
            try
            {
                _components_arrays.at(std::type_index(typeid(Component)));
            }
            catch(const std::exception& e)
            {
                throw;
            }
            if (!_components_arrays.at(std::type_index(typeid(Component))).get_index(std::forward<Component>(c))) {
                _components_arrays.at(std::type_index(typeid(Component))).insert_at(to, std::forward<Component>(c));
            }
        };
        template <typename Component, typename ... Params>
        typename sparse_array<Component>::reference_type emplace_component(entity_t const &to, Params &&... p)
        {
            try
            {
                _components_arrays.at(std::type_index(typeid(Component)));
            }
            catch(const std::exception& e)
            {
                throw;
            }
            _components_arrays.at(std::type_index(typeid(Component))).emplace_at(to, std::forward<Component>(c));
        };
        template <typename Component>
        void remove_component(entity_t const &from)
        {
            try
            {
                _components_arrays.at(std::type_index(typeid(Component)));
            }
            catch(const std::exception& e)
            {
                throw;
            }
            if (!_components_arrays.at(std::type_index(typeid(Component))).get_index(from)) {
                _components_arrays.at(std::type_index(typeid(Component))).erase(from);
            }
        };
    private:
        std::unordered_map<std::type_index, sparse_array<std::any>> _components_arrays;
        // std::function<void(registry &, entity_t const &)>
};
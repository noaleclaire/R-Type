/*
** EPITECH PROJECT, 2022
** SparseArray
** File description:
** SparseArray
*/

#pragma once
#include <iostream>
#include <optional>
#include <vector>
#include "../Exceptions/ExceptionComponentNull.hpp"
#include "../Exceptions/ExceptionIndexComponent.hpp"

namespace ecs
{
    template <typename Component> class SparseArray {
      public:
        using value_type = std::optional<Component>; // optional component type
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<value_type>;
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

      public:
        SparseArray(){}; // You can add more constructors.
        SparseArray(SparseArray const &other)
        {
            for (size_type i = 0; i < size(); i++)
                other._data.push_back(_data.at(i));
        }; // copy constructor
        SparseArray(SparseArray &&other) noexcept
        {
            for (size_type i = 0; i < size(); i++)
                other._data.push_back(std::move(_data.at(i)));
        }; // move constructor
        ~SparseArray() = default;
        SparseArray &operator=(SparseArray const &other)
        {
            for (size_type i = 0; i < size(); i++)
                other._data.push_back(_data.at(i));
        }; // copy assignment operator
        SparseArray &operator=(SparseArray &&other) noexcept
        {
            for (size_type i = 0; i < size(); i++)
                other._data.push_back(std::move(_data.at(i)));
        }; // move assignment operator
        reference_type operator[](size_t idx)
        {
            try {
                if (!_data.at(idx))
                    throw ExceptionComponentNull("Component doesn't exist", "reference_type operator[](size_t idx)");
                return (_data.at(idx));
            } catch (const std::out_of_range &e) {
                throw ExceptionIndexComponent("Bad index", "reference_type operator[](size_t idx)");
            }
        };
        const_reference_type operator[](size_t idx) const
        {
            try {
                if (!_data.at(idx))
                    throw ExceptionComponentNull("Component doesn't exist", "const_reference_type operator[](size_t idx) const");
                return (_data.at(idx));
            } catch (const std::out_of_range &e) {
                throw ExceptionIndexComponent("Bad index", "const_reference_type operator[](size_t idx) const");
            }
        };
        iterator begin()
        {
            return (_data.begin());
        };
        const_iterator begin() const
        {
            return (_data.begin());
        };
        const_iterator cbegin() const
        {
            return (_data.cbegin());
        };
        iterator end()
        {
            return (_data.end());
        };
        const_iterator end() const
        {
            return (_data.end());
        };
        const_iterator cend() const
        {
            return (_data.cend());
        };
        size_type size() const
        {
            return (_data.size());
        };
        reference_type at(size_type idx)
        {
            try {
                if (!_data.at(idx))
                    throw ExceptionComponentNull("Component doesn't exist", "reference_type at(size_type idx)");
                return (_data.at(idx));
            } catch (const std::out_of_range &e) {
                throw ExceptionIndexComponent("Bad index", "reference_type at(size_type idx)");
            }
        };
        const_reference_type at(size_type idx) const
        {
            try {
                if (!_data.at(idx))
                    throw ExceptionComponentNull("Component doesn't exist", "const_reference_type at(size_type idx) const");
                return (_data.at(idx));
            } catch (const std::out_of_range &e) {
                throw ExceptionIndexComponent("Bad index", "reference_type at(size_type idx)");
            }
        };
        reference_type insert_at(size_type idx, Component const &compo)
        {
            std::cout << "oui" << std::endl;
            if (idx >= size())
                _data.resize((size() + 1) + (idx - size()));
            erase(idx);
            try {
                _data.at(idx).emplace(compo);
                return (_data.at(idx));
            } catch (std::out_of_range &e) {
                throw ExceptionIndexComponent("Cannot insert this component, bad index", "reference_type insert_at(size_type idx, Component const &compo)");
            }
        };
        reference_type insert_at(size_type idx, Component &&compo)
        {
            std::cout << "non" << std::endl;
            if (idx >= size())
                _data.resize((size() + 1) + (idx - size()));
            try {
                _data.at(idx).emplace(compo);
                return (_data.at(idx));
            } catch (const std::out_of_range &e) {
                throw ExceptionIndexComponent("Cannot insert this component, bad index", "reference_type insert_at(size_type idx, Component &&compo)");
            }
        };
        template <class... Params> reference_type emplace_at(size_type idx, Params &&...args)
        {
            std::cout << "lol" << std::endl;
            if (idx >= size())
                _data.resize((size() + 1) + (idx - size()));
            try {
                _data.at(idx).emplace(Component(args...));
                return (_data.at(idx));
            } catch (const std::out_of_range &e) {
                throw ExceptionIndexComponent(
                    "Cannot emplace this component, bad index", "template <class... Params> reference_type emplace_at(size_type idx, Params &&...)");
            }
        } // optional
        void erase(size_type idx)
        {
            try {
                _data.at(idx).reset();
            } catch (const std::out_of_range &e) {
                throw ExceptionIndexComponent("Cannot erase this component, bad index", "void erase(size_type idx)");
            }
        };
        size_type get_index(value_type const &compo) const
        {
            for (size_type idx = 0; idx < size(); idx++) {
                if (std::addressof(_data.at(idx)) == std::addressof(compo))
                    return (idx);
            }
            throw ExceptionIndexComponent("Cannot find this component in the SparseArray", "size_type get_index(value_type const &compo) const");
        };

      private:
        container_t _data;
    };
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** MapMemberFunctionPointer
** File description:
** MapMemberFunctionPointer
*/

#pragma once
#include <string>
#include <unordered_map>

template <class T> class MapMemberFunctionPointer {
  public:
    MapMemberFunctionPointer() = default;
    ~MapMemberFunctionPointer() = default;

    void insert(std::string key, T function)
    {
        _map_fptr.insert(std::make_pair(key, function));
    }

    template <class U, class A, class... Params> U searchAndCall(A obj, std::string key, Params &&...args)
    {
        T fp = _map_fptr.at(key);
        return (obj->*fp)(args...);
    }

  protected:
  private:
    std::unordered_map<std::string, T> _map_fptr;
};

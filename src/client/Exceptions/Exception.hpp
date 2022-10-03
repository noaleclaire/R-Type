/*
** EPITECH PROJECT, 2022
** Exception
** File description:
** Exception
*/

#pragma once
#include <string>

class Exception : public std::exception {
  public:
    Exception(const std::string &message, const std::string &location)
    {
        _message = message;
        _location = location;
    };
    ~Exception() = default;

    const char *what() const noexcept override
    {
        return (_message.c_str());
    };

    const char *where() const noexcept
    {
        return (_location.c_str());
    };

  protected:
  private:
    std::string _message;
    std::string _location;
};

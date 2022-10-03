/*
** EPITECH PROJECT, 2022
** ExceptionDirectoryNotFound
** File description:
** ExceptionDirectoryNotFound
*/

#pragma once
#include "Exception.hpp"

class ExceptionDirectoryNotFound : public Exception {
  public:
    ExceptionDirectoryNotFound(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionDirectoryNotFound() = default;

  protected:
  private:
};

/*
** EPITECH PROJECT, 2022
** ExceptionFileNotFound
** File description:
** ExceptionFileNotFound
*/

#pragma once
#include "Exception.hpp"

class ExceptionFileNotFound : public Exception {
  public:
    ExceptionFileNotFound(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionFileNotFound() = default;

  protected:
  private:
};

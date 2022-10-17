/*
** EPITECH PROJECT, 2022
** ExceptionNoAnimAttribute
** File description:
** ExceptionNoAnimAttribute
*/

#pragma once
#include "Exception.hpp"

class ExceptionNoAnimAttribute : public Exception {
  public:
    ExceptionNoAnimAttribute(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionNoAnimAttribute() = default;

  protected:
  private:
};

/*
** EPITECH PROJECT, 2022
** ExceptionNotANumber
** File description:
** ExceptionNotANumber
*/

#pragma once
#include "Exception.hpp"

class ExceptionNotANumber : public Exception {
  public:
    ExceptionNotANumber(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionNotANumber() = default;

  protected:
  private:
};

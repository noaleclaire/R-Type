/*
** EPITECH PROJECT, 2022
** ExceptionNotAnInteger
** File description:
** ExceptionNotAnInteger
*/

#pragma once
#include "Exception.hpp"

class ExceptionNotAnInteger : public Exception {
  public:
    ExceptionNotAnInteger(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionNotAnInteger() = default;

  protected:
  private:
};

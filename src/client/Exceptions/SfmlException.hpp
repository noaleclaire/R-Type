/*
** EPITECH PROJECT, 2022
** SfmlException
** File description:
** SfmlException
*/

#pragma once
#include "Exception.hpp"

class SfmlException : public Exception {
  public:
    SfmlException(const std::string &message, const std::string &location) : Exception(message, location){};
    ~SfmlException() = default;

  protected:
  private:
};

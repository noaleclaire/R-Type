/*
** EPITECH PROJECT, 2022
** SfmlExceptionTexture
** File description:
** SfmlExceptionSfmlExceptionTexture
*/

#pragma once
#include "SfmlException.hpp"

class SfmlExceptionTexture : public SfmlException {
  public:
    SfmlExceptionTexture(const std::string &message, const std::string &location) : SfmlException(message, location){};
    ~SfmlExceptionTexture() = default;

  protected:
  private:
};

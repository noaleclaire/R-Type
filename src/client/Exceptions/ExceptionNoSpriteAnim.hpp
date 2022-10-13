/*
** EPITECH PROJECT, 2022
** ExceptionNoSpriteAnim
** File description:
** ExceptionNoSpriteAnim
*/

#pragma once
#include "Exception.hpp"

class ExceptionNoSpriteAnim : public Exception {
  public:
    ExceptionNoSpriteAnim(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionNoSpriteAnim() = default;

  protected:
  private:
};

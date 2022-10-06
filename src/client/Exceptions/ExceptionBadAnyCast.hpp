/*
** EPITECH PROJECT, 2022
** ExceptionBadAnyCast
** File description:
** ExceptionBadAnyCast
*/

#pragma once
#include "Exception.hpp"

class ExceptionBadAnyCast : public Exception {
  public:
    ExceptionBadAnyCast(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionBadAnyCast() = default;

  protected:
  private:
};

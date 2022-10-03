/*
** EPITECH PROJECT, 2022
** ExceptionBadFileName
** File description:
** ExceptionBadFileName
*/

#pragma once
#include "Exception.hpp"

class ExceptionBadFileName : public Exception {
  public:
    ExceptionBadFileName(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionBadFileName() = default;

  protected:
  private:
};

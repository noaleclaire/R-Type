/*
** EPITECH PROJECT, 2022
** ExceptionBadYamlWord
** File description:
** ExceptionBadYamlWord
*/

#pragma once
#include "Exception.hpp"

class ExceptionBadYamlWord : public Exception {
  public:
    ExceptionBadYamlWord(const std::string &message, const std::string &location) : Exception(message, location){};
    ~ExceptionBadYamlWord() = default;

  protected:
  private:
};

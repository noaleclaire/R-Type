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
    /**
     * @brief Construct a new Exception Bad Yaml Word object
     *
     * @param message
     * @param location
     */
    ExceptionBadYamlWord(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception Bad Yaml Word object
     *
     */
    ~ExceptionBadYamlWord() = default;

  protected:
  private:
};

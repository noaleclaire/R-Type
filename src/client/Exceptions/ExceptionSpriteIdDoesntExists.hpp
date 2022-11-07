/*
** EPITECH PROJECT, 2022
** ExceptionSpriteIdDoesntExists
** File description:
** ExceptionSpriteIdDoesntExists
*/

#pragma once
#include "Exception.hpp"

class ExceptionSpriteIdDoesntExists : public Exception {
  public:
    /**
     * @brief Construct a new Exception Bad Any Cast object
     *
     * @param message
     * @param location
     */
    ExceptionSpriteIdDoesntExists(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception Bad Any Cast object
     *
     */
    ~ExceptionSpriteIdDoesntExists() = default;

  protected:
  private:
};

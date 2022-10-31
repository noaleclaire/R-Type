/*
** EPITECH PROJECT, 2022
** ExceptionSpriteIdExists
** File description:
** ExceptionSpriteIdExists
*/

#pragma once
#include "Exception.hpp"

class ExceptionSpriteIdExists : public Exception {
  public:
    /**
     * @brief Construct a new Exception Bad Any Cast object
     *
     * @param message
     * @param location
     */
    ExceptionSpriteIdExists(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception Bad Any Cast object
     *
     */
    ~ExceptionSpriteIdExists() = default;

  protected:
  private:
};

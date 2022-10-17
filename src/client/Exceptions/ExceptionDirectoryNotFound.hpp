/*
** EPITECH PROJECT, 2022
** ExceptionDirectoryNotFound
** File description:
** ExceptionDirectoryNotFound
*/

#pragma once
#include "Exception.hpp"

class ExceptionDirectoryNotFound : public Exception {
  public:
    /**
     * @brief Construct a new Exception Directory Not Found object
     *
     * @param message
     * @param location
     */
    ExceptionDirectoryNotFound(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception Directory Not Found object
     *
     */
    ~ExceptionDirectoryNotFound() = default;

  protected:
  private:
};

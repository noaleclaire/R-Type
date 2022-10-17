/*
** EPITECH PROJECT, 2022
** ExceptionFileNotFound
** File description:
** ExceptionFileNotFound
*/

#pragma once
#include "Exception.hpp"

class ExceptionFileNotFound : public Exception {
  public:
    /**
     * @brief Construct a new Exception File Not Found object
     *
     * @param message
     * @param location
     */
    ExceptionFileNotFound(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception File Not Found object
     *
     */
    ~ExceptionFileNotFound() = default;

  protected:
  private:
};

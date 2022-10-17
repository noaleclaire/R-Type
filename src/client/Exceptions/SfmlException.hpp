/*
** EPITECH PROJECT, 2022
** SfmlException
** File description:
** SfmlException
*/

#pragma once
#include "Exception.hpp"

class SfmlException : public Exception {
  public:
    /**
     * @brief Construct a new Sfml Exception object
     *
     * @param message
     * @param location
     */
    SfmlException(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Sfml Exception object
     *
     */
    ~SfmlException() = default;

  protected:
  private:
};

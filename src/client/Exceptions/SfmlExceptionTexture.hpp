/*
** EPITECH PROJECT, 2022
** SfmlExceptionTexture
** File description:
** SfmlExceptionSfmlExceptionTexture
*/

#pragma once
#include "SfmlException.hpp"

class SfmlExceptionTexture : public SfmlException {
  public:
    /**
     * @brief Construct a new Sfml Exception Texture object
     *
     * @param message
     * @param location
     */
    SfmlExceptionTexture(const std::string &message, const std::string &location) : SfmlException(message, location){};
    /**
     * @brief Destroy the Sfml Exception Texture object
     *
     */
    ~SfmlExceptionTexture() = default;

  protected:
  private:
};

/*
** EPITECH PROJECT, 2022
** ExceptionNoSpriteAnim
** File description:
** ExceptionNoSpriteAnim
*/

#pragma once
#include "Exception.hpp"

class ExceptionNoSpriteAnim : public Exception {
  public:
    /**
     * @brief Construct a new Exception No Sprite Anim object
     *
     * @param message
     * @param location
     */
    ExceptionNoSpriteAnim(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception No Sprite Anim object
     *
     */
    ~ExceptionNoSpriteAnim() = default;

  protected:
  private:
};

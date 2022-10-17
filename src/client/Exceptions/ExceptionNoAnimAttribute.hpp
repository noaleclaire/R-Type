/*
** EPITECH PROJECT, 2022
** ExceptionNoAnimAttribute
** File description:
** ExceptionNoAnimAttribute
*/

#pragma once
#include "Exception.hpp"

class ExceptionNoAnimAttribute : public Exception {
  public:
    /**
     * @brief Construct a new Exception No Anim Attribute object
     *
     * @param message
     * @param location
     */
    ExceptionNoAnimAttribute(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception No Anim Attribute object
     *
     */
    ~ExceptionNoAnimAttribute() = default;

  protected:
  private:
};

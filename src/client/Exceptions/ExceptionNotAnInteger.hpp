/*
** EPITECH PROJECT, 2022
** ExceptionNotAnInteger
** File description:
** ExceptionNotAnInteger
*/

#pragma once
#include "Exception.hpp"

class ExceptionNotAnInteger : public Exception {
  public:
  /**
   * @brief Construct a new Exception Not An Integer object
   * 
   * @param message 
   * @param location 
   */
    ExceptionNotAnInteger(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception Not An Integer object
     * 
     */
    ~ExceptionNotAnInteger() = default;

  protected:
  private:
};

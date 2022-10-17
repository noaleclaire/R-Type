/*
** EPITECH PROJECT, 2022
** ExceptionNotANumber
** File description:
** ExceptionNotANumber
*/

#pragma once
#include "Exception.hpp"

class ExceptionNotANumber : public Exception {
  public:
    /**
     * @brief Construct a new Exception Not A Number object
     *
     * @param message
     * @param location
     */
    ExceptionNotANumber(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception Not A Number object
     *
     */
    ~ExceptionNotANumber() = default;

  protected:
  private:
};

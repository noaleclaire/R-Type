/*
** EPITECH PROJECT, 2022
** ExceptionBadAnyCast
** File description:
** ExceptionBadAnyCast
*/

#pragma once
#include "Exception.hpp"

class ExceptionBadAnyCast : public Exception {
  public:
    /**
     * @brief Construct a new Exception Bad Any Cast object
     *
     * @param message
     * @param location
     */
    ExceptionBadAnyCast(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception Bad Any Cast object
     *
     */
    ~ExceptionBadAnyCast() = default;

  protected:
  private:
};

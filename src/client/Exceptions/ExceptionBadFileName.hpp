/*
** EPITECH PROJECT, 2022
** ExceptionBadFileName
** File description:
** ExceptionBadFileName
*/

#pragma once
#include "Exception.hpp"

class ExceptionBadFileName : public Exception {
  public:
    /**
     * @brief Construct a new Exception Bad File Name object
     *
     * @param message
     * @param location
     */
    ExceptionBadFileName(const std::string &message, const std::string &location) : Exception(message, location){};
    /**
     * @brief Destroy the Exception Bad File Name object
     *
     */
    ~ExceptionBadFileName() = default;

  protected:
  private:
};

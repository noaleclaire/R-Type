/*
** EPITECH PROJECT, 2022
** ExceptionComponentNull
** File description:
** ExceptionComponentNull
*/

#pragma once
#include "Exception.hpp"

namespace ecs
{
    class ExceptionComponentNull : public Exception {
      public:
        /**
         * @brief Construct a new Exception Component Null object
         *
         * @param message
         * @param location
         */
        ExceptionComponentNull(const std::string &message, const std::string &location) : Exception(message, location){};
        /**
         * @brief Destroy the Exception Component Null object
         *
         */
        ~ExceptionComponentNull() = default;

      protected:
      private:
    };
} // namespace ecs

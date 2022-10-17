/*
** EPITECH PROJECT, 2022
** ExceptionIndexComponent
** File description:
** ExceptionIndexComponent
*/

#pragma once
#include "Exception.hpp"

namespace ecs
{
    class ExceptionIndexComponent : public Exception {
      public:
        /**
         * @brief Construct a new Exception Index Component object
         *
         * @param message
         * @param location
         */
        ExceptionIndexComponent(const std::string &message, const std::string &location) : Exception(message, location){};
        /**
         * @brief Destroy the Exception Index Component object
         *
         */
        ~ExceptionIndexComponent() = default;

      protected:
      private:
    };
} // namespace ecs

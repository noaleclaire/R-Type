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
        ExceptionComponentNull(const std::string &message, const std::string &location) : Exception(message, location){};
        ~ExceptionComponentNull() = default;

      protected:
      private:
    };
} // namespace ecs

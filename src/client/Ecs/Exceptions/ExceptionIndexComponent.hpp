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
        ExceptionIndexComponent(const std::string &message, const std::string &location) : Exception(message, location){};
        ~ExceptionIndexComponent() = default;

      protected:
      private:
    };
} // namespace ecs

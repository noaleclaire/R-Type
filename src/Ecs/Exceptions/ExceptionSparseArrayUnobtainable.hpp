/*
** EPITECH PROJECT, 2022
** ExceptionSparseArrayUnobtainable
** File description:
** ExceptionSparseArrayUnobtainable
*/

#pragma once
#include "Exception.hpp"

namespace ecs
{
    class ExceptionSparseArrayUnobtainable : public Exception {
      public:
        /**
         * @brief Construct a new Exception Sparse Array Unobtainable object
         *
         * @param message
         * @param location
         */
        ExceptionSparseArrayUnobtainable(const std::string &message, const std::string &location) : Exception(message, location){};
        /**
         * @brief Destroy the Exception Sparse Array Unobtainable object
         *
         */
        ~ExceptionSparseArrayUnobtainable() = default;

      protected:
      private:
    };
} // namespace ecs

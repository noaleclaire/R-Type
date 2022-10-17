/*
** EPITECH PROJECT, 2022
** ExceptionEntityUnobtainable
** File description:
** ExceptionEntityUnobtainable
*/

#pragma once
#include "Exception.hpp"

namespace ecs
{
    class ExceptionEntityUnobtainable : public Exception {
      public:
        /**
         * @brief Construct a new Exception Entity Unobtainable object
         *
         * @param message
         * @param location
         */
        ExceptionEntityUnobtainable(const std::string &message, const std::string &location) : Exception(message, location){};
        /**
         * @brief Destroy the Exception Entity Unobtainable object
         *
         */
        ~ExceptionEntityUnobtainable() = default;

      protected:
      private:
    };
} // namespace ecs

/*
** EPITECH PROJECT, 2022
** ExceptionEntityLabelExists
** File description:
** ExceptionEntityLabelExists
*/

#pragma once
#include "Exception.hpp"

namespace ecs
{
    class ExceptionEntityLabelExists : public Exception {
      public:
      /**
       * @brief Construct a new Exception Entity Label Exists object
       * 
       * @param message 
       * @param location 
       */
        ExceptionEntityLabelExists(const std::string &message, const std::string &location) : Exception(message, location){};
        /**
         * @brief Destroy the Exception Entity Label Exists object
         * 
         */
        ~ExceptionEntityLabelExists() = default;

      protected:
      private:
    };
} // namespace ecs

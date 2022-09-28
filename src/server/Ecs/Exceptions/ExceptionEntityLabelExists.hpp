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
            ExceptionEntityLabelExists(const std::string &message, const std::string &location) : Exception(message, location) {};
            ~ExceptionEntityLabelExists() = default;

        protected:
        private:
    };
}

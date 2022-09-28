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
            ExceptionEntityUnobtainable(const std::string &message, const std::string &location) : Exception(message, location) {};
            ~ExceptionEntityUnobtainable() = default;

        protected:
        private:
    };
}

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
            ExceptionSparseArrayUnobtainable(const std::string &message, const std::string &location) : Exception(message, location) {};
            ~ExceptionSparseArrayUnobtainable() = default;

        protected:
        private:
    };
}

#pragma once

#include <stdexcept>

namespace naranja
{
    namespace core
    {
        class StreamClosedException : public std::runtime_error
        {
        public:
            explicit StreamClosedException()
                : std::runtime_error("Stream has been closed.")
            {
            }

            explicit StreamClosedException(const char* message)
                : std::runtime_error(message)
            {
            }
        };

        class ParseFailureException : public std::runtime_error
        {
        public:
            explicit ParseFailureException()
                : std::runtime_error("Failed to parse data.")
            {
            }

            explicit ParseFailureException(const char* message)
                : std::runtime_error(message)
            {
            }
        };

        class TimeoutException : public std::runtime_error
        {
        public:
            explicit TimeoutException()
                : std::runtime_error("Timeout occured.")
            {
            }
        };

        class ObjectDestroyedException : std::runtime_error
        {
        public:
            explicit ObjectDestroyedException()
                : std::runtime_error("Object has already been destroyed.")
            {
            }
        };
    }
}
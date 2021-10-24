// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_EXCEPTION_HPP
#define HARMONY_OPTIC_EXCEPTION_HPP

#include <exception>
#include <string>

namespace Harmony::Optic {
    class Exception : public std::exception {
    public:
        /**
         * Return the error message
         */
        const char *what() const noexcept;

        /**
         * Constructor for optic exception
         * @param message   Error message
         */
        Exception(std::string message) noexcept;

    private:
        /** Error message */
        std::string message;

        /**
         * Print exception error message
         */
        void print_error() noexcept;
    };
}

#endif

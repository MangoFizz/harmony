// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EXCEPTION_HPP
#define HARMONY_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace Harmony {
    class ExceptionBox : public std::runtime_error {
    public:
        /**
         * Constructor for exception message box
         * @param message   Error message
         */
        ExceptionBox(std::string message) noexcept;
    };
}

#endif

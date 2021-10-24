// SPDX-License-Identifier: GPL-3.0-only

#include "../messaging/console_output.hpp"
#include "exception.hpp"

namespace Harmony::Optic {
    const char *Exception::what() const noexcept {
        return this->message.c_str();
    }

    Exception::Exception(std::string message) noexcept {
        this->message = message;
        this->print_error();
    }

    void Exception::print_error() noexcept {
        console_error("[Optic]: %s", message.c_str());
    }
}

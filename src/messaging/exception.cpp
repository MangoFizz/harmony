// SPDX-License-Identifier: GPL-3.0-only

#include "message_box.hpp"
#include "exception.hpp"

namespace Harmony {
    ExceptionBox::ExceptionBox(std::string message) noexcept : std::runtime_error(message) {
        message_box(message.c_str());
    }
}

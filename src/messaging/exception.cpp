// SPDX-License-Identifier: GPL-3.0-only

#include "message_box.hpp"
#include "exception.hpp"

namespace Harmony {
    ExceptionBox::ExceptionBox(std::string message) noexcept {
        message_box(message.c_str());
    }
}

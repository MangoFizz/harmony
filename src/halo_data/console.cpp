// SPDX-License-Identifier: GPL-3.0-only

#include <cstring>
#include "console.hpp"

namespace Harmony::HaloData {
    extern "C" void console_output_asm(const ColorARGB &color, const char *message);

    void console_output_raw(const ColorARGB &color, const char *message) noexcept {
        char message_copy[256];
        std::strncpy(message_copy, message, sizeof(message_copy) - 1);
        console_output_asm(color, message_copy);
    }
}

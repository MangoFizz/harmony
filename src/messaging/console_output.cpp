// SPDX-License-Identifier: GPL-3.0-only

#include <cstring>
#include "console_output.hpp"
#include "../harmony.hpp"

namespace Harmony {
    const char *output_prefix = nullptr;

    static bool output_enabled = false;
    void enable_output(bool enabled) noexcept {
        output_enabled = enabled;
    }

    extern "C" void console_output_asm(const ConsoleColor &color, const char *message);
    void console_output_raw(const ConsoleColor &color, const char *message) noexcept {
        if(!output_enabled) {
            return;
        }
        char message_copy[256];
        if(output_prefix) {
            std::snprintf(message_copy, sizeof(message_copy), "%s: %s", output_prefix, message);
        }
        else {
            std::strncpy(message_copy, message, sizeof(message_copy) - 1);
        }
        console_output_asm(color, message_copy);
    }
}

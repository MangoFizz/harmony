// SPDX-License-Identifier: GPL-3.0-only

#include <string>
#include <cstring>
#include "console_output.hpp"
#include "../harmony.hpp"

namespace Harmony {
    static std::string output_prefix;
    static bool output_enabled = true;

    bool output_is_enabled() noexcept {
        return output_enabled;
    }

    void enable_output(bool enabled) noexcept {
        output_enabled = enabled;
    }

    void set_output_prefix(const char *new_prefix) noexcept {
        output_prefix = new_prefix;
    }

    void clear_output_prefix() noexcept {
        output_prefix.clear();
    }

    void console_output(const HaloData::ColorARGB &color, const char *message) noexcept {
        if(!output_enabled) {
            return;
        }

        if(output_prefix.empty()) {
            HaloData::console_output_raw(color, message);
        }
        else {
            char message_copy[256];
            std::snprintf(message_copy, sizeof(message_copy), "%s: %s", output_prefix.c_str(), message);
            HaloData::console_output_raw(color, message_copy);
        }
    }
}

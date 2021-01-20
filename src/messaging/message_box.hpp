// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_MESSAGE_BOX_HPP
#define HARMONY_MESSAGE_BOX_HPP

#include <cstdio>

namespace Harmony {
    /**
     * Create a dialog with a given message
     * @param message   Message to display
     */
    void message_box(const char *message) noexcept;

    /**
     * Create a dialog with a given message
     * @param format    Message format
     * @param args      Format arguments
     */
    template<typename... Args> void message_box(const char *format, Args... args) noexcept {
        char message[256];
        std::snprintf(message, sizeof(message), format, args...);
        message_box(message);
    }
}

#endif

// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__OUTPUT__CONSOLE_OUTPUT_HPP
#define HARMONY__OUTPUT__CONSOLE_OUTPUT_HPP

#include <cstdio>
#include "../halo_data/console.hpp"

namespace Harmony {
    /**
     * Display a message of a color
     * @param color  Color to use in the message
     * @param format String format (passed to snprintf)
     * @param args   Additional arguments to pass
     */
    template<typename... Args> void console_output(const HaloData::ColorARGB &color, const char *format, Args... args) noexcept {
        char message[256];
        std::snprintf(message, sizeof(message), format, args...);
        HaloData::console_output_raw(color, message);
    }

    /**
     * Display a message (white)
     * @param format String format (passed to snprintf)
     * @param args   Additional arguments to pass
     */
    template<typename... Args> void console_output(const char *format, Args... args) noexcept {
        console_output(HaloData::ColorARGB {1.0, 1.0, 1.0, 1.0}, format, args...);
    }

    /**
     * Display an error (red)
     * @param format String format (passed to snprintf)
     * @param args   Additional arguments to pass
     */
    template<typename... Args> void console_error(const char *format, Args... args) noexcept {
        console_output(HaloData::ColorARGB {1.0, 1.0, 0.25, 0.25}, format, args...);
    }

    /**
     * Display a warning (yellow)
     * @param format String format (passed to snprintf)
     * @param args   Additional arguments to pass
     */
    template<typename... Args> void console_warning(const char *format, Args... args) noexcept {
        console_output(HaloData::ColorARGB {1.0, 1.0, 1.0, 0.125}, format, args...);
    }
}

#endif

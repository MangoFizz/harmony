// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__OUTPUT__CONSOLE_OUTPUT_HPP
#define HARMONY__OUTPUT__CONSOLE_OUTPUT_HPP

#include <cstdio>
#include "../halo_data/console.hpp"

namespace Harmony {
    /**
     * Get whether or not output is enabled
     */
    bool output_is_enabled() noexcept;

    /**
     * Set whether or not to enable output
     * @param enabled set to true if output should be enabled
     */
    void enable_output(bool enabled) noexcept;

    /**
     * Set console output prefix
     * @param prefix    string to append at the start of console output
     */
    void set_output_prefix(const char *new_prefix) noexcept;

    /**
     * Clear console output prefix
     */
    void clear_output_prefix() noexcept;

    /**
     * Display a message of a color
     * @param color   Color to use in the message
     * @param message Message to use
     */
    void console_output(const HaloData::ColorARGB &color, const char *message) noexcept;

    /**
     * Display a message of a color
     * @param color  Color to use in the message
     * @param format String format (passed to snprintf)
     * @param args   Additional arguments to pass
     */
    template<typename... Args> void console_output(const HaloData::ColorARGB &color, const char *format, Args... args) noexcept {
        char message[256];
        std::snprintf(message, sizeof(message), format, args...);
        console_output(color, message);
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

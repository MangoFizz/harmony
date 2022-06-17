// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__HALO_DATA__CONSOLE_HPP
#define HARMONY__HALO_DATA__CONSOLE_HPP

#include <cstdio>
#include "color.hpp"

namespace Harmony::HaloData {
    /**
     * Display a message of a color
     * @param color   Color to use in the message
     * @param message Message to use
     */
    void console_output_raw(const ColorARGB &color, const char *message) noexcept;
}

#endif

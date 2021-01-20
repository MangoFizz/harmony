// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_WINDOW_HPP
#define HARMONY_HALO_WINDOW_HPP

#include <windows.h>

namespace Harmony::HaloData {
    /**
     * Get the window handle
     */
    HWND *get_window_handle() noexcept;
}

#endif
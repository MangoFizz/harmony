// SPDX-License-Identifier: GPL-3.0-only

#include <windows.h>
#include "../halo_data/window.hpp"
#include "message_box.hpp"

namespace Harmony {
    void message_box(const char *message) noexcept {
        HWND window_handle;
        try {
            window_handle = HaloData::WindowGlobals::get().hWnd;
        }
        catch(...) {
            window_handle = nullptr;
        }
        MessageBoxA(window_handle, message, "Harmony", MB_OK);
    }
}
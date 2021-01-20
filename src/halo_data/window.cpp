// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "window.hpp"

namespace Harmony::HaloData {
    HWND *get_window_handle() noexcept {
        static auto &window_handle_sig = get_harmony().get_signature("window_handle");
        static auto *window_handle = *reinterpret_cast<HWND **>(window_handle_sig.get_data());

        return window_handle;
    }
}
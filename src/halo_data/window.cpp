// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "window.hpp"

namespace Harmony::HaloData {
    WindowGlobals &WindowGlobals::get() {
        if(!Harmony::get().signature_exists("window_globals")) {
            throw std::exception();
        }
        
        static auto &windows_global_sig = Harmony::get().get_signature("window_globals");
        WindowGlobals *window_globals = *reinterpret_cast<WindowGlobals **>(windows_global_sig.get_data());
        return *window_globals;
    }
}
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>
#include <balltze/output.hpp>
#include <balltze/event.hpp>

namespace Harmony {
    using namespace Balltze::Event;

    static EventListenerHandle<TickEvent> firstTickListener;

    static void first_tick(TickEvent const &context) noexcept {
        Balltze::console_printf("Harmony initialized");
        firstTickListener.remove();
    }

    static void initialize_harmony() noexcept {
        firstTickListener = TickEvent::subscribe_const(first_tick, EVENT_PRIORITY_HIGHEST);
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch(fdwReason) {
        case DLL_PROCESS_ATTACH:
            Harmony::initialize_harmony();
            break;

        default:
            break;
    }
    return TRUE;
}

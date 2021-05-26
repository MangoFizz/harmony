// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "d3d9_reset.hpp"

namespace Harmony {
    static std::vector<Event<ResetEventFunction>> reset_events;

    extern "C" {
        void on_d3d9_reset_asm();
    }

    void add_d3d9_reset_event(const ResetEventFunction function, EventPriority priority) {
        // Remove if exists
        remove_d3d9_reset_event(function);

        // Add the event
        reset_events.emplace_back(Event<ResetEventFunction> { function, priority });
    }

    void remove_d3d9_reset_event(const ResetEventFunction function) {
        for(std::size_t i = 0; i < reset_events.size(); i++) {
            if(reset_events[i].function == function) {
                reset_events.erase(reset_events.begin() + i);
                return;
            }
        }
    }

    extern "C" void do_d3d9_reset_event(LPDIRECT3DDEVICE9 device, D3DPRESENT_PARAMETERS *present) {
        call_in_order(reset_events, device, present);
    }

    void enable_d3d9_reset_hook() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        static auto &d3d9_call_reset_sig = get_harmony().get_signature("d3d9_call_reset");
        
        // Write hacks
        static Codecave d3d9_reset_cave;
        d3d9_reset_cave.write_basic_cave(d3d9_call_reset_sig.get_data(), reinterpret_cast<void *>(on_d3d9_reset_asm), false);

        // Hook D3D9 reset call
        d3d9_reset_cave.hook();
    }
}

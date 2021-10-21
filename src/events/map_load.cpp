// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "map_load.hpp"

namespace Harmony {
    static Memory::Hook on_map_load_hook;
    static std::vector<Event<event_no_args>> events;

    void add_map_load_event(const event_no_args function, EventPriority priority) noexcept {
        // Remove if exists
        remove_map_load_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_map_load_event(event_no_args function) noexcept {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    static void do_map_load_event() noexcept {
        call_in_order(events);
    }

    void set_up_map_load_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        static auto &on_map_load_sig = Harmony::get().get_signature("on_map_load");
        
        // Write hacks
        on_map_load_hook.initialize(on_map_load_sig.get_data(), reinterpret_cast<void *>(do_map_load_event));
        on_map_load_hook.hook();
    }
}

// SPDX-License-Identifier: GPL-3.0-only

#include <vector>
#include <cstddef>
#include "../memory/codecave.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "tick.hpp"

namespace Harmony {
    static std::vector<Event<event_no_args>> tick_events;

    void add_tick_event(event_no_args event_function, EventPriority priority) {
        for(std::size_t i = 0; i < tick_events.size(); i++) {
            if(tick_events[i].function == event_function) {
                return;
            }
        }
        tick_events.emplace_back(event_function, priority);
    }

    void remove_tick_event(event_no_args event_function) {
        for(std::size_t i = 0; i < tick_events.size(); i++) {
            if(tick_events[i].function == event_function) {
                tick_events.erase(tick_events.begin() + i);
                return;
            }
        }
    }

    static void on_tick() noexcept {
        call_in_order(tick_events);
    }

    void enable_tick_event() {
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        static auto &on_tick_sig = get_harmony().get_signature("on_tick");
        
        // Write hacks
        static Codecave on_tick_cave;
        on_tick_cave.write_basic_codecave(on_tick_sig.get_data(), reinterpret_cast<void *>(on_tick));

        // Hook multiplayer event call
        on_tick_cave.hook();
    }
}

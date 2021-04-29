// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "multiplayer_event.hpp"

namespace Harmony {
    static Codecave on_multiplayer_event_cave;
    static std::vector<Event<MultiplayerEventFunction>> multiplayer_events;

    void add_multiplayer_event(MultiplayerEventFunction function, EventPriority priority) {
        // Remove if exists
        remove_multiplayer_event(function);

        // Add the event
        multiplayer_events.emplace_back(Event<MultiplayerEventFunction> { function, priority });
    }

    void remove_multiplayer_event(MultiplayerEventFunction function) {
        for(std::size_t i = 0; i < multiplayer_events.size(); i++) {
            if(multiplayer_events[i].function == function) {
                multiplayer_events.erase(multiplayer_events.begin() + i);
                return;
            }
        }
    }

    extern "C" void on_multiplayer_event_asm();
        
    extern "C" void do_on_multiplayer_event(std::uint32_t event, std::uint32_t killer, std::uint32_t victim, std::uint32_t local_player) {
        call_in_order(multiplayer_events, static_cast<HaloData::MultiplayerEvent>(event), local_player, killer, victim);
    }

    void enable_multiplayer_event_hook() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        static auto &on_multiplayer_event_sig = get_harmony().get_signature("on_multiplayer_event");
        
        // Write hacks
        on_multiplayer_event_cave.write_basic_codecave(on_multiplayer_event_sig.get_data(), reinterpret_cast<void *>(on_multiplayer_event_asm), false);

        // Hook multiplayer event call
        on_multiplayer_event_cave.hook();
    }
}

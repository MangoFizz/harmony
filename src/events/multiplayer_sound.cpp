// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "multiplayer_sound.hpp"

namespace Harmony {
    static Codecave on_multiplayer_sound_cave;
    static std::vector<Event<MultiplayerSoundEventFunction>> multiplayer_sound_events;

    extern "C" {
        void on_multiplayer_sound_asm();
    }

    void add_multiplayer_sound_event(MultiplayerSoundEventFunction function, EventPriority priority) {
        // Remove if exists
        remove_multiplayer_sound_event(function);

        // Add the event
        multiplayer_sound_events.emplace_back(Event<MultiplayerSoundEventFunction> { function, priority });
    }

    void remove_multiplayer_sound_event(MultiplayerSoundEventFunction function) {
        for(std::size_t i = 0; i < multiplayer_sound_events.size(); i++) {
            if(multiplayer_sound_events[i].function == function) {
                multiplayer_sound_events.erase(multiplayer_sound_events.begin() + i);
                return;
            }
        }
    }

    extern "C" void do_on_multiplayer_sound(HaloData::MultiplayerSound sound) {
        bool allow = true;
        call_in_order_allow(multiplayer_sound_events, allow, sound);
        on_multiplayer_sound_cave.execute_original_code(allow);
    }

    void set_up_multiplayer_sounds_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        static auto &on_multiplayer_sound_sig = get_harmony().get_signature("on_multiplayer_sound");
        
        // Write hacks
        on_multiplayer_sound_cave.write_basic_cave(on_multiplayer_sound_sig.get_data(), reinterpret_cast<void *>(on_multiplayer_sound_asm), false);

        // Hook multiplayer event call
        on_multiplayer_sound_cave.hook();
    }
}

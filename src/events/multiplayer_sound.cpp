// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "multiplayer_sound.hpp"

namespace Harmony {
    static Memory::FunctionOverride on_multiplayer_sound_hook;
    static std::vector<Event<MultiplayerSoundEventFunction>> multiplayer_sound_events;

    extern "C" {
        void multiplayer_sound_override();
        const void *multiplayer_sound_fn_return;
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

    extern "C" bool do_on_multiplayer_sound(HaloData::MultiplayerSound sound) {
        bool allow = true;
        call_in_order_allow(multiplayer_sound_events, allow, sound);
        return allow;
    }

    void set_up_multiplayer_sounds_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        static auto &on_multiplayer_sound_sig = Harmony::get().get_signature("on_multiplayer_sound");
        
        // Write hacks
        on_multiplayer_sound_hook.initialize(on_multiplayer_sound_sig.get_data(), reinterpret_cast<void *>(multiplayer_sound_override), &multiplayer_sound_fn_return);
        on_multiplayer_sound_hook.hook();
    }
}

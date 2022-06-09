// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "multiplayer_hit_sound.hpp"

#include "../messaging/console_output.hpp"

namespace Harmony {
    static Memory::SwitchHook hook;
    static std::vector<Event<MultiplayerHitSoundEvent_t>> events;

    extern "C" {
        void multiplayer_hit_sound_event_asm();
        bool *allow_multiplayer_hit_sound = nullptr;

        void do_multiplayer_hit_sound_events() noexcept {
            static Signature sound_volume_sig = Harmony::get().get_signature("multiplayer_hit_sound_volume");
            static float *sound_volume = *reinterpret_cast<float **>(sound_volume_sig.get_data());

            bool allow = true;
            call_in_order_allow(events, allow, *sound_volume);
            hook.execute_original_code(allow);
        }
    }

    void add_multiplayer_hit_sound_event(MultiplayerHitSoundEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_multiplayer_hit_sound_event(function);

        // Add the event
        events.emplace_back(Event<MultiplayerHitSoundEvent_t> { function, priority });
    }

    void remove_multiplayer_hit_sound_event(MultiplayerHitSoundEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_multiplayer_hit_sound_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signatures
        static auto &multiplayer_hit_sound_call_sig = Harmony::get().get_signature("multiplayer_hit_sound_call");
        static auto &multiplayer_hit_sound_check_sig = Harmony::get().get_signature("multiplayer_hit_sound_volume_check");
        
        // Write hacks
        hook.initialize(multiplayer_hit_sound_call_sig.get_data(), reinterpret_cast<void *>(multiplayer_hit_sound_event_asm), false);
        hook.hook();

        // Remove volume check
        Memory::fill_with_nops(multiplayer_hit_sound_check_sig.get_data(), 2);

        // Set allow flag pointer
        allow_multiplayer_hit_sound = &hook.execute_original_code();
    }
}

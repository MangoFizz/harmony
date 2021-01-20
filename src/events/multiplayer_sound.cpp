// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "multiplayer_sound.hpp"

namespace Harmony {
    static Codecave on_multiplayer_sound_hook;
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
        on_multiplayer_sound_hook.skip_og_code = !allow;
    }

    void enable_multiplayer_sounds_hook() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        static auto &on_multiplayer_sound_sig = get_harmony().get_signature("on_multiplayer_sound");

        // Instruction
        auto *instruction = on_multiplayer_sound_sig.get_data();
        std::size_t instruction_size = 0x5;

        std::size_t offset = 0;

        // Write the assembly function call
        on_multiplayer_sound_hook.write_function_call(offset, reinterpret_cast<void *>(on_multiplayer_sound_asm), false);

        // Copy original instruction
        on_multiplayer_sound_hook.copy_intruction(offset, instruction, instruction_size);
        
        // Check if the skip flag is set
        on_multiplayer_sound_hook.write_skip_code_check(offset, 5);

        // Return to the original function
        on_multiplayer_sound_hook.write_exit(offset, instruction + instruction_size);

        // If the skip flag is set, then do a return
        on_multiplayer_sound_hook.data[offset] = 0xC3;
        offset += 1;

        // Update codecave data size
        on_multiplayer_sound_hook.data_size = offset;

        // Hook it!
        on_multiplayer_sound_hook.hook(reinterpret_cast<void *>(instruction));
    }
}

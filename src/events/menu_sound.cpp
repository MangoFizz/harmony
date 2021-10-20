// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "menu_sound.hpp"

namespace Harmony {
    static Codecave menu_sound_cave;
    static std::vector<Event<MenuSoundEvent_t>> events;

    extern "C" {
        void menu_sound();

        bool on_menu_sound(HaloData::TagID button_id, HaloData::MenuSound sound) {
            bool allow = true;
            call_in_order_allow(events, allow, button_id, sound);
            return allow;
        }
    }

    void add_menu_sound_event(MenuSoundEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_menu_sound_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_menu_sound_event(MenuSoundEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_menu_sound_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        auto &menu_sound_play_function_sig = Harmony::get().get_signature("menu_sound_play_function");
        
        // Write the hacks
        menu_sound_cave.write_function_call(menu_sound_play_function_sig.get_data(), nullptr, reinterpret_cast<void *>(menu_sound), false);

        // Hook it
        menu_sound_cave.hook();
    }
}

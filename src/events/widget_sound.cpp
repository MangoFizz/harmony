// SPDX-License-Identifier: GPL-3.0-only

#include "../messaging/message_box.hpp"
#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "widget_sound.hpp"

namespace Harmony {
    static Memory::FunctionOverride widget_sound_hook;
    static std::vector<Event<WidgetSoundEvent_t>> events;

    extern "C" {
        void play_widget_sound_override();
        const void *play_widget_sound_fn_return;

        bool call_widget_sound_events(HaloData::WidgetNavigationSound sound) {
            bool allow = true;
            call_in_order_allow(events, allow, sound);
            return allow;
        }
    }

    void add_widget_sound_event(WidgetSoundEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_widget_sound_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_widget_sound_event(WidgetSoundEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_widget_sound_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        auto &widget_sound_play_function_sig = Harmony::get().get_signature("widget_sound_play_function");
        
        try {
            // Write the hacks
            widget_sound_hook.initialize(widget_sound_play_function_sig.get_data(), reinterpret_cast<void *>(play_widget_sound_override), &play_widget_sound_fn_return);
            widget_sound_hook.hook();
        }
        catch(std::runtime_error &e) {
            message_box("Failed to set up widget sound event.");
            std::terminate();
        }
    }
}

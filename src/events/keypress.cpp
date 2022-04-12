// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../messaging/message_box.hpp"
#include "../harmony.hpp"
#include "keypress.hpp"

namespace Harmony {
    static Memory::Hook on_keypress_hook;
    static std::vector<Event<KeypressEvent_t>> events;

    extern "C" {
        void call_keypress_events_asm();

        void call_keypress_events(HaloData::InputGlobals::BufferedKey key) noexcept {
            call_in_order(events, key.modifiers, key.character, key.keycode);
        }
    }

    void add_keypress_event(const KeypressEvent_t function, EventPriority priority) noexcept {
        // Remove if exists
        remove_keypress_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_keypress_event(KeypressEvent_t function) noexcept {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_keypress_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        static auto &on_keypress_sig = Harmony::get().get_signature("keypress_event");

        // Write hacks
        on_keypress_hook.initialize(on_keypress_sig.get_data(), reinterpret_cast<void *>(call_keypress_events_asm));
        on_keypress_hook.hook();
    }
}

// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "menu_accept.hpp"

namespace Harmony {
    static Codecave menu_accept_event_cave;
    static std::vector<Event<MenuAcceptEvent_t>> events;

    extern "C" {
        void menu_accept();
        void *menu_accept_return = nullptr;
    }

    void add_menu_accept_event(MenuAcceptEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_menu_accept_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_menu_accept_event(MenuAcceptEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    extern "C" bool on_menu_accept(HaloData::TagID *tag_id) {
        bool allow = true;
        call_in_order_allow(events, allow, tag_id);
        return allow;
    }

    void set_up_menu_accept_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        auto &menu_button_accept_event_check_sig = get_harmony().get_signature("menu_accept_event_check");
        
        // Write the hacks
        menu_accept_event_cave.write_function_call(menu_button_accept_event_check_sig.get_data(), nullptr, reinterpret_cast<void *>(menu_accept), false);

        // Hook it
        menu_accept_event_cave.hook();
    }
}

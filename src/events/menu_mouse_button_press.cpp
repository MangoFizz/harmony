// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "menu_mouse_button_press.hpp"

namespace Harmony {
    static Codecave on_menu_mouse_button_press_cave;
    static std::vector<Event<MenuMouseButtonPressEvent_t>> events;

    extern "C" {
        void menu_mouse_button_press();

        bool on_menu_button_press(HaloData::TagID tag_id, HaloData::MenuMouseButtonCode button) {
            bool allow = true;
            call_in_order_allow(events, allow, tag_id, button);
            return allow;
        }
    }

    void add_menu_mouse_button_press_event(MenuMouseButtonPressEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_menu_mouse_button_press_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_menu_mouse_button_press_event(MenuMouseButtonPressEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_menu_mouse_button_press_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        auto &on_menu_button_press_sig = get_harmony().get_signature("menu_mouse_pressed_button_check");
        auto *on_menu_button_press_address = on_menu_button_press_sig.get_data();
        
        // Write the hacks
        Memory::fill_with_nops(reinterpret_cast<void *>(on_menu_button_press_sig.get_data()), 0x1E); // Remove original code
        on_menu_mouse_button_press_cave.write_function_call(on_menu_button_press_sig.get_data(), reinterpret_cast<void *>(menu_mouse_button_press), nullptr, false);

        // Hook it
        on_menu_mouse_button_press_cave.hook();
    }
}

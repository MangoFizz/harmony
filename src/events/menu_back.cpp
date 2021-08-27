// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "menu_back.hpp"

namespace Harmony {
    static Codecave menu_back_button_press_cave;
    static Codecave menu_back_call_escape_key_cave;
    static Codecave menu_back_call_multiplayer_lobby_cave;
    static Codecave menu_back_call_controls_menu_cave;
    static std::vector<Event<MenuBackEvent_t>> events;

    void add_menu_back_event(MenuBackEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_menu_back_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_menu_back_event(MenuBackEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    static void on_menu_back() {
        bool allow = true;
        call_in_order_allow(events, allow);
        menu_back_button_press_cave.execute_original_code(allow);
        menu_back_call_escape_key_cave.execute_original_code(allow);
        menu_back_call_multiplayer_lobby_cave.execute_original_code(allow);
        menu_back_call_controls_menu_cave.execute_original_code(allow);
    }

    void set_up_menu_back_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        auto &menu_back_call_button_press_sig = get_harmony().get_signature("menu_back_call_button_press");
        auto &menu_back_call_escape_key_sig = get_harmony().get_signature("menu_back_call_escape_key");
        auto &menu_back_call_multiplayer_lobby_sig = get_harmony().get_signature("menu_back_call_multiplayer_lobby");
        auto &menu_back_call_controls_menu_sig = get_harmony().get_signature("menu_back_call_controls_menu");
        
        // Write the hacks
        menu_back_button_press_cave.write_basic_cave(menu_back_call_button_press_sig.get_data(), reinterpret_cast<void *>(on_menu_back));
        menu_back_call_escape_key_cave.write_basic_cave(menu_back_call_escape_key_sig.get_data(), reinterpret_cast<void *>(on_menu_back));
        menu_back_call_multiplayer_lobby_cave.write_basic_cave(menu_back_call_multiplayer_lobby_sig.get_data(), reinterpret_cast<void *>(on_menu_back));
        menu_back_call_controls_menu_cave.write_basic_cave(menu_back_call_controls_menu_sig.get_data(), reinterpret_cast<void *>(on_menu_back));

        // Hook it
        menu_back_button_press_cave.hook();
        menu_back_call_escape_key_cave.hook();
        menu_back_call_multiplayer_lobby_cave.hook();
        menu_back_call_controls_menu_cave.hook();
    }
}

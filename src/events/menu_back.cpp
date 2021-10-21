// SPDX-License-Identifier: GPL-3.0-only

#include "../messaging/message_box.hpp"
#include "../memory/hook.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "menu_back.hpp"

namespace Harmony {
    static Memory::SwitchHook menu_back_button_press_hook;
    static Memory::SwitchHook menu_back_call_escape_key_hook;
    static Memory::SwitchHook menu_back_call_multiplayer_lobby_hook;
    static Memory::SwitchHook menu_back_call_controls_menu_hook;
    static std::vector<Event<MenuBackEvent_t>> events;

    extern "C" {
        void menu_back_event();

        void on_menu_back(HaloData::TagID menu_id) {
            bool allow = true;
            call_in_order_allow(events, allow, menu_id);
            menu_back_button_press_hook.execute_original_code(allow);
            menu_back_call_escape_key_hook.execute_original_code(allow);
            menu_back_call_multiplayer_lobby_hook.execute_original_code(allow);
            menu_back_call_controls_menu_hook.execute_original_code(allow);
        }
    }

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

    void set_up_menu_back_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Write the hacks
        auto &menu_back_call_button_press_sig = Harmony::get().get_signature("menu_back_call_button_press");
        menu_back_button_press_hook.initialize(menu_back_call_button_press_sig.get_data(), reinterpret_cast<void *>(menu_back_event));
        menu_back_button_press_hook.hook();
        
        auto &menu_back_call_escape_key_sig = Harmony::get().get_signature("menu_back_call_escape_key");
        menu_back_call_escape_key_hook.initialize(menu_back_call_escape_key_sig.get_data(), reinterpret_cast<void *>(menu_back_event));
        menu_back_call_escape_key_hook.hook();
        
        auto &menu_back_call_multiplayer_lobby_sig = Harmony::get().get_signature("menu_back_call_multiplayer_lobby");
        menu_back_call_multiplayer_lobby_hook.initialize(menu_back_call_multiplayer_lobby_sig.get_data(), reinterpret_cast<void *>(menu_back_event));
        menu_back_call_multiplayer_lobby_hook.hook();
        
        auto &menu_back_call_controls_menu_sig = Harmony::get().get_signature("menu_back_call_controls_menu");
        menu_back_call_controls_menu_hook.initialize(menu_back_call_controls_menu_sig.get_data(), reinterpret_cast<void *>(menu_back_event));
        menu_back_call_controls_menu_hook.hook();
    }
}

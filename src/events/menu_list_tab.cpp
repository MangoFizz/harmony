// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "menu_list_tab.hpp"

namespace Harmony {
    static Memory::SwitchHook menu_tab_list_items_next_vertical_hook;
    static Memory::SwitchHook menu_tab_list_items_next_horizontal_hook;
    static Memory::SwitchHook menu_tab_list_items_previous_vertical_hook;
    static Memory::SwitchHook menu_tab_list_items_previous_horizontal_hook;
    static Memory::SwitchHook menu_tab_children_next_vertical_hook;
    static Memory::SwitchHook menu_tab_children_next_horizontal_hook;
    static Memory::SwitchHook menu_tab_children_previous_hook;
    static std::vector<Event<MenuListTabEvent_t>> events;

    extern "C" {
        void menu_list_tab();

        void on_menu_list_tab(HaloData::MenuNavigationKeyCode key, HaloData::TagID list, HaloData::TagID button) {
            bool allow = true;
            call_in_order_allow(events, allow, key, list, button);
            menu_tab_list_items_next_vertical_hook.execute_original_code(allow);
            menu_tab_list_items_next_horizontal_hook.execute_original_code(allow);
            menu_tab_list_items_previous_vertical_hook.execute_original_code(allow);
            menu_tab_list_items_previous_horizontal_hook.execute_original_code(allow);
            menu_tab_children_next_vertical_hook.execute_original_code(allow);
            menu_tab_children_next_horizontal_hook.execute_original_code(allow);
            menu_tab_children_previous_hook.execute_original_code(allow);
        }
    }

    void add_menu_list_tab_event(MenuListTabEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_menu_list_tab_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_menu_list_tab_event(MenuListTabEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }
    void set_up_menu_list_tab_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Write a ton of hacks
        auto &menu_tab_list_items_next_vertical_sig = Harmony::get().get_signature("menu_tab_list_items_next_vertical_call");
        menu_tab_list_items_next_vertical_hook.initialize(menu_tab_list_items_next_vertical_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_list_items_next_vertical_hook.hook();
        
        auto &menu_tab_list_items_next_horizontal_sig = Harmony::get().get_signature("menu_tab_list_items_next_horizontal_call");
        menu_tab_list_items_next_horizontal_hook.initialize(menu_tab_list_items_next_horizontal_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_list_items_next_horizontal_hook.hook();
        
        auto &menu_tab_list_items_previous_vertical_sig = Harmony::get().get_signature("menu_tab_list_items_previous_vertical_call");
        menu_tab_list_items_previous_vertical_hook.initialize(menu_tab_list_items_previous_vertical_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_list_items_previous_vertical_hook.hook();
        
        auto &menu_tab_list_items_previous_horizontal_sig = Harmony::get().get_signature("menu_tab_list_items_previous_horizontal_call");
        menu_tab_list_items_previous_horizontal_hook.initialize(menu_tab_list_items_previous_horizontal_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_list_items_previous_horizontal_hook.hook();
        
        auto &menu_tab_children_next_vertical_sig = Harmony::get().get_signature("menu_tab_children_next_vertical_call");
        menu_tab_children_next_vertical_hook.initialize(menu_tab_children_next_vertical_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_children_next_vertical_hook.hook();
        
        auto &menu_tab_children_next_horizontal_sig = Harmony::get().get_signature("menu_tab_children_next_horizontal_call");
        menu_tab_children_next_horizontal_hook.initialize(menu_tab_children_next_horizontal_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_children_next_horizontal_hook.hook();
        
        auto &menu_tab_children_previous_sig = Harmony::get().get_signature("menu_tab_children_previous_call");
        menu_tab_children_previous_hook.initialize(menu_tab_children_previous_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_children_previous_hook.hook();
    }
}

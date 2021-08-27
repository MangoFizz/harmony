// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "menu_list_tab.hpp"

namespace Harmony {
    static Codecave menu_tab_list_items_next_vertical_cave;
    static Codecave menu_tab_list_items_next_horizontal_cave;
    static Codecave menu_tab_list_items_previous_vertical_cave;
    static Codecave menu_tab_list_items_previous_horizontal_cave;
    static Codecave menu_tab_children_next_vertical_cave;
    static Codecave menu_tab_children_next_horizontal_cave;
    static Codecave menu_tab_children_previous_cave;
    static std::vector<Event<MenuListTabEvent_t>> events;

    extern "C" {
        void menu_list_tab();

        void on_menu_list_tab(HaloData::MenuNavigationKeyCode key, HaloData::TagID list, HaloData::TagID button) {
            bool allow = true;
            call_in_order_allow(events, allow, key, list, button);
            menu_tab_list_items_next_vertical_cave.execute_original_code(allow);
            menu_tab_list_items_next_horizontal_cave.execute_original_code(allow);
            menu_tab_list_items_previous_vertical_cave.execute_original_code(allow);
            menu_tab_list_items_previous_horizontal_cave.execute_original_code(allow);
            menu_tab_children_next_vertical_cave.execute_original_code(allow);
            menu_tab_children_next_horizontal_cave.execute_original_code(allow);
            menu_tab_children_previous_cave.execute_original_code(allow);
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

        // Get signatures
        auto &menu_tab_list_items_next_vertical_sig = get_harmony().get_signature("menu_tab_list_items_next_vertical");
        auto &menu_tab_list_items_next_horizontal_sig = get_harmony().get_signature("menu_tab_list_items_next_horizontal");
        auto &menu_tab_list_items_previous_vertical_sig = get_harmony().get_signature("menu_tab_list_items_previous_vertical");
        auto &menu_tab_list_items_previous_horizontal_sig = get_harmony().get_signature("menu_tab_list_items_previous_horizontal");
        auto &menu_tab_children_next_vertical_sig = get_harmony().get_signature("menu_tab_children_next_vertical");
        auto &menu_tab_children_next_horizontal_sig = get_harmony().get_signature("menu_tab_children_next_horizontal");
        auto &menu_tab_children_previous_sig = get_harmony().get_signature("menu_tab_children_previous");
        
        // Write a ton of hacks
        menu_tab_list_items_next_vertical_cave.write_basic_cave(menu_tab_list_items_next_vertical_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_list_items_next_horizontal_cave.write_basic_cave(menu_tab_list_items_next_horizontal_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_list_items_previous_vertical_cave.write_basic_cave(menu_tab_list_items_previous_vertical_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_list_items_previous_horizontal_cave.write_basic_cave(menu_tab_list_items_previous_horizontal_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_children_next_vertical_cave.write_basic_cave(menu_tab_children_next_vertical_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_children_next_horizontal_cave.write_basic_cave(menu_tab_children_next_horizontal_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);
        menu_tab_children_previous_cave.write_basic_cave(menu_tab_children_previous_sig.get_data(), reinterpret_cast<void *>(menu_list_tab), false);

        // Hook it
        menu_tab_list_items_next_vertical_cave.hook();
        menu_tab_list_items_next_horizontal_cave.hook();
        menu_tab_list_items_previous_vertical_cave.hook();
        menu_tab_list_items_previous_horizontal_cave.hook();
        menu_tab_children_next_vertical_cave.hook();
        menu_tab_children_next_horizontal_cave.hook();
        menu_tab_children_previous_cave.hook();
    }
}

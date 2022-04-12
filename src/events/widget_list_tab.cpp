// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "widget_list_tab.hpp"

namespace Harmony {
    static std::vector<std::unique_ptr<Memory::SwitchHook>> widget_list_tab_hooks;
    static std::vector<Event<WidgetListTabEvent_t>> events;

    extern "C" {
        void call_widget_list_tab_events_asm();

        void call_widget_list_tab_events(HaloData::GamepadButtonWidgetEvent::GamepadButton button, HaloData::WidgetInstance *list_widget) {
            bool allow = true;
            auto *pressed_button = list_widget->focused_child;
            call_in_order_allow(events, allow, button, list_widget, pressed_button);
            
            for(auto &hook : widget_list_tab_hooks) {
                hook->execute_original_code(allow);
            }
        }
    }

    void add_widget_list_tab_event(WidgetListTabEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_widget_list_tab_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_widget_list_tab_event(WidgetListTabEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }
    void set_up_widget_list_tab_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;
        
        auto *hook_function_ptr = reinterpret_cast<void *>(call_widget_list_tab_events_asm);

        #define HOOK_WIDGET_LIST_TAB(sig) { \
            auto &sig = Harmony::get().get_signature(#sig); \
            auto &hook_sig = widget_list_tab_hooks.emplace_back(std::make_unique<Memory::SwitchHook>(sig.get_data(), hook_function_ptr, false)); \
            hook_sig->hook(); \
        }

        // Write a ton of hacks
        HOOK_WIDGET_LIST_TAB(widget_tab_list_items_next_vertical_call);
        HOOK_WIDGET_LIST_TAB(widget_tab_list_items_next_horizontal_call);
        HOOK_WIDGET_LIST_TAB(widget_tab_list_items_previous_vertical_call);
        HOOK_WIDGET_LIST_TAB(widget_tab_list_items_previous_horizontal_call);
        HOOK_WIDGET_LIST_TAB(widget_tab_children_next_vertical_call);
        HOOK_WIDGET_LIST_TAB(widget_tab_children_next_horizontal_call);
        HOOK_WIDGET_LIST_TAB(widget_tab_children_previous_call);

        #undef HOOK_WIDGET_LIST_TAB
    }
}

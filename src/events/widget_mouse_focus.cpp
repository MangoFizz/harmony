// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "widget_mouse_focus.hpp"

namespace Harmony {
    static Memory::SwitchHook widget_mouse_focus_hook;
    static std::vector<Event<WidgetMouseFocusEvent_t>> events;

    extern "C" {
        void handle_widget_mouse_focus_asm();

        void call_widget_mouse_focus_events(HaloData::WidgetInstance *focused_widget) {
            bool allow = true;
            call_in_order_allow(events, allow, focused_widget);
            widget_mouse_focus_hook.execute_original_code(allow);
        }
    }

    void add_widget_mouse_focus_event(WidgetMouseFocusEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_widget_mouse_focus_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_widget_mouse_focus_event(WidgetMouseFocusEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_widget_mouse_focus_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        auto &on_widget_focus_sig = Harmony::get().get_signature("widget_mouse_focus_update");
        
        // Write the hacks
        widget_mouse_focus_hook.initialize(on_widget_focus_sig.get_data(), reinterpret_cast<void *>(handle_widget_mouse_focus_asm), true);
        widget_mouse_focus_hook.hook();
    }
}

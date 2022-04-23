// SPDX-License-Identifier: GPL-3.0-only

#include "../messaging/message_box.hpp"
#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "widget_close.hpp"

namespace Harmony {
    static Memory::FunctionOverride widget_close_function_hook;
    static std::vector<Event<WidgetCloseEvent_t>> events;

    extern "C" {
        void close_widget_override();
        const void *close_widget_fn_return;

        bool call_widget_close_events(HaloData::WidgetInstance *current_root_widget) {
            bool allow = true;
            call_in_order_allow(events, allow, current_root_widget);
            return allow;
        }
    }

    void add_widget_close_event(WidgetCloseEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_widget_close_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_widget_close_event(WidgetCloseEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_widget_close_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Write the hacks
        auto &widget_close_function_sig = Harmony::get().get_signature("widget_close_function");

        try {
            widget_close_function_hook.initialize(widget_close_function_sig.get_data(), reinterpret_cast<void *>(close_widget_override), &close_widget_fn_return);
            widget_close_function_hook.hook();
        }
        catch(std::runtime_error &e) {
            message_box("Failed to set up widget close event.");
            std::terminate();
        }
    }
}

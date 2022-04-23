// SPDX-License-Identifier: GPL-3.0-only

#include "../messaging/message_box.hpp"
#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "widget_accept.hpp"

namespace Harmony {
    static Memory::Hook widget_accept_event_check_hook;
    static std::vector<Event<WidgetAcceptEvent_t>> events;

    extern "C" {
        void call_widget_accept_events_asm();

        bool call_widget_accept_events(HaloData::WidgetInstance *pressed_widget) {
            bool allow = true;
            call_in_order_allow(events, allow, pressed_widget);
            return allow;
        }
    }

    void add_widget_accept_event(WidgetAcceptEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_widget_accept_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_widget_accept_event(WidgetAcceptEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_widget_accept_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        auto &widget_accept_event_check_sig = Harmony::get().get_signature("widget_accept_event_check");
        
        try {
            // Write the hacks
            widget_accept_event_check_hook.initialize(widget_accept_event_check_sig.get_data(), nullptr, reinterpret_cast<void *>(call_widget_accept_events_asm), false);
            widget_accept_event_check_hook.hook();
        }
        catch(std::runtime_error &e) {
            message_box("Failed to set up widget accept event.");
            std::terminate();
        }
    }
}

// SPDX-License-Identifier: GPL-3.0-only

#include <stdexcept>
#include "../messaging/message_box.hpp"
#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "widget_open.hpp"

namespace Harmony {
    static Memory::Hook widget_open_hook;
    static std::vector<Event<WidgetOpenEvent_t>> events;

    extern "C" {
        void create_widget_return_hook_asm();

        void call_widget_open_events(HaloData::WidgetInstance *widget) {
            auto &widget_globals = HaloData::WidgetGlobals::get();

            /**
             * When a widget is opened using the create event, this function 
             * will receive the opened widget before the widget that triggered 
             * the event, so we just have to ignore it.
             */
            if(widget == widget_globals.root_widget) {
                call_in_order(events, widget);
            }
        }
    }

    void add_widget_open_event(WidgetOpenEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_widget_open_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_widget_open_event(WidgetOpenEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_widget_open_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Write the hacks
        auto &widget_create_function_return_sig = Harmony::get().get_signature("widget_create_function_return");

        try {
            widget_open_hook.initialize(widget_create_function_return_sig.get_data(), nullptr, reinterpret_cast<void *>(create_widget_return_hook_asm), false);
            widget_open_hook.hook();
        }
        catch(std::runtime_error &e) {
            message_box("Failed to set up widget open event.");
            std::terminate();
        }
    }
}

// SPDX-License-Identifier: GPL-3.0-only

#include "../messaging/message_box.hpp"
#include "../memory/hook.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "widget_mouse_button_press.hpp"

namespace Harmony {
    static Memory::Hook widget_mouse_button_press_hook;
    static std::vector<Event<WidgetMouseButtonPressEvent_t>> events;

    extern "C" {
        void handle_widget_mouse_button_press_asm();

        bool call_widget_mouse_button_press_events(HaloData::WidgetInstance *pressed_widget, HaloData::MouseButtonWidgetEvent::MouseButton button) {
            bool allow = true;
            call_in_order_allow(events, allow, pressed_widget, button);
            return allow;
        }
    }

    void add_widget_mouse_button_press_event(WidgetMouseButtonPressEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_widget_mouse_button_press_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_widget_mouse_button_press_event(WidgetMouseButtonPressEvent_t function) {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_widget_mouse_button_press_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        auto &on_widget_button_press_sig = Harmony::get().get_signature("widget_mouse_pressed_button_check");
        auto *on_widget_button_press_address = on_widget_button_press_sig.get_data();
        
        
        try {
            // Write the hacks
            Memory::fill_with_nops(reinterpret_cast<void *>(on_widget_button_press_sig.get_data()), 0x1E); // Remove original memes, we will take care about it
            widget_mouse_button_press_hook.initialize(on_widget_button_press_sig.get_data(), reinterpret_cast<void *>(handle_widget_mouse_button_press_asm), nullptr, false);
            widget_mouse_button_press_hook.hook();
        }
        catch(std::runtime_error &e) {
            message_box("Failed to set up widget mouse button press event.");
            std::terminate();
        }
    }
}

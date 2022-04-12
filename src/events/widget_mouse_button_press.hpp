// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_WIDGET_BUTTON_PRESS_HPP
#define HARMONY_EVENT_WIDGET_BUTTON_PRESS_HPP

#include "../halo_data/widget.hpp"
#include "../halo_data/tag.hpp"
#include "event.hpp"

namespace Harmony {
    using WidgetMouseButtonPressEvent_t = bool (*)(HaloData::WidgetInstance *, HaloData::MouseButtonWidgetEvent::MouseButton);

    /**
     * Add a widget mouse button press event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_widget_mouse_button_press_event(WidgetMouseButtonPressEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a widget mouse button press event
     * @param function  Function of the event to be removed
     */
    void remove_widget_mouse_button_press_event(WidgetMouseButtonPressEvent_t event_function);

    /**
     * Set up widget mouse button press event
     */
    void set_up_widget_mouse_button_press_event();
}

#endif

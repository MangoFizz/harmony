// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_WIDGET_MOUSE_FOCUS_HPP
#define HARMONY_EVENT_WIDGET_MOUSE_FOCUS_HPP

#include "../halo_data/widget.hpp"
#include "../halo_data/tag.hpp"
#include "event.hpp"

namespace Harmony {
    using WidgetMouseFocusEvent_t = bool (*)(HaloData::WidgetInstance *);

    /**
     * Add a widget mouse focus event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_widget_mouse_focus_event(WidgetMouseFocusEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a widget mouse focus event
     * @param function  Function of the event to be removed
     */
    void remove_widget_mouse_focus_event(WidgetMouseFocusEvent_t event_function);

    /**
     * Set up widget mouse focus event
     */
    void set_up_widget_mouse_focus_event();
}

#endif

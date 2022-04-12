// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_WIDGET_CLOSE_HPP
#define HARMONY_EVENT_WIDGET_CLOSE_HPP

#include "../halo_data/widget.hpp"
#include "event.hpp"

namespace Harmony {
    using WidgetCloseEvent_t = bool (*)(HaloData::WidgetInstance *);

    /**
     * Add a widget close event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_widget_close_event(WidgetCloseEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a widget close event
     * @param function  Function of the event to be removed
     */
    void remove_widget_close_event(WidgetCloseEvent_t event_function);

    /**
     * Set up widget close event
     */
    void set_up_widget_close_event();
}

#endif

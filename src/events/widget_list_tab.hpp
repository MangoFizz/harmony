// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_WIDGET_LIST_TAB_HPP
#define HARMONY_EVENT_WIDGET_LIST_TAB_HPP

#include "../halo_data/widget.hpp"
#include "../halo_data/tag.hpp"
#include "event.hpp"

namespace Harmony {
    /**
     * Widget list tab event
     * @param gamepad_button    Pressed gamepad button
     * @param list_widget       Widget list of the pressed widget
     * @param pressed_widget    Pressed widget
     */
    using WidgetListTabEvent_t = bool (*)(HaloData::GamepadButtonWidgetEvent::GamepadButton, HaloData::WidgetInstance *, HaloData::WidgetInstance *);

    /**
     * Add a widget list tab event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_widget_list_tab_event(WidgetListTabEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a widget list tab event
     * @param function  Function of the event to be removed
     */
    void remove_widget_list_tab_event(WidgetListTabEvent_t event_function);

    /**
     * Set up widget list tab
     */
    void set_up_widget_list_tab_event();
}

#endif

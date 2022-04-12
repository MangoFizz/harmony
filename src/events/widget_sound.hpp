// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_MENU_SOUND_HPP
#define HARMONY_EVENT_MENU_SOUND_HPP

#include "../halo_data/widget.hpp"
#include "event.hpp"

namespace Harmony {
    using WidgetSoundEvent_t = bool (*)(HaloData::WidgetNavigationSound);

    /**
     * Add a widget sound event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_widget_sound_event(WidgetSoundEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a widget sound event
     * @param function  Function of the event to be removed
     */
    void remove_widget_sound_event(WidgetSoundEvent_t event_function);

    /**
     * Set up widget sound event
     */
    void set_up_widget_sound_event();
}

#endif

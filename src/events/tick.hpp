// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_TICK_EVENT_HPP
#define HARMONY_TICK_EVENT_HPP

#include "event.hpp"

namespace Harmony {
    /**
     * Add a tick event.
     * @param function  Function to be executed on every game tick
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_tick_event(event_no_args event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a tick event.
     * @param function  Function of the event to be removed
     */
    void remove_tick_event(event_no_args event_function);

    /**
     * Set up tick event
     */
    void enable_tick_event();
}

#endif

// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_KEYPRESS_EVENT_HPP
#define HARMONY_KEYPRESS_EVENT_HPP

#include "../halo_data/input_devices.hpp"
#include "event.hpp"

namespace Harmony {
    using KeypressEvent_t = void (*)(std::uint8_t, wchar_t, std::uint8_t);

    /**
     * Add a keypress event.
     * @param function  Function to be executed on key press
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_keypress_event(KeypressEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT) noexcept;

    /**
     * Remove a keypress event.
     * @param function  Function of the event to be removed
     */
    void remove_keypress_event(KeypressEvent_t event_function) noexcept;

    /**
     * Set up keypress event
     */
    void set_up_keypress_event();
}

#endif

// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_HS_FUNCTION_HPP
#define HARMONY_EVENT_HS_FUNCTION_HPP

#include <cstdint>
#include "../halo_data/script.hpp"
#include "event.hpp"

namespace Harmony {
    using HsFunctionEvent_t = void (*)(const char *script, HaloData::ScriptFunction *function, const std::uint32_t *params);

    /**
     * Add a halo script function event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_hs_function_event(HsFunctionEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a halo script function event
     * @param function  Function of the event to be removed
     */
    void remove_hs_function_event(HsFunctionEvent_t event_function);

    /**
     * Set up halo script function event
     */
    void set_up_hs_function_event();
}

#endif

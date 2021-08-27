// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENTS_MULTIPLAYER_EVENT_HPP
#define HARMONY_EVENTS_MULTIPLAYER_EVENT_HPP

#include "../halo_data/multiplayer_events.hpp"
#include "../halo_data/type.hpp"
#include "event.hpp"

namespace Harmony {
    using MultiplayerEventFunction = bool (*)(HaloData::MultiplayerEvent type, HaloData::PlayerID local, HaloData::PlayerID killer, HaloData::PlayerID victim);

    /**
     * Add a multiplayer event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_multiplayer_event(MultiplayerEventFunction event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a multiplayer event.
     * @param function  Function of the event to be removed
     */
    void remove_multiplayer_event(MultiplayerEventFunction event_function);

    /**
     * Set up multiplayer event
     */
    void set_up_multiplayer_event();
}

#endif

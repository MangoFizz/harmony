#ifndef HARMONY_EVENTS_MULTIPLAYER_HIT_SOUND_EVENT_HPP
#define HARMONY_EVENTS_MULTIPLAYER_HIT_SOUND_EVENT_HPP

#include "event.hpp"

namespace Harmony {
    using MultiplayerHitSoundEvent_t = bool (*)(float);

    /**
     * Add a multiplayer hit sound event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_multiplayer_hit_sound_event(MultiplayerHitSoundEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a multiplayer hit sound event.
     * @param function  Function of the event to be removed
     */
    void remove_multiplayer_hit_sound_event(MultiplayerHitSoundEvent_t event_function);

    /**
     * Set up multiplayer hit sound event
     */
    void set_up_multiplayer_hit_sound_event();
}

#endif

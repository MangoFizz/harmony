// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_MULTIPLAYER_SOUND
#define HARMONY_EVENT_MULTIPLAYER_SOUND

#include "../halo_data/multiplayer_sounds.hpp"
#include "event.hpp"

namespace Harmony {
    /**
     * This is an event that is triggered when a multiplayer sound is played.
     * @param  sound sound that is player
     */
    using MultiplayerSoundEventFunction = bool (*)(HaloData::MultiplayerSound sound);

    /**
     * Add a multiplayer sound event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_multiplayer_sound_event(MultiplayerSoundEventFunction event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a tick event.
     * @param function  Function of the event to be removed
     */
    void remove_multiplayer_sound_event(MultiplayerSoundEventFunction event_function);

    /**
     * Set up multiplayer sounds event
     */
    void enable_multiplayer_sounds_hook();
}

#endif

// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_MENU_SOUND_HPP
#define HARMONY_EVENT_MENU_SOUND_HPP

#include "../halo_data/menu.hpp"
#include "event.hpp"

namespace Harmony {
    using MenuSoundEvent_t = bool (*)(HaloData::TagID, HaloData::MenuSound);

    /**
     * Add a menu sound event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_menu_sound_event(MenuSoundEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a menu mouse button press event
     * @param function  Function of the event to be removed
     */
    void remove_menu_sound_event(MenuSoundEvent_t event_function);

    /**
     * Set up menu sound event
     */
    void set_up_menu_sound_event();
}

#endif

// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_MENU_BUTTON_PRESS_HPP
#define HARMONY_EVENT_MENU_BUTTON_PRESS_HPP

#include "../halo_data/menu.hpp"
#include "../halo_data/tag.hpp"
#include "event.hpp"

namespace Harmony {
    using MenuMouseButtonPressEvent_t = bool (*)(HaloData::TagID, HaloData::MenuMouseButtonCode button);

    /**
     * Add a menu mouse button press event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_menu_mouse_button_press_event(MenuMouseButtonPressEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a menu mouse button press event
     * @param function  Function of the event to be removed
     */
    void remove_menu_mouse_button_press_event(MenuMouseButtonPressEvent_t event_function);

    /**
     * Set up menu mouse button press event
     */
    void set_up_menu_mouse_button_press_event();
}

#endif

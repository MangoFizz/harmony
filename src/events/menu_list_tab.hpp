// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENT_MENU_LIST_TAB_HPP
#define HARMONY_EVENT_MENU_LIST_TAB_HPP

#include "../halo_data/menu.hpp"
#include "../halo_data/tag.hpp"
#include "event.hpp"

namespace Harmony {
    using MenuListTabEvent_t = bool (*)(HaloData::MenuNavigationKeyCode key, HaloData::TagID, HaloData::TagID);

    /**
     * Add a menu list tab event
     * @param function  Function to be executed when the event occurs
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_menu_list_tab_event(MenuListTabEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT);

    /**
     * Remove a menu list tab event
     * @param function  Function of the event to be removed
     */
    void remove_menu_list_tab_event(MenuListTabEvent_t event_function);

    /**
     * Set up menu list tab
     */
    void set_up_menu_list_tab_event();
}

#endif

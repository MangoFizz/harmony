// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_EVENTS_CONSOLE_COMMAND_HPP
#define HARMONY_EVENTS_CONSOLE_COMMAND_HPP

#include <string>
#include "event.hpp"

namespace Harmony {
    /**
     * This is an event that is triggered when a console unknown command is called.
     * @param command   Console command
     */
    using ConsoleUnknownCommandEvent_t = bool (*)(std::string, std::string);

    /**
     * Add a console unknown command event.
     * @param function  Function to execute when a console command is called
     * @param priority  This is the priority that defines the order in which the event will be called
     */
    void add_console_unknown_command_event(ConsoleUnknownCommandEvent_t event_function, EventPriority priority = EVENT_PRIORITY_DEFAULT) noexcept;

    /**
     * Remove a console unknown command event.
     * @param function  Function of the event to remove
     */
    void remove_console_unknown_command_event(ConsoleUnknownCommandEvent_t event_function) noexcept;

    /**
     * Set up console unknown command event
     */
    void set_up_console_unknown_command_event();
}

#endif

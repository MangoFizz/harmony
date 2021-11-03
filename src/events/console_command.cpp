// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "console_command.hpp"

namespace Harmony {
    static Memory::SwitchHook console_command_hook;
    static std::vector<Event<ConsoleCommandEvent_t>> events;

    void add_console_command_event(const ConsoleCommandEvent_t function, EventPriority priority) noexcept {
        // Remove if exists
        remove_console_command_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_console_command_event(const ConsoleCommandEvent_t function) noexcept {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    static void do_on_console_command(const char *command) noexcept {
        bool allow = true;
        call_in_order_allow(events, allow, command);
        console_command_hook.execute_original_code(allow);
    }

    void set_up_console_command_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signatures
        static auto &console_unknown_command_message_call_sig = Harmony::get().get_signature("console_call");
        
        // Write hacks
        console_command_hook.initialize(console_unknown_command_message_call_sig.get_data(), reinterpret_cast<void *>(do_on_console_command), true);
        console_command_hook.hook();
    }
}

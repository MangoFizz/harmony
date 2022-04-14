// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../messaging/message_box.hpp"
#include "../harmony.hpp"
#include "console_unknown_command.hpp"

namespace Harmony {
    static Memory::SwitchHook console_unknown_command_print_hook;
    static Memory::SwitchHook console_unknown_command_push_hook;
    static std::vector<Event<ConsoleUnknownCommandEvent_t>> events;

    extern "C" {
        void call_console_unknown_command_events_asm();

        void call_console_unknown_command_events(const char *command) {
            bool allow = true;
            const char *arguments = command + strlen(command) + 1;
            call_in_order_allow(events, allow, command, arguments);
            console_unknown_command_print_hook.execute_original_code(allow);
        }
    }

    static void undo_chimera_block() noexcept {
        console_unknown_command_print_hook.release();
        console_unknown_command_print_hook.hook();
    }

    void add_console_unknown_command_event(const ConsoleUnknownCommandEvent_t function, EventPriority priority) noexcept {
        // Remove if exists
        remove_console_unknown_command_event(function);

        // Add the event
        events.emplace_back(function, priority);
    }

    void remove_console_unknown_command_event(const ConsoleUnknownCommandEvent_t function) noexcept {
        for(std::size_t i = 0; i < events.size(); i++) {
            if(events[i].function == function) {
                events.erase(events.begin() + i);
                return;
            }
        }
    }

    void set_up_console_unknown_command_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        static auto &console_unknown_command_message_call_sig = Harmony::get().get_signature("console_unknown_command_message_print_call");
        console_unknown_command_print_hook.initialize(console_unknown_command_message_call_sig.get_data(), reinterpret_cast<void *>(call_console_unknown_command_events_asm), false);
        console_unknown_command_print_hook.hook();

        static auto &console_unknown_command_message_command_push_sig = Harmony::get().get_signature("console_unknown_command_message_command_push");
        console_unknown_command_push_hook.initialize(console_unknown_command_message_command_push_sig.get_data(), reinterpret_cast<void *>(undo_chimera_block), true);
        console_unknown_command_push_hook.hook();
    }
}

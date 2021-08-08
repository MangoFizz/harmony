// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "console_command.hpp"

namespace Harmony {
    static Codecave on_console_command_cave;
    static Signature *console_output_sig;
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

        if(!allow) {
            Memory::nuke_function(console_output_sig->get_data());
        }
    }

    static void restore_console_output() noexcept {
        console_output_sig->restore();
    }

    void enable_console_command_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signatures
        static auto &on_console_command_sig = get_harmony().get_signature("console_call");
        console_output_sig = &get_harmony().get_signature("console_out");
        
        // Write hacks
        on_console_command_cave.hack_chimera_function_call(on_console_command_sig.get_data(), reinterpret_cast<void *>(do_on_console_command), reinterpret_cast<void *>(restore_console_output));

        // Hook map load call
        on_console_command_cave.hook();
    }
}

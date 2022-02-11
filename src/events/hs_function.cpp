// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../memory/codefinder.hpp"
#include "../harmony.hpp"
#include "hs_function.hpp"

#include "../messaging/message_box.hpp"

namespace Harmony {
    static Memory::SwitchHook hs_function_hook;
    static Memory::FunctionOverride hs_get_function_parameters_function_hook;
    static std::vector<Event<HsFunctionEvent_t>> hs_function_events;

    extern "C" {
        void script_function();

        void on_hs_function(const char *script, HaloData::ScriptFunction *function, const std::uint32_t *params) {
            bool allow = true;
            call_in_order(hs_function_events, script, function, params);
        }

        void get_script_function_parameters_override();
        const void *get_script_function_parameters_fn;
    }

    void add_hs_function_event(HsFunctionEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_hs_function_event(function);

        // Add the event
        hs_function_events.emplace_back(function, priority);
    }

    void remove_hs_function_event(HsFunctionEvent_t function) {
        for(std::size_t i = 0; i < hs_function_events.size(); i++) {
            if(hs_function_events[i].function == function) {
                hs_function_events.erase(hs_function_events.begin() + i);
                return;
            }
        }
    }

    void set_up_hs_function_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signatures
        auto &hs_function_call_sig = Harmony::get().get_signature("hs_function_call");
        auto &hs_get_function_parameters_function_sig = Harmony::get().get_signature("hs_get_function_parameters_function");
        
        // Write the hacks
        hs_function_hook.initialize(hs_function_call_sig.get_data(), reinterpret_cast<void *>(script_function), false);
        hs_get_function_parameters_function_hook.initialize(hs_get_function_parameters_function_sig.get_data(), reinterpret_cast<void *>(get_script_function_parameters_override), &get_script_function_parameters_fn);

        // Hook everything
        hs_function_hook.hook();
        hs_get_function_parameters_function_hook.hook();
    }
}

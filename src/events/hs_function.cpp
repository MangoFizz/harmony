// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/hook.hpp"
#include "../memory/signature.hpp"
#include "../memory/codefinder.hpp"
#include "../harmony.hpp"
#include "hs_function.hpp"

#include "../messaging/message_box.hpp"

namespace Harmony {
    static Memory::RawHook hs_function_hook;
    static Memory::FunctionOverride hs_get_function_parameters_function_hook;
    static std::vector<Event<HsFunctionEvent_t>> hs_function_events;

    extern "C" {
        void hs_function_hook_fn();
        const void *hs_function_hook_fn_return;

        bool on_hs_function(const char *script, HaloData::ScriptFunction *function, const std::uint32_t *params) {
            bool allow = true;
            call_in_order_allow(hs_function_events, allow, script, function, params);
            return allow;
        }

        void get_hs_function_parameters_fn_override();
        const void *get_hs_function_parameters_fn_return;
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
        hs_function_hook.initialize(hs_function_call_sig.get_data(), reinterpret_cast<void *>(hs_function_hook_fn), &hs_function_hook_fn_return);
        hs_get_function_parameters_function_hook.initialize(hs_get_function_parameters_function_sig.get_data(), reinterpret_cast<void *>(get_hs_function_parameters_fn_override), &get_hs_function_parameters_fn_return);

        // Hook everything
        hs_function_hook.hook();
        hs_get_function_parameters_function_hook.hook();
    }
}

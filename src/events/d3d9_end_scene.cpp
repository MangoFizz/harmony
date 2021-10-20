// SPDX-License-Identifier: GPL-3.0-only

#include "d3d9_end_scene.hpp"
#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/signature.hpp"
#include "../messaging/message_box.hpp"
#include "../harmony.hpp"

namespace Harmony {
    static std::vector<Event<EndSceneEvent_t>> end_scene_events;

    extern "C" {
        void on_d3d9_end_scene_asm();
    }

    void add_d3d9_end_scene_event(const EndSceneEvent_t function, EventPriority priority) {
        // Remove if exists
        remove_d3d9_end_scene_event(function);

        // Add the event
        end_scene_events.emplace_back(Event<EndSceneEvent_t> { function, priority });
    }

    void remove_d3d9_end_scene_event(const EndSceneEvent_t function) {
        for(std::size_t i = 0; i < end_scene_events.size(); i++) {
            if(end_scene_events[i].function == function) {
                end_scene_events.erase(end_scene_events.begin() + i);
                return;
            }
        }
    }

    extern "C" void do_d3d9_end_scene_event(LPDIRECT3DDEVICE9 device) {
        call_in_order(end_scene_events, device);
    }

    void set_up_d3d9_end_scene_event() {
        // Enable if not already enabled.
        static bool enabled = false;
        if(enabled) {
            return;
        }
        enabled = true;

        // Get signature
        static auto &d3d9_call_end_scene_sig = Harmony::get().get_signature("d3d9_call_end_scene");
        
        // Write hacks
        static Codecave d3d9_end_scene_cave;
        d3d9_end_scene_cave.write_basic_cave(d3d9_call_end_scene_sig.get_data(), reinterpret_cast<void *>(on_d3d9_end_scene_asm), false);

        // Hook D3D9 end scene call
        d3d9_end_scene_cave.hook();
    }
}

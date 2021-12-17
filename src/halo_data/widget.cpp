// SPDX-License-Identifier: GPL-3.0-only

#include <d3d9.h>
#include <cmath>
#include "../memory/signature.hpp"
#include "../menu/widescreen_override.hpp"
#include "../harmony.hpp"
#include "widget.hpp"

namespace Harmony::HaloData {
    WidgetEventGlobals &WidgetEventGlobals::get() {
        static auto &menu_widget_event_globals_sig = Harmony::get().get_signature("menu_widget_event_globals");
        static auto *widget_event_globals = *reinterpret_cast<WidgetEventGlobals **>(menu_widget_event_globals_sig.get_data());
        return *widget_event_globals;
    }
    
    WidgetCursorGlobals &WidgetCursorGlobals::get() {
        static auto &menu_cursor_globals_sig = Harmony::get().get_signature("menu_cursor_globals");
        static auto *widget_cursor_globals = *reinterpret_cast<WidgetCursorGlobals **>(menu_cursor_globals_sig.get_data());
        return *widget_cursor_globals;
    }
    
    WidgetGlobals &WidgetGlobals::get() {
        static auto &menu_widget_globals_sig = Harmony::get().get_signature("menu_widget_globals");
        static auto *widget_globals = *reinterpret_cast<WidgetGlobals **>(menu_widget_globals_sig.get_data());
        return *widget_globals;
    }
    
    Math::Point2D WidgetCursorGlobals::get_normalized_position() const {
        auto &ws_handle = Harmony::get().get_widescreen_override_handle();
        std::uint32_t mouse_bounds_displacement = floor(ws_handle.get_menu_displacement());
        std::uint32_t menu_frame_width = ws_handle.get_aspect_ratio() * 480.000f;

        std::uint32_t mouse_left_bound = -mouse_bounds_displacement;
        std::uint32_t mouse_right_bound = menu_frame_width + mouse_bounds_displacement;
        
        float x = static_cast<float>(position.x - mouse_left_bound) / (mouse_right_bound - mouse_left_bound);
        float y = static_cast<float>(position.y) / 480;
        return {x, y};
    }
    
    Math::Point2D WidgetCursorGlobals::get_framebuffer_position() const {
        static auto &d3d9_present_parameters_sig = Harmony::get().get_signature("d3d9_present_parameters");
        static auto const *present_parameters = *reinterpret_cast<D3DPRESENT_PARAMETERS **>(d3d9_present_parameters_sig.get_data());
        
        const auto [normalized_x, normalized_y] = get_normalized_position();
        return {normalized_x * present_parameters->BackBufferWidth, normalized_y * present_parameters->BackBufferHeight};
    }
}
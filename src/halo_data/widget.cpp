// SPDX-License-Identifier: GPL-3.0-only

#include <d3d9.h>
#include <cmath>
#include "../memory/signature.hpp"
#include "../menu/widescreen_override.hpp"
#include "../harmony.hpp"
#include "widget.hpp"

namespace Harmony::HaloData {
    extern "C" {
        /**
         * Open a widget.
         * @param widget_id     Tag ID of the widget to open
         */
        void open_widget_asm(TagID widget_id) noexcept;

        /**
         * Open a widget and pushes the current one to the menu history.
         * If there is no widget instance, the widget will not open.
         * @param previous_widget_instance  Pointer to the current root widget instance
         * @param widget_id                 Tag ID of the widget to open
         */
        void open_widget_push_history_asm(WidgetInstance *previous_widget_instance, TagID widget_id) noexcept;
    }

    std::string GamepadButtonWidgetEvent::string_for_button(GamepadButtonWidgetEvent::Button btn) noexcept {
        switch(btn) {
            case Button::BUTTON_A:
                return "a";
            case Button::BUTTON_B:
                return "b";
            case Button::BUTTON_X:
                return "x";
            case Button::BUTTON_Y:
                return "y";
            case Button::BUTTON_BLACK:
                return "black";
            case Button::BUTTON_WHITE:
                return "white";
            case Button::BUTTON_LEFT_TRIGGER:
                return "left trigger";
            case Button::BUTTON_RIGHT_TRIGGER:
                return "right trigger";
            case Button::BUTTON_DPAD_UP:
                return "dpad up";
            case Button::BUTTON_DPAD_DOWN:
                return "dpad down";
            case Button::BUTTON_DPAD_LEFT:
                return "dpad left";
            case Button::BUTTON_DPAD_RIGHT:
                return "dpad right";
            case Button::BUTTON_START:
                return "start";
            case Button::BUTTON_BACK:
                return "back";
            case Button::BUTTON_LEFT_THUMB:
                return "left thumb";
            case Button::BUTTON_RIGHT_THUMB:
                return "right thumb";
            default:
                return "unknown button " + std::to_string(btn);
        }
    }

    std::string MouseButtonWidgetEvent::string_for_button(MouseButtonWidgetEvent::Button btn) noexcept {
        switch(btn) {
            case Button::BUTTON_LEFT:
                return "left";
            case Button::BUTTON_MIDDLE:
                return "middle";
            case Button::BUTTON_RIGHT:
                return "right";
            case Button::BUTTON_DOUBLE_LEFT:
                return "double left";
            default:
                return "unknown button " + std::to_string(btn);
        }
    }

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

    void open_widget(TagID widget_id, bool push_history) noexcept {
        auto &widget_globals = WidgetGlobals::get();
        auto *current_widget_instance = widget_globals.root_widget_instance;
        
        if(push_history && current_widget_instance) {
            open_widget_push_history_asm(current_widget_instance, widget_id);
        }
        else {
            open_widget_asm(widget_id);
        }
    }
}
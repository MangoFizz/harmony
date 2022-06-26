// SPDX-License-Identifier: GPL-3.0-only

#include <cstdint>
#include "../events/map_load.hpp"
#include "../events/tick.hpp"
#include "../halo_data/resolution.hpp"
#include "../halo_data/tag.hpp"
#include "../halo_data/tag_class.hpp"
#include "../halo_data/widget.hpp"
#include "../memory/signature.hpp"
#include "../memory/memory.hpp"
#include "../memory/hook.hpp"
#include "../memory/struct.hpp"
#include "../messaging/console_output.hpp"
#include "../messaging/message_box.hpp"
#include "../harmony.hpp"
#include "widescreen.hpp"

namespace Harmony::Menu {
    static Memory::Hook widescreen_element_position_menu_hook;
    static Memory::Hook widescreen_menu_text_hook;
    static Memory::Hook widescreen_menu_text_2_hook;
    static Memory::Hook widescreen_input_text_hook;
    static Memory::SwitchHook widescreen_mouse_hook;
    static bool ready = false;
    static bool enabled = false;
    static float screen_width_480p = 0;
    static float menu_aspect_ratio = 0;
    static float menu_displacement = 0;
    
    static void jason_jones_widgets() noexcept;
    static void on_tick() noexcept;
    static void on_map_load() noexcept;

    extern "C" {
        void menu_render_background_bitmap_asm();
        void menu_render_text_asm();

        HaloData::WidgetDefinitionBounds *widescreen_text_input_element;
        void widescreen_input_text() noexcept;
        void widescreen_input_text_undo() noexcept;

        void widescreen_mouse() noexcept;
        std::int32_t widescreen_mouse_left_bound = 0;
        std::int32_t widescreen_mouse_right_bound = 640;
        std::int32_t *widescreen_mouse_x = nullptr;
        std::int32_t **widescreen_fix_mouse_x_ptr = nullptr;
        std::int32_t *widescreen_mouse_y = nullptr;
    }

    void enable_widescreen_override(bool setting) noexcept {
        if(ready) {
            if(setting) {
                // Set mouse bounds
                widescreen_mouse_x = *widescreen_fix_mouse_x_ptr;
                widescreen_mouse_y = widescreen_mouse_x + 1;

                // Redirect widescreen fix pointer to a fake variable
                static std::int32_t gotya = 0;
                *widescreen_fix_mouse_x_ptr = &gotya;

                // Hook everything
                widescreen_element_position_menu_hook.hook();
                widescreen_menu_text_hook.hook();
                widescreen_menu_text_2_hook.hook();
                widescreen_input_text_hook.hook();
                widescreen_mouse_hook.hook();

                // Register events
                add_tick_event(on_tick);
                add_map_load_event(on_map_load);

                // Stretch stock widgets
                jason_jones_widgets();

                // Set default aspect ratio
                if(menu_aspect_ratio == 0) {
                    set_menu_aspect_ratio(4, 3);
                }
            }
            else {
                // Remove events
                remove_tick_event(on_tick);
                remove_map_load_event(on_map_load);

                // Restore widescreen fix mouse position pointer
                *widescreen_fix_mouse_x_ptr = widescreen_mouse_x;
                widescreen_mouse_x = nullptr;

                // Release all hooks
                widescreen_element_position_menu_hook.release();
                widescreen_menu_text_hook.release();
                widescreen_menu_text_2_hook.release();
                widescreen_input_text_hook.release();
                widescreen_mouse_hook.release();
            }
        }        
        enabled = setting;
    }

    float get_menu_aspect_ratio() noexcept {
        return menu_aspect_ratio;
    }

    void set_menu_aspect_ratio(std::uint16_t x, std::uint16_t y) noexcept {
        menu_aspect_ratio = static_cast<float>(x) / static_cast<float>(y);
        
        // Recalculate values for new aspect ratio
        screen_width_480p = 0;
    }

    std::pair<std::uint16_t, std::uint16_t> get_mouse_horizontal_bounds() noexcept {
        return std::make_pair(widescreen_mouse_left_bound, widescreen_mouse_right_bound);
    }

    void set_up_widescreen_override() noexcept {
        if(ready) {
            return;
        }

        try {
            static auto &widescreen_element_position_menu_sig = Harmony::get().get_signature("widescreen_element_position_menu");
            widescreen_element_position_menu_hook.initialize(widescreen_element_position_menu_sig.get_data(), reinterpret_cast<void *>(menu_render_background_bitmap_asm), nullptr, false);

            static auto &widescreen_menu_text_sig = Harmony::get().get_signature("widescreen_menu_text");
            widescreen_menu_text_hook.initialize(widescreen_menu_text_sig.get_data(), reinterpret_cast<void *>(menu_render_text_asm), nullptr, false);
            
            static auto &widescreen_menu_text_2_sig = Harmony::get().get_signature("widescreen_menu_text_2");
            widescreen_menu_text_2_hook.initialize(widescreen_menu_text_2_sig.get_data(), reinterpret_cast<void *>(menu_render_text_asm), nullptr, false);
            
            static auto &widescreen_input_text_sig = Harmony::get().get_signature("widescreen_input_text");
            auto *widescreen_input_text_address = Memory::Hook::follow_jump(widescreen_input_text_sig.get_data()) + 9;
            widescreen_input_text_hook.initialize(widescreen_input_text_address, reinterpret_cast<void *>(widescreen_input_text), reinterpret_cast<void *>(widescreen_input_text_undo));

            // Get mouse bounds
            static auto &widescreen_mouse_sig = Harmony::get().get_signature("widescreen_mouse");
            auto *widescreen_mouse_address = widescreen_mouse_sig.get_data();
            auto *original_cave = Memory::Hook::follow_jump(widescreen_mouse_address);
            auto *original_widescreen_mouse_fn = Memory::Hook::follow_jump(original_cave);
            widescreen_fix_mouse_x_ptr = *reinterpret_cast<std::int32_t ***>(original_widescreen_mouse_fn + 0x28);

            widescreen_mouse_hook.initialize(widescreen_mouse_address, reinterpret_cast<void *>(widescreen_mouse), false);
            widescreen_mouse_hook.execute_original_code(false);

            ready = true;

            // If enabled, enable it again
            if(enabled) {
                enabled = false;
                enable_widescreen_override(true);
            }
        }
        catch(Memory::Hook::Exception &e) {
            console_error("harmony: Failed to enable widescreen override: Chimera's widescreen fix is disabled!");
            return;
        }
    }

    static void jason_jones_widgets() noexcept {
        auto stretch_widget = [](const char *widget_path) noexcept {
            auto *tag = HaloData::get_tag(widget_path, HaloData::TagClassInt::TAG_CLASS_UI_WIDGET_DEFINITION);
            if(!tag) {
                return;
            }

            auto *bounds = reinterpret_cast<HaloData::WidgetDefinitionBounds *>(tag->data + 0x24);
            if(bounds->left == 0.0f && bounds->right == 640.0f) {
                bounds->right = 639.0f;
            }
        };

        stretch_widget("ui\\shell\\main_menu\\halo_logo");
        stretch_widget("ui\\shell\\main_menu\\multiplayer_type_select\\join_game\\join_game_items_list");
        stretch_widget("ui\\shell\\main_menu\\settings_select\\player_setup\\player_profile_edit\\controls_setup\\controls_options_menu");
        stretch_widget("ui\\shell\\main_menu\\settings_select\\player_setup\\player_profile_edit\\gamepad_setup\\gamepad_setup_options");
    }

    static void on_tick() noexcept {
        static auto &resolution = HaloData::get_resolution();
        float current_aspect_ratio = static_cast<float>(resolution.width) / static_cast<float>(resolution.height);
        float current_screen_width = current_aspect_ratio * 480.000f;

        if(static_cast<std::uint16_t>(screen_width_480p) != static_cast<std::uint16_t>(current_screen_width)) {
            screen_width_480p = current_screen_width;

            /**
             * Calculate how much we need to displace back widgets with respect to the 
             * displacement that will be applied by the Chimera's widescreen fix.
             */
            float menu_frame_width = menu_aspect_ratio * 480.000f;
            float screen_extra_width = screen_width_480p - 640.000f;
            float menu_frame_offset = (screen_width_480p - menu_frame_width) / 2.0f;
            menu_displacement = menu_frame_offset - screen_extra_width / 2.0f;

            // Calculate mouse cursor bounds
            std::int32_t mouse_increase = static_cast<std::int32_t>(screen_width_480p - menu_frame_width) / 2;
            widescreen_mouse_left_bound = -mouse_increase;
            widescreen_mouse_right_bound = menu_frame_width + mouse_increase;

            if(*widescreen_mouse_x > menu_frame_width + mouse_increase) {
                *widescreen_mouse_x = widescreen_mouse_right_bound;
            }
            if(*widescreen_mouse_x < -mouse_increase) {
                *widescreen_mouse_x = -mouse_increase;
            }
        }
    }

    static void on_map_load() noexcept {
        jason_jones_widgets();
    }

    extern "C" void widescreen_displace_menu_elements(HaloData::WidgetRenderArea &rect, HaloData::WidgetInstance *widget) {
        float min_x = rect.top_left.x;
        float max_x = rect.top_right.x;
        float min_y = rect.top_left.y;
        float max_y = rect.bottom_left.y;

        /**
         * These widgets will be stretched by the widescreen fix
         */
        if(min_x <= 1.0f && max_x >= 639.0f && min_y <= 1.0F && max_y >= 479.0f) {
            return;
        }

        if(min_x == 0.0f && max_x == 640.0f) {
            // Revert widescreen fix displacement
            float screen_extra_width = screen_width_480p - 640.000f;
            rect.top_right.x -= screen_extra_width / 2.0f;
            rect.bottom_right.x -= screen_extra_width / 2.0f;
            rect.top_left.x -= screen_extra_width / 2.0f;
            rect.bottom_left.x -= screen_extra_width / 2.0f;

            // Stretch it
            rect.top_right.x += screen_extra_width;
            rect.bottom_right.x += screen_extra_width;
        }
        else {
            rect.top_left.x += menu_displacement;
            rect.top_right.x += menu_displacement;
            rect.bottom_right.x += menu_displacement;
            rect.bottom_left.x += menu_displacement;
        }
    }

    extern "C" void widescreen_displace_menu_text(HaloData::WidgetDefinitionBounds *text_box_bounds) noexcept {
        text_box_bounds->right += menu_displacement;
        text_box_bounds->left += menu_displacement;
    }

    extern "C" void reposition_menu_text_input() noexcept {
        widescreen_text_input_element->right -= menu_displacement;
        widescreen_text_input_element->left -= menu_displacement;
    }

    extern "C" void unreposition_menu_text_input() noexcept {
        widescreen_text_input_element->right += menu_displacement;
        widescreen_text_input_element->left += menu_displacement;
    }
}

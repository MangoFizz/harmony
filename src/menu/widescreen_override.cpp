// SPDX-License-Identifier: GPL-3.0-only

#include <cstdint>
#include "../events/map_load.hpp"
#include "../events/tick.hpp"
#include "../halo_data/resolution.hpp"
#include "../halo_data/tag.hpp"
#include "../halo_data/tag_class.hpp"
#include "../memory/signature.hpp"
#include "../memory/memory.hpp"
#include "../memory/struct.hpp"
#include "../messaging/console_output.hpp"
#include "../messaging/message_box.hpp"
#include "../harmony.hpp"
#include "widescreen_override.hpp"

namespace Harmony::UserInterface {
    /** Instance pointer */
    static WidescreenOverride *instance;

    extern "C" {   
        void widescreen_element_reposition_menu() noexcept;
        const void *widescreen_element_position_menu_fn;

        void widescreen_element_reposition_menu_text() noexcept;
        const void *widescreen_element_position_menu_text_fn;

        void widescreen_element_reposition_menu_text_2() noexcept;
        const void *widescreen_element_position_menu_text_2_fn;

        std::int16_t *widescreen_text_input_element;
        void widescreen_input_text() noexcept;
        void widescreen_input_text_undo() noexcept;

        void widescreen_mouse() noexcept;
        std::int32_t widescreen_mouse_left_bounds = 0;
        std::int32_t widescreen_mouse_right_bounds = 640;
        std::int32_t *widescreen_mouse_x = nullptr;
        std::int32_t **widescreen_fix_mouse_x_ptr = nullptr;
        std::int32_t *widescreen_mouse_y = nullptr;
    }

    void WidescreenOverride::enable(bool setting) noexcept {
        if(setting == this->enabled) {
            return;
        }
        if(setting) {
            try {
                static auto &widescreen_element_position_menu_sig = Harmony::get().get_signature("widescreen_element_position_menu");
                this->overrides.emplace_back(std::make_unique<Memory::ChimeraFunctionOverride>(widescreen_element_position_menu_sig.get_data(), reinterpret_cast<void *>(widescreen_element_reposition_menu), &widescreen_element_position_menu_fn));

                static auto &widescreen_menu_text_sig = Harmony::get().get_signature("widescreen_menu_text");
                this->overrides.emplace_back(std::make_unique<Memory::ChimeraFunctionOverride>(widescreen_menu_text_sig.get_data(), reinterpret_cast<void *>(widescreen_element_reposition_menu_text), &widescreen_element_position_menu_text_fn));
                
                static auto &widescreen_menu_text_2_sig = Harmony::get().get_signature("widescreen_menu_text_2");
                this->overrides.emplace_back(std::make_unique<Memory::ChimeraFunctionOverride>(widescreen_menu_text_2_sig.get_data(), reinterpret_cast<void *>(widescreen_element_reposition_menu_text_2), &widescreen_element_position_menu_text_2_fn));
                
                static auto &widescreen_input_text_sig = Harmony::get().get_signature("widescreen_input_text");
                auto *widescreen_input_text_address = Memory::Hook::follow_jump(widescreen_input_text_sig.get_data()) + 9;
                this->overrides.emplace_back(std::make_unique<Memory::Hook>(widescreen_input_text_address, reinterpret_cast<void *>(widescreen_input_text), reinterpret_cast<void *>(widescreen_input_text_undo)));

                // Get mouse bounds
                static auto &widescreen_mouse_sig = Harmony::get().get_signature("widescreen_mouse");
                auto *widescreen_mouse_address = widescreen_mouse_sig.get_data();
                auto *original_cave = Memory::Hook::follow_jump(widescreen_mouse_address);
                auto *original_widescreen_mouse_fn = Memory::Hook::follow_jump(original_cave);
                widescreen_fix_mouse_x_ptr = *reinterpret_cast<std::int32_t ***>(original_widescreen_mouse_fn + 0x28);
                widescreen_mouse_x = *widescreen_fix_mouse_x_ptr;
                widescreen_mouse_y = widescreen_mouse_x + 1;

                // Redirect widescreen fix mouse x pointer to a fake variable
                static std::int32_t gotya = 0;
                *widescreen_fix_mouse_x_ptr = &gotya;

                // Get and recast the meme to disble original code execution
                auto *widescreen_mouse_cave = this->overrides.emplace_back(std::make_unique<Memory::SwitchHook>(widescreen_mouse_address, reinterpret_cast<void *>(widescreen_mouse), false)).get();
                static_cast<Memory::SwitchHook *>(widescreen_mouse_cave)->execute_original_code(false);
            }
            catch(Memory::Hook::Exception &e) {
                console_error("%s", "Failed to enable widescreen override: Chimera's widescreen fix is disabled!");
                if(widescreen_mouse_x) {
                    *widescreen_fix_mouse_x_ptr = widescreen_mouse_x;
                    widescreen_mouse_x = nullptr;
                }
                this->overrides.clear();
                return;
            }

            // Hook everything
            for(auto &hook : this->overrides) {
                hook.get()->hook();
            }

            // Register events
            add_tick_event(this->on_tick);
            add_map_load_event(this->on_map_load);
        }
        else {
            // Remove events
            remove_tick_event(this->on_tick);
            remove_map_load_event(this->on_map_load);

            // Restore widescreen fix mouse x pointer
            *widescreen_fix_mouse_x_ptr = widescreen_mouse_x;
            widescreen_mouse_x = nullptr;

            // Destroy all caves
            this->overrides.clear();
        }
        this->enabled = setting;
    }

    void WidescreenOverride::set_aspect_ratio(std::uint16_t x, std::uint16_t y) noexcept {
        this->menu_aspect_ratio = static_cast<float>(x) / static_cast<float>(y);

        // Force widescreen readjustment
        this->screen_width_480p = 0;
    }

    void WidescreenOverride::reset_frame_aspect_ratio() noexcept {
        this->set_aspect_ratio(4, 3);
    }

    float WidescreenOverride::get_menu_extra_width() noexcept {
        return this->menu_extra_width;
    }

    float WidescreenOverride::get_menu_displacement() const noexcept {
        return this->menu_displacement;
    }

    WidescreenOverride::WidescreenOverride() noexcept {
        // Set instance pointer
        instance = this;

        // Default menu aspect ratio
        this->menu_aspect_ratio = 4.0f / 3.0f;
    }

    void WidescreenOverride::jason_jones_menu_widget(const char *widget_path) noexcept {
        auto *tag = HaloData::get_tag(widget_path, HaloData::TagClassInt::TAG_CLASS_UI_WIDGET_DEFINITION);
        if(!tag) {
            return;
        }
        std::int16_t &bounds_top = *reinterpret_cast<std::int16_t *>(tag->data + 0x24);
        std::int16_t &bounds_left = *reinterpret_cast<std::int16_t *>(tag->data + 0x26);
        std::int16_t &bounds_bottom = *reinterpret_cast<std::int16_t *>(tag->data + 0x28);
        std::int16_t &bounds_right = *reinterpret_cast<std::int16_t *>(tag->data + 0x2A);

        if(bounds_left <= 1.0f && bounds_right >= 639.0f) {
            bounds_right = 638.9f;
        }
    }

    void WidescreenOverride::on_map_load() noexcept {
        // Do not stretch this
        instance->jason_jones_menu_widget("ui\\shell\\main_menu\\multiplayer_type_select\\join_game\\join_game_items_list");
        instance->jason_jones_menu_widget("ui\\shell\\main_menu\\settings_select\\player_setup\\player_profile_edit\\controls_setup\\controls_options_menu");
        instance->jason_jones_menu_widget("ui\\shell\\main_menu\\settings_select\\player_setup\\player_profile_edit\\gamepad_setup\\gamepad_setup_options");
    }

    void WidescreenOverride::on_tick() noexcept {
        static auto &resolution = HaloData::get_resolution();
        float aspect_ratio = static_cast<float>(resolution.width) / static_cast<float>(resolution.height);
        float width_480p = aspect_ratio * 480.000f;

        if(static_cast<std::uint16_t>(instance->screen_width_480p) != static_cast<std::uint16_t>(width_480p)) {
            // Re-calculate widescreen values
            float menu_frame_width = instance->menu_aspect_ratio * 480.000f;
            instance->screen_width_480p = width_480p;
            instance->menu_extra_width = width_480p - 640.000f;
            instance->menu_displacement = (width_480p - menu_frame_width) / 2.0f;

            // Revert widescreen fix displacement
            instance->menu_displacement -= instance->menu_extra_width / 2.0f;

            // Calculate mouse cursor bounds
            std::int32_t mouse_increase = static_cast<std::int32_t>(width_480p - menu_frame_width) / 2;
            widescreen_mouse_left_bounds = -mouse_increase;
            widescreen_mouse_right_bounds = menu_frame_width + mouse_increase;
            *widescreen_mouse_x = widescreen_mouse_left_bounds;
        }
    }
    
    enum ElementCorner {
        CORNER_TOP_LEFT = 0,
        CORNER_TOP_RIGHT,
        CORNER_BOTTOM_RIGHT,
        CORNER_BOTTOM_LEFT
    };

    struct ElementData {
        struct {
            float x;
            float y;
            PADDING(0x8);
            float unknown[2];
        } corners[4];
    };

    extern "C" void reposition_menu_element(ElementData &element) noexcept {
        float min_x = element.corners[CORNER_TOP_LEFT].x;
        float max_x = element.corners[CORNER_TOP_RIGHT].x;
        float min_y = element.corners[CORNER_TOP_LEFT].y;
        float max_y = element.corners[CORNER_BOTTOM_LEFT].y;

        // This will be stretched by the widescreen fix
        if(min_x <= 1.0f && max_x >= 639.0f && min_y <= 1.0F && max_y >= 479.0f) {
            return;
        }

        float menu_extra_width = instance->get_menu_extra_width();
        float displacement = instance->get_menu_displacement();

        if(min_x == 0.0f && max_x == 640.0f) {
            // Revert widescreen fix displacement
            element.corners[CORNER_TOP_RIGHT].x -= menu_extra_width / 2.0f;
            element.corners[CORNER_BOTTOM_RIGHT].x -= menu_extra_width / 2.0f;
            element.corners[CORNER_TOP_LEFT].x -= menu_extra_width / 2.0f;
            element.corners[CORNER_BOTTOM_LEFT].x -= menu_extra_width / 2.0f;

            // Stretch it
            element.corners[CORNER_TOP_RIGHT].x += menu_extra_width;
            element.corners[CORNER_BOTTOM_RIGHT].x += menu_extra_width;
        }
        else {
            element.corners[0].x += displacement;
            element.corners[1].x += displacement;
            element.corners[2].x += displacement;
            element.corners[3].x += displacement;
        }
    }

    extern "C" void reposition_menu_text_element(std::int16_t *element) noexcept {
        auto displacement = instance->get_menu_displacement();

        element[1] += displacement;
        element[3] += displacement;
    }

    extern "C" void reposition_menu_text_input() noexcept {
        auto displacement = instance->get_menu_displacement();
        widescreen_text_input_element[1] -= displacement;
        widescreen_text_input_element[3] -= displacement;
    }

    extern "C" void unreposition_menu_text_input(std::int16_t *element) noexcept {
        auto displacement = instance->get_menu_displacement();
        widescreen_text_input_element[1] += displacement;
        widescreen_text_input_element[3] += displacement;
    }
}

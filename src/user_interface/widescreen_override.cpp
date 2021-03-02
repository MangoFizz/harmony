// SPDX-License-Identifier: GPL-3.0-only

#include <cstdint>
#include <cmath>
#include "../events/map_load.hpp"
#include "../events/tick.hpp"
#include "../halo_data/resolution.hpp"
#include "../halo_data/tag.hpp"
#include "../halo_data/tag_class.hpp"
#include "../memory/signature.hpp"
#include "../memory/codecave.hpp"
#include "../memory/memory.hpp"
#include "../memory/padding.hpp"
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
        if(setting) {
            static auto &widescreen_element_position_menu_sig = get_harmony().get_signature("widescreen_element_position_menu");
            static auto &widescreen_menu_text_sig = get_harmony().get_signature("widescreen_menu_text");
            static auto &widescreen_menu_text_2_sig = get_harmony().get_signature("widescreen_menu_text_2");
            static auto &widescreen_input_text_sig = get_harmony().get_signature("widescreen_input_text");
            static auto &widescreen_text_tab_sig = get_harmony().get_signature("widescreen_text_tab");
            static auto &widescreen_mouse_sig = get_harmony().get_signature("widescreen_mouse");

            auto *reposition_menu_cave = this->overrides.emplace_back(std::make_unique<Codecave>()).get();
            reposition_menu_cave->hack_chimera_override(widescreen_element_position_menu_sig.get_data(), reinterpret_cast<void *>(widescreen_element_reposition_menu), &widescreen_element_position_menu_fn);

            auto *reposition_menu_text_cave = this->overrides.emplace_back(std::make_unique<Codecave>()).get();
            reposition_menu_text_cave->hack_chimera_override(widescreen_menu_text_sig.get_data(), reinterpret_cast<void *>(widescreen_element_reposition_menu_text), &widescreen_element_position_menu_text_fn);

            auto *reposition_menu_text_2_cave = this->overrides.emplace_back(std::make_unique<Codecave>()).get();
            reposition_menu_text_2_cave->hack_chimera_override(widescreen_menu_text_2_sig.get_data(), reinterpret_cast<void *>(widescreen_element_reposition_menu_text_2), &widescreen_element_position_menu_text_2_fn);
            
            auto *reposition_input_text_cave = this->overrides.emplace_back(std::make_unique<Codecave>()).get();
            auto *widescreen_input_text_address = Codecave::follow_jump(widescreen_input_text_sig.get_data()) + 9;
            reposition_input_text_cave->write_function_call(widescreen_input_text_address, reinterpret_cast<void *>(widescreen_input_text), reinterpret_cast<void *>(widescreen_input_text_undo));

            // Get mouse bounds
            auto *widescreen_mouse_address = widescreen_mouse_sig.get_data();
            auto *original_cave = Codecave::follow_jump(widescreen_mouse_address);
            auto *original_widescreen_mouse_fn = Codecave::follow_jump(original_cave);
            widescreen_fix_mouse_x_ptr = *reinterpret_cast<std::int32_t ***>(original_widescreen_mouse_fn + 0x28);
            widescreen_mouse_x = *widescreen_fix_mouse_x_ptr;
            widescreen_mouse_y = widescreen_mouse_x + 1;

            // Redirect widescreen fix mouse x pointer to a fake variable
            static std::int32_t gotya = 0;
            *widescreen_fix_mouse_x_ptr = &gotya;

            auto *widescreen_mouse_cave = this->overrides.emplace_back(std::make_unique<Codecave>()).get();
            widescreen_mouse_cave->write_basic_cave(widescreen_mouse_address, reinterpret_cast<void *>(widescreen_mouse), false);
            widescreen_mouse_cave->execute_original_code(false);

            // Hook everything
            for(auto &cave : this->overrides) {
                cave.get()->hook();
            }

            this->tabs = *reinterpret_cast<std::uint16_t **>(widescreen_text_tab_sig.get_data());

            // Register events
            add_tick_event(this->on_tick);
            add_map_load_event(this->on_map_load);

            // Set up map changes
            this->on_map_load();
        }
        else {
            // Remove events
            remove_tick_event(this->on_tick);
            remove_map_load_event(this->on_map_load);

            // Restore widescreen fix mouse x pointer
            *widescreen_fix_mouse_x_ptr = widescreen_mouse_x;

            this->tabs = nullptr;

            // Destroy all caves
            this->overrides.clear();
        }
    }

    float WidescreenOverride::get_menu_extra_width() noexcept {
        return this->menu_extra_width;
    }

    float WidescreenOverride::get_menu_displacement() const noexcept {
        return this->menu_displacement;
    }

    std::uint16_t *WidescreenOverride::get_text_tabs() noexcept {
        return this->tabs;
    }

    WidescreenOverride::WidescreenOverride() noexcept {
        // Set instance pointer
        instance = this;

        // Default menu aspect ratio
        this->menu_aspect_ratio = 16.0f / 9.0f;
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
        instance->jason_jones_menu_widget("ui\\shell\\main_menu\\multiplayer_type_select\\join_game\\join_game_items_list");
        instance->jason_jones_menu_widget("ui\\shell\\main_menu\\settings_select\\player_setup\\player_profile_edit\\controls_setup\\controls_options_menu");
        instance->jason_jones_menu_widget("ui\\shell\\main_menu\\settings_select\\player_setup\\player_profile_edit\\gamepad_setup\\gamepad_setup_options");
    }

    void WidescreenOverride::on_tick() noexcept {
        static auto &resolution = HaloData::get_resolution();
        float aspect_ratio = static_cast<float>(resolution.width) / static_cast<float>(resolution.height);
        float width_480p = aspect_ratio * 480.000f;

        if(round(instance->screen_width_480p) != round(width_480p)) {
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

        if(min_x <= 1.0f && max_x >= 639.0f) {
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
        auto *tabs = instance->get_text_tabs();

        element[1] += displacement;
        element[3] += displacement;
        
        // This is for the score screens which use tabbing.
        std::uint16_t tab_count = static_cast<std::uint16_t>(tabs[0]);

        static std::int16_t last_increase = -1337;
        if(tab_count == 0) {
            last_increase = -1337;
        }
        else {
            if(tabs[1] != last_increase) {
                for(std::size_t i = 0; i < tab_count; i++) {
                    tabs[i + 1] += displacement;
                }
                last_increase = tabs[1];
            }
        }
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

// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_menu_WIDESCREEN_HPP
#define HARMONY_menu_WIDESCREEN_HPP

#include <vector>
#include <utility>
#include <memory>
#include <cstddef>
#include "../memory/hook.hpp"

namespace Harmony::Menu {
    class WidescreenOverride {
    public:
        /**
         * Enable/Disable widescreen override
         */
        void enable(bool setting) noexcept;

        /**
         * Get screen width (in 480p scale)
         */
        float get_screen_480p_width() noexcept;

        /**
         * Get widescreen displacement
         */
        float get_menu_extra_width() noexcept;

        /**
         * Get menu displacement
         */
        float get_menu_displacement() const noexcept;

        /**
         * Get widescreen fix menu displacement
         */
        float get_widescreen_fix_menu_displacement() const noexcept;

        /**
         * Get widescreen frame aspect ratio
         */
        float get_aspect_ratio() const noexcept;

        /**
         * Set widescreen frame aspect ratio
         * @param x     Width of the menu frame
         * @param y     Height of the menu frame
         */
        void set_aspect_ratio(std::uint16_t x, std::uint16_t y) noexcept;

        /**
         * Reset widescreen aspect ratio
         */
        void reset_frame_aspect_ratio() noexcept;

        /**
         * Default constructor
         */
        WidescreenOverride() noexcept;

    private:
        /** Override state */
        bool enabled = false;

        /** Menu widescreen mode */
        float widescreen_mode = false;

        /** Screen width (480p scale) */
        float screen_width_480p = 0;

        /** Screen aspect ratio */
        float menu_aspect_ratio = 0;

        /** Extra space */
        float menu_extra_width = 0;

        /** Menu frame displacement */
        float menu_displacement = 0;

        /** Widescreen fix menu frame displacement */
        float widescreen_fix_menu_displacement = 0;

        /** Menu text tabs */
        std::uint16_t *tabs;
        
        /** Chimera widescreen hooks */
        std::vector<std::unique_ptr<Memory::Hook>> overrides;

        /**
         * Force fullscreen-widget scaling
         * @param widget_path   Path of the widget tag
         */
        void jason_jones_menu_widget(const char *widget_path) noexcept;

        /**
         * Events functions
         */
        static void on_tick() noexcept;
        static void on_map_load() noexcept;
    };
}

#endif

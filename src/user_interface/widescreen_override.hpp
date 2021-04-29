// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_USER_INTERFACE_WIDESCREEN_HPP
#define HARMONY_USER_INTERFACE_WIDESCREEN_HPP

#include <vector>
#include <utility>
#include <memory>
#include <cstddef>
#include "../memory/codecave.hpp"

namespace Harmony::UserInterface {
    class WidescreenOverride {
    public:
        /**
         * Enable/Disable widescreen override
         */
        void enable(bool setting) noexcept;

        /**
         * Set widescreen frame aspect ratio
         * @param x     Width of the menu frame
         * @param y     Height of the menu frame
         */
        void set_aspect_ratio(std::uint16_t x = 4, std::uint16_t y = 3) noexcept;

        /**
         * Get widescreen fix displacement
         */
        float get_menu_extra_width() noexcept;

        /**
         * Get menu displacement
         */
        float get_menu_displacement() const noexcept;

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

        /** Menu frame left displacement */
        float menu_displacement = 0;

        /** Menu text tabs */
        std::uint16_t *tabs;
        
        /** Chimera widescreen hooks */
        std::vector<std::unique_ptr<Codecave>> overrides;

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
        static void reset_frame_aspect_ratio() noexcept;
    };
}

#endif

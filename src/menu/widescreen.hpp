// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__MENU__WIDESCREEN_HPP
#define HARMONY__MENU__WIDESCREEN_HPP

#include <utility>
#include <cstdint>

namespace Harmony::Menu {
    /**
     * Enable or disable Chimera's widescreen fix override
     */
    void enable_widescreen_override(bool setting) noexcept;

    /**
     * Get the current menu aspect ratio
     */
    float get_menu_aspect_ratio() noexcept;

    /**
     * Set the current menu aspect ratio
     */
    void set_menu_aspect_ratio(std::uint16_t x, std::uint16_t y) noexcept;

    /**
     * Get the current mouse horizontal bounds
     * @return  Left and right mouse bounds
     */
    std::pair<std::uint16_t, std::uint16_t> get_mouse_horizontal_bounds() noexcept;

    /**
     * Set up Chimera's widescreen fix override
     */
    void set_up_widescreen_override() noexcept;
}

#endif

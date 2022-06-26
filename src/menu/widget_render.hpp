// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__MENU__MENU_HPP
#define HARMONY__MENU__MENU_HPP

#include <utility>
#include <cstdint>
#include "../halo_data/widget.hpp"
#include "../math/geometry.hpp"

namespace Harmony::Menu {
    /**
     * Scale the render area of the cursor
     * @param scale         Scale to apply
     */
    void set_cursor_scale(float scale) noexcept;
}

#endif

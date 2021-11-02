// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_MENU_HPP
#define HARMONY_HALO_DATA_MENU_HPP

#include <string>
#include <cstdint>
#include "tag.hpp"

namespace Harmony::HaloData {
    enum MenuNavigationKeyCode {
        MENU_NAVIGATION_KEY_ENTER = 0,
        MENU_NAVIGATION_KEY_SUPR = 0x02,
        MENU_NAVIGATION_KEY_INSERT,
        MENU_NAVIGATION_KEY_UP = 0x08,
        MENU_NAVIGATION_KEY_DOWN,
        MENU_NAVIGATION_KEY_LEFT,
        MENU_NAVIGATION_KEY_RIGHT,
        MENU_NAVIGATION_KEY_ESCAPE = 0x0D
    };
    std::string string_from_menu_key_code(MenuNavigationKeyCode key) noexcept;

    enum MenuMouseButtonCode {
        MENU_MOUSE_BUTTON_LEFT = 0,
        MENU_MOUSE_BUTTON_MIDDLE,
        MENU_MOUSE_BUTTON_RIGHT,
        MENU_MOUSE_BUTTON_DOUBLE_LEFT
    };
    std::string string_from_menu_mouse_button_code(MenuMouseButtonCode button) noexcept;

    enum MenuSound {
        MENU_SOUND_CURSOR = 0,
        MENU_SOUND_FORWARD,
        MENU_SOUND_BACK,
        MENU_SOUND_FLAG_FAILURE
    };
    std::string string_from_menu_sound(MenuSound sound) noexcept;
}

#endif

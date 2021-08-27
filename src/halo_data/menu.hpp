// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_HALO_DATA_MENU_HPP
#define HARMONY_HALO_DATA_MENU_HPP

#include <string>
#include <cstdint>

namespace Harmony::HaloData {
    enum MenuNavigationKeyCode {
        MENU_NAVIGATION_KEY_ENTER = 0,
        MENU_NAVIGATION_KEY_SUPR = 0x2,
        MENU_NAVIGATION_KEY_INSERT = 0x3,
        MENU_NAVIGATION_KEY_UP = '\b',
        MENU_NAVIGATION_KEY_DOWN = '\t',
        MENU_NAVIGATION_KEY_LEFT = '\n',
        MENU_NAVIGATION_KEY_RIGHT = '\v',
        MENU_NAVIGATION_KEY_ESCAPE = '\r'
    };
    std::string string_from_menu_key_code(MenuNavigationKeyCode key) noexcept;

    enum MenuMouseButtonCode {
        MENU_MOUSE_BUTTON_LEFT = 0,
        MENU_MOUSE_BUTTON_MIDDLE,
        MENU_MOUSE_BUTTON_RIGHT,
        MENU_MOUSE_BUTTON_DOUBLE_LEFT
    };
    std::string string_from_menu_mouse_button_code(MenuMouseButtonCode button) noexcept;
}

#endif

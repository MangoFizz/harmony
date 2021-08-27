// SPDX-License-Identifier: GPL-3.0-only

#include "menu.hpp"

namespace Harmony::HaloData {
    std::string string_from_menu_key_code(MenuNavigationKeyCode key) noexcept {
        switch(key) {
            case MenuNavigationKeyCode::MENU_NAVIGATION_KEY_ENTER:      return "enter";
            case MenuNavigationKeyCode::MENU_NAVIGATION_KEY_SUPR:       return "supr";
            case MenuNavigationKeyCode::MENU_NAVIGATION_KEY_INSERT:     return "insert";
            case MenuNavigationKeyCode::MENU_NAVIGATION_KEY_UP:         return "up";
            case MenuNavigationKeyCode::MENU_NAVIGATION_KEY_DOWN:       return "down";
            case MenuNavigationKeyCode::MENU_NAVIGATION_KEY_LEFT:       return "left";
            case MenuNavigationKeyCode::MENU_NAVIGATION_KEY_RIGHT:      return "right";
            case MenuNavigationKeyCode::MENU_NAVIGATION_KEY_ESCAPE:     return "escape";
            
            default: {
                auto str = "unknown key (" + std::to_string(key) + ")";
                return str.c_str();
            }
        }
    }

    std::string string_from_menu_mouse_button_code(MenuMouseButtonCode button) noexcept {
        switch(button) {
            case MenuMouseButtonCode::MENU_MOUSE_BUTTON_LEFT:           return "left button";
            case MenuMouseButtonCode::MENU_MOUSE_BUTTON_MIDDLE:         return "middle button";
            case MenuMouseButtonCode::MENU_MOUSE_BUTTON_RIGHT:          return "right button";
            case MenuMouseButtonCode::MENU_MOUSE_BUTTON_DOUBLE_LEFT:    return "double left button";
            
            default: {
                auto str = "unknown mouse button (" + std::to_string(button) + ")";
                return str.c_str();
            }
        }
    }
}
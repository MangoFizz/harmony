-- SPDX-License-Identifier: GPL-3.0-only

clua_version = 2.056

local harmony = require "mods.harmony"

local function get_widget_name(widget_id)
    local widget_values = harmony.menu.get_widget_values(widget_id)
    return widget_values.name
end

function on_widget_open(widget_id) 
    console_out("[widget open] " .. get_widget_name(widget_id))
end

function on_widget_accept(widget_id)
    console_out("[widget accept] " .. get_widget_name(widget_id))
    return true
end

function on_widget_back(widget_id)
    console_out("[widget back] " .. get_widget_name(widget_id))
    return true
end

function on_widget_list_tab(key, list_id, button_id)
    console_out("[widget list tab] Pressed key " .. key .. " on widget " .. get_widget_name(button_id) .. " from list " .. get_widget_name(list_id))
    return true
end

function on_widget_mouse_button_press(widget_id, button)
    console_out("[widget mouse button press] Pressed button " .. button .. " on widget " .. get_widget_name(widget_id))
    return true
end

function on_widget_mouse_focus(widget_id)
    console_out("[widget mouse focus] Focussed widget " .. get_widget_name(widget_id))
    return true
end

function on_widget_sound(sound)
    console_out("[widget sound] " .. sound)
    return true
end

harmony.set_callback("widget open", "on_widget_open")
harmony.set_callback("widget accept", "on_widget_accept")
harmony.set_callback("widget back", "on_widget_back")
harmony.set_callback("widget list tab", "on_widget_list_tab")
harmony.set_callback("widget mouse button press", "on_widget_mouse_button_press")
harmony.set_callback("widget mouse focus", "on_widget_mouse_focus")
harmony.set_callback("widget sound", "on_widget_sound")

-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Menu fade-in effect
-- Adds a fade-in effect to menus
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

clua_version = 2.056

local harmony = require "mods.harmony"

-- Duration in milliseconds
local animation_duration = 215

-- Script state
local animation_play = false
local animation_bezier_curve = nil
local animation_start_timestamp = nil
local current_widget = nil
local current_widget_background = nil
local last_widget_background = nil

local function get_widget_definition_background(tagId)
    local tag_address = get_tag(tagId)
    if(not tag_address) then
        return nil
    end

    local tag_data = read_dword(tag_address + 0x14)
    local background = read_dword(tag_data + 0x44)

    return background
end


local function apply_opacity(opacity)
    local new_widget_values = {
        opacity = opacity
    }

    -- If previous widget background is the same on current widget, just apply the effect to its childs.
    if(current_widget_background == last_widget_background) then
        local current_widget_values = harmony.menu.get_widget_values(current_widget)
        local current_child = current_widget_values.child_widget
        local previous_child = nil
        while(current_child) do
            if(previous_child == current_child) then
                break
            end
            harmony.menu.set_widget_values(current_child, new_widget_values)
            local current_widget_values = harmony.menu.get_widget_values(current_child)
            previous_child = current_child
            current_child = current_widget_values.next_widget
            
        end
    else 
        harmony.menu.set_widget_values(current_widget, new_widget_values)
    end
end

function on_preframe()
    if(animation_play and harmony.menu.get_root_widget()) then
        -- Calculate elapsed seconds
        local animation_elapsed_milliseconds = harmony.time.get_elapsed_milliseconds(animation_start_timestamp)
        
        if(animation_elapsed_milliseconds < animation_duration) then
            local t = animation_elapsed_milliseconds / animation_duration
            local new_opacity = harmony.math.get_bezier_curve_point(animation_bezier_curve, 0, 1, t)
    
            apply_opacity(new_opacity)
        else
            -- Reset opacity, just in case
            apply_opacity(1.0)
            
            animation_play = false
        end
    end
end

function on_tick()
    if(not harmony.menu.get_root_widget()) then
        current_widget = nil
        current_widget_background = nil
    end
end

function on_widget_open(widget)
    current_widget = widget

    -- Update widget background
    local current_widget_values = harmony.menu.get_widget_values(current_widget)

    last_widget_background = current_widget_background
    current_widget_background = get_widget_definition_background(current_widget_values.tag_id)

    -- Workaround for stock UI widget wrappers. Use wrapped widget instead.
    local current_widget_name = current_widget_values.name
    if(current_widget_values.child_widget and (current_widget_name:find("wrapper") or current_widget_name:find("connected"))) then
        local wrapped_widget = current_widget_values.child_widget
        local wrapped_widget_values = harmony.menu.get_widget_values(wrapped_widget)

        if(wrapped_widget_values.name:find("wrapper")) then
            wrapped_widget = wrapped_widget_values.child_widget
            wrapped_widget_values = harmony.menu.get_widget_values(wrapped_widget)
        end

        current_widget = wrapped_widget
        current_widget_background = get_widget_definition_background(wrapped_widget_values.tag_id)
    end

    animation_start_timestamp = harmony.time.set_timestamp()
    animation_play = true
end

function on_load()
    animation_bezier_curve = harmony.math.create_bezier_curve("ease in")

    -- Set up callbacks
    set_callback("preframe", "on_preframe")
    set_callback("tick", "on_tick")
    harmony.set_callback("widget open", "on_widget_open")
end

-- Load script stuff
on_load()

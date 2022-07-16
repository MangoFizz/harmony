-- SPDX-License-Identifier: GPL-3.0-only

------------------------------------------------------------------------------
-- Hitmarker
-- Adds an animated hitmarker
-- Source: https://github.com/JerryBrick/harmony
------------------------------------------------------------------------------

clua_version = 2.056

local harmony = require "mods.harmony"
local optic = harmony.optic

-- Paramenters
local duration = 125
local marker_scale = 3

local screen_width = read_word(0x637CF2)
local screen_height = read_word(0x637CF0)
local marker_corner_size = screen_width * (marker_scale / 640)
local animation_duration = duration
local fade_out_duration = duration / 3
local animation_displacement = marker_corner_size * 1.85
local kill_marker = false

-- Optic resources
local hitmarker_corner_sprite
local killmarker_corner_sprite
local top_left_corner_anim
local top_right_corner_anim
local bottom_left_corner_anim
local bottom_right_corner_anim
local fade_out_anim
local hit_sound
local audio_engine

local function render_marker(sprite) 
    local position_x = (screen_width - marker_corner_size) / 2
    local position_y = (screen_height - marker_corner_size) / 2
    local displacement = marker_corner_size * 4.5
    local opacity = 255
    optic.render_sprite(sprite, position_x - displacement, position_y - displacement, opacity, 180, duration, top_left_corner_anim, fade_out_anim)
    optic.render_sprite(sprite, position_x + displacement, position_y - displacement, opacity, -90, duration, top_right_corner_anim, fade_out_anim)
    optic.render_sprite(sprite, position_x - displacement, position_y + displacement, opacity, 90, duration, bottom_left_corner_anim, fade_out_anim)
    optic.render_sprite(sprite, position_x + displacement, position_y + displacement, opacity, 0, duration, bottom_right_corner_anim, fade_out_anim)
end

function on_multiplayer_event(event_name, local_id, killer_id, victim_id)
    if(event_name == "local killed player") then
        if(local_id == killer_id) then
            render_marker(killmarker_corner_sprite)

            -- Block hitmarker
            kill_marker = true
        end
    end
end

function on_multiplayer_hit_sound(sound)
    if(not kill_marker) then
        render_marker(hitmarker_corner_sprite)
    else
        kill_marker = false
        return false
    end
    return true
end

function on_load()
    hitmarker_corner_sprite = optic.create_sprite("hm_blue_corner.png", marker_corner_size, marker_corner_size)
    killmarker_corner_sprite = optic.create_sprite("hm_red_corner.png", marker_corner_size, marker_corner_size)

    top_left_corner_anim = optic.create_animation(animation_duration)
    optic.set_animation_property(top_left_corner_anim, "ease in out", "position x", -animation_displacement)
    optic.set_animation_property(top_left_corner_anim, "ease in out", "position y", -animation_displacement)

    top_right_corner_anim = optic.create_animation(animation_duration)
    optic.set_animation_property(top_right_corner_anim, "ease in out", "position x", animation_displacement)
    optic.set_animation_property(top_right_corner_anim, "ease in out", "position y", -animation_displacement)

    bottom_left_corner_anim = optic.create_animation(animation_duration)
    optic.set_animation_property(bottom_left_corner_anim, "ease in out", "position x", -animation_displacement)
    optic.set_animation_property(bottom_left_corner_anim, "ease in out", "position y", animation_displacement)

    bottom_right_corner_anim = optic.create_animation(animation_duration)
    optic.set_animation_property(bottom_right_corner_anim, "ease in out", "position x", animation_displacement)
    optic.set_animation_property(bottom_right_corner_anim, "ease in out", "position y", animation_displacement)

    fade_out_anim = optic.create_animation(duration / 3)
    optic.set_animation_property(fade_out_anim, "linear", "opacity", -255)
    
    -- Set harmony callbacks
    harmony.set_callback("multiplayer event", "on_multiplayer_event")
    harmony.set_callback("multiplayer hit sound", "on_multiplayer_hit_sound")
end

-- Load stuff
on_load()

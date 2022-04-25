-- SPDX-License-Identifier: GPL-3.0-only

clua_version = 2.056

local harmony = require "mods.harmony"
local optic = harmony.optic

-- Get screen size
local screen_width = read_word(0x637CF2)
local screen_height = read_word(0x637CF0)

-- Hitmarker corner sprite
local corner_size = screen_width * (18 / 1280)
optic.create_sprite("corner", "images/hitmarker_corn.png", corner_size, corner_size)

-- Animation params
local anim_duration = 140
local anim_disp = corner_size

-- Top left corner fade in
optic.create_animation("top left in", anim_duration)
optic.set_animation_property("top left in", "ease in out", "position x", -anim_disp)
optic.set_animation_property("top left in", "ease in out", "position y", -anim_disp)

-- Top right corner fade in
optic.create_animation("top right in", anim_duration)
optic.set_animation_property("top right in", "ease in out", "position x", anim_disp)
optic.set_animation_property("top right in", "ease in out", "position y", -anim_disp)

-- Bottom left corner fade in
optic.create_animation("bottom left in", anim_duration)
optic.set_animation_property("bottom left in", "ease in out", "position x", -anim_disp)
optic.set_animation_property("bottom left in", "ease in out", "position y", anim_disp)

-- Bottom right corner fade in
optic.create_animation("bottom right in", anim_duration)
optic.set_animation_property("bottom right in", "ease in out", "position x", anim_disp)
optic.set_animation_property("bottom right in", "ease in out", "position y", anim_disp)

-- Fade out
optic.create_animation("out", anim_duration / 2)
optic.set_animation_property("out", "linear", "opacity", -255)

-- Add hit sound
optic.create_sound("hit", "sounds/hit.wav")

-- Create hitmarker audio engine instance
optic.create_audio_engine("default")

function on_multiplayer_sound(sound)
    if(sound == "ting") then
        -- Render hitmarker
        local pos_x = (screen_width - corner_size) / 2
        local pos_y = (screen_height - corner_size) / 2
        local disp = corner_size * 1.5
        local opacity = 255
        local duration = 140
        optic.render_sprite("corner", pos_x - disp, pos_y - disp, opacity, 180, duration, "top left in", "out")
        optic.render_sprite("corner", pos_x + disp, pos_y - disp, opacity, -90, duration, "top right in", "out")
        optic.render_sprite("corner", pos_x - disp, pos_y + disp, opacity, 90, duration, "bottom left in", "out")
        optic.render_sprite("corner", pos_x + disp, pos_y + disp, opacity, 0, duration, "bottom right in", "out")

        -- Play hit sound
        optic.play_sound("hit", "default", true)
        
        return false
    end

    return true
end

harmony.set_callback("multiplayer sound", "on_multiplayer_sound")

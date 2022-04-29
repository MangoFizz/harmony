-- SPDX-License-Identifier: GPL-3.0-only

clua_version = 2.056

local harmony = require "mods.harmony"
local optic = harmony.optic

-- Screen size
local screen_width = read_word(0x637CF2)
local screen_height = read_word(0x637CF0)

-- Fade in animation
local fade_in_animation = optic.create_animation(200)
optic.set_animation_property(fade_in_animation, "ease in", "position x", 60)
optic.set_animation_property(fade_in_animation, "ease in", "opacity", 255)

-- Fade out animation
local fade_out_animation = optic.create_animation(200)
optic.set_animation_property(fade_out_animation, "ease out", "opacity", -255)

-- Slide animation
local slide_animation = optic.create_animation(300)
optic.set_animation_property(slide_animation, 0.4, 0.0, 0.6, 1.0, "position x", 60)
optic.set_animation_property(slide_animation, 0.4, 0.0, 0.6, 1.0, "position y", 2)

-- Add demo render group
local position_x, position_y = 50, 400
local opacity = 255
local rotation = 180
local duration = 4000
local max_renders = 6
local render_queue = optic.create_render_queue(position_x, position_y, opacity, rotation, duration, max_renders, fade_in_animation, fade_out_animation, slide_animation)

-- Add demo sprite
local sprite_width, sprite_height = 50, 50
local sandia_sprite = optic.create_sprite("images/sandia.jpg", sprite_width, sprite_height)

function on_multiplayer_sound(sound)
    if(sound == "ting") then
        -- Render sandia sprite
        optic.render_sprite(sandia_sprite, render_queue)
    end
    return true
end

harmony.set_callback("multiplayer sound", "on_multiplayer_sound")

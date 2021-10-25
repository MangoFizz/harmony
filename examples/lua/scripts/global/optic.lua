clua_version = 2.056

local harmony = require "mods.harmony"

local optic = harmony.optic

-- Screen size
local screen_width = read_word(0x637CF2)
local screen_height = read_word(0x637CF0)

-- Fade in animation
optic.create_animation("fade in", 200)
optic.set_animation_property("fade in", "ease in", "position x", 60)
optic.set_animation_property("fade in", "ease in", "opacity", 255)

-- Fade out animation
optic.create_animation("fade out", 200)
optic.set_animation_property("fade out", "ease out", "opacity", -255)

-- Slide animation
optic.create_animation("slide", 300)
optic.set_animation_property("slide", 0.4, 0.0, 0.6, 1.0, "position x", 60)
optic.set_animation_property("slide", 0.4, 0.0, 0.6, 1.0, "position y", 2)

-- Add demo render group
optic.create_render_queue("demo", 50, 400, 255, math.random(0, 360), 4000, 6, "fade in", "fade out", "slide")

-- Add demo sprites
optic.create_sprite("sandia", "images/sandia.jpg", 50, 50)
optic.create_sprite("hitmarker", "images/hitmarker.png", 35, 35)

-- Add hit sound
optic.create_sound("hit", "sounds/hit.wav")

-- Create hitmarker playback queue
optic.create_playback_queue("audio queue")

function on_multiplayer_sound(sound)
	if(sound == "ting") then
		-- Render sandia sprite
		optic.render_sprite("sandia", "demo")

		-- Render hitmarker sprite
		optic.render_sprite("hitmarker", (screen_width - 35) / 2, (screen_height - 35) / 2, 255, 0, 200)

		-- Play custom hit sound
		optic.play_sound("hit", "audio queue")
		
		return false
	end

	return true
end

harmony.set_callback("multiplayer sound", "on_multiplayer_sound")

clua_version = 2.056

local harmony = require "mods.harmony"

local optic = harmony.optic

-- Fade in animation
optic.register_animation("fade in", 200)
optic.add_animation_target("fade in", "ease in", "position y", -60)
optic.add_animation_target("fade in", "ease in", "opacity", 255)

-- Fade out animation
optic.register_animation("fade out", 200)
optic.add_animation_target("fade out", "ease out", "opacity", -255)

-- Slide animation
optic.register_animation("slide", 300)
optic.add_animation_target("slide", 0.4, 0.0, 0.6, 1.0, "position x", 60)

-- Add demo render group
optic.create_group("demo", 50, 400, 255, math.random(0, 360), 4000, 0, "fade in", "fade out", "slide")

-- Add sprite
optic.register_sprite("sandia", "images/sandia.jpg", 50, 50)
optic.register_sprite("hitmarker", "images/hitmarker.png", 35, 35, "sounds/hit.wav")

function on_multiplayer_sound(sound)
	if(sound == "ting") then
		-- Sandia sprite
		optic.render_sprite("demo", "sandia")

		-- Hitmarker sprite
		local screen_width = read_word(0x637CF2)
		local screen_height = read_word(0x637CF0)
		optic.render_sprite("hitmarker", (screen_width - 35) / 2, (screen_height - 35) / 2, 255, 0, 200)
	end

	return true
end

harmony.set_callback("multiplayer sound", "on_multiplayer_sound")

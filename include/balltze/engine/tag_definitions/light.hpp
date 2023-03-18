// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__LIGHT_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__LIGHT_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct LightFlags {
		std::uint32_t dynamic : 1;
		std::uint32_t no_specular : 1;
		std::uint32_t dont_light_own_object : 1;
		std::uint32_t supersize_in_first_person : 1;
		std::uint32_t first_person_flashlight : 1;
		std::uint32_t dont_fade_active_camouflage : 1;
	};
	static_assert(sizeof(LightFlags) == sizeof(std::uint32_t));

	struct Light {
		LightFlags flags;
		float radius;
		float radius_modifer[2];
		Angle falloff_angle;
		Angle cutoff_angle;
		float lens_flare_only_radius;
		float cos_falloff_angle;
		float cos_cutoff_angle;
		float unknown_two;
		float sin_cutoff_angle;
		PADDING(8);
		ColorInterpolationFlags interpolation_flags;
		ColorARGB color_lower_bound;
		ColorARGB color_upper_bound;
		PADDING(12);
		TagDependency primary_cube_map;
		PADDING(2);
		WaveFunction texture_animation_function;
		float texture_animation_period;
		TagDependency secondary_cube_map;
		PADDING(2);
		WaveFunction yaw_function;
		float yaw_period;
		PADDING(2);
		WaveFunction roll_function;
		float roll_period;
		PADDING(2);
		WaveFunction pitch_function;
		float pitch_period;
		PADDING(8);
		TagDependency lens_flare;
		PADDING(24);
		float intensity;
		ColorRGB color;
		PADDING(16);
		float duration;
		PADDING(2);
		FunctionType falloff_function;
		PADDING(8);
		PADDING(92);
	};
	static_assert(sizeof(Light) == 352);

}

#endif


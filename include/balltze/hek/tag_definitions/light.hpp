// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__LIGHT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__LIGHT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<LightFlags> flags;
		Memory::BigEndian<float> radius;
		Memory::BigEndian<float> radius_modifer[2];
		Angle falloff_angle;
		Angle cutoff_angle;
		Memory::BigEndian<float> lens_flare_only_radius;
		Memory::BigEndian<float> cos_falloff_angle;
		Memory::BigEndian<float> cos_cutoff_angle;
		Memory::BigEndian<float> unknown_two;
		Memory::BigEndian<float> sin_cutoff_angle;
		PADDING(8);
		Memory::BigEndian<ColorInterpolationFlags> interpolation_flags;
		ColorARGB color_lower_bound;
		ColorARGB color_upper_bound;
		PADDING(12);
		TagDependency primary_cube_map;
		PADDING(2);
		Memory::BigEndian<WaveFunction> texture_animation_function;
		Memory::BigEndian<float> texture_animation_period;
		TagDependency secondary_cube_map;
		PADDING(2);
		Memory::BigEndian<WaveFunction> yaw_function;
		Memory::BigEndian<float> yaw_period;
		PADDING(2);
		Memory::BigEndian<WaveFunction> roll_function;
		Memory::BigEndian<float> roll_period;
		PADDING(2);
		Memory::BigEndian<WaveFunction> pitch_function;
		Memory::BigEndian<float> pitch_period;
		PADDING(8);
		TagDependency lens_flare;
		PADDING(24);
		Memory::BigEndian<float> intensity;
		ColorRGB color;
		PADDING(16);
		Memory::BigEndian<float> duration;
		PADDING(2);
		Memory::BigEndian<FunctionType> falloff_function;
		PADDING(8);
		PADDING(92);
	};
	static_assert(sizeof(Light) == 352);

}

#endif


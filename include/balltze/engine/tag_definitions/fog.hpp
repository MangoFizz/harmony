// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__FOG_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__FOG_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct FogFlags {
		std::uint32_t is_water : 1;
		std::uint32_t atmosphere_dominant : 1;
		std::uint32_t fog_screen_only : 1;
	};
	static_assert(sizeof(FogFlags) == sizeof(std::uint32_t));

	struct FogScreenFlags {
		std::uint16_t no_environment_multipass : 1;
		std::uint16_t no_model_multipass : 1;
		std::uint16_t no_texture_based_falloff : 1;
	};
	static_assert(sizeof(FogScreenFlags) == sizeof(std::uint16_t));

	struct Fog {
		FogFlags flags;
		PADDING(4);
		PADDING(76);
		PADDING(4);
		Fraction maximum_density;
		PADDING(4);
		float opaque_distance;
		PADDING(4);
		float opaque_depth;
		PADDING(8);
		float distance_to_water_plane;
		ColorRGB color;
		FogScreenFlags flags_1;
		std::int16_t layer_count;
		float distance_gradient[2];
		Fraction density_gradient[2];
		float start_distance_from_fog_plane;
		PADDING(4);
		ColorARGBInt screen_layers_color;
		Fraction rotation_multiplier;
		Fraction strafing_multiplier;
		Fraction zoom_multiplier;
		PADDING(8);
		float map_scale;
		TagDependency map;
		float animation_period;
		PADDING(4);
		float wind_velocity[2];
		float wind_period[2];
		Fraction wind_acceleration_weight;
		Fraction wind_perpendicular_weight;
		PADDING(8);
		TagDependency background_sound;
		TagDependency sound_environment;
		PADDING(120);
	};
	static_assert(sizeof(Fog) == 396);

}

#endif


// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__WEATHER_PARTICLE_SYSTEM_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__WEATHER_PARTICLE_SYSTEM_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "particle.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class WeatherParticleSystemRenderDirectionSource : std::uint16_t {
		FROM_VELOCITY = 0,
		FROM_ACCELERATION,
	};

	struct WeatherParticleSystemParticleTypeFlags {
		std::uint32_t interpolate_colors_in_hsv : 1;
		std::uint32_t along_long_hue_path : 1;
		std::uint32_t random_rotation : 1;
	};
	static_assert(sizeof(WeatherParticleSystemParticleTypeFlags) == sizeof(std::uint32_t));

	struct WeatherParticleSystemParticleType {
		TagString name;
		WeatherParticleSystemParticleTypeFlags flags;
		float fade_in_start_distance;
		float fade_in_end_distance;
		float fade_out_start_distance;
		float fade_out_end_distance;
		float fade_in_start_height;
		float fade_in_end_height;
		float fade_out_start_height;
		float fade_out_end_height;
		PADDING(96);
		float particle_count[2];
		TagDependency physics;
		PADDING(16);
		float acceleration_magnitude[2];
		Fraction acceleration_turning_rate;
		float acceleration_change_rate;
		PADDING(32);
		float particle_radius[2];
		float animation_rate[2];
		Angle rotation_rate[2];
		PADDING(32);
		ColorARGB color_lower_bound;
		ColorARGB color_upper_bound;
		float sprite_size;
		PADDING(60);
		TagDependency sprite_bitmap;
		ParticleOrientation render_mode;
		WeatherParticleSystemRenderDirectionSource render_direction_source;
		PADDING(36);
		std::uint32_t not_broken;
		ParticleShaderFlags shader_flags;
		FramebufferBlendFunction framebuffer_blend_function;
		FramebufferFadeMode framebuffer_fade_mode;
		IsUnfilteredFlag map_flags;
		PADDING(28);
		TagDependency bitmap;
		ParticleAnchor anchor;
		IsUnfilteredFlag flags_1;
		FunctionOut u_animation_source;
		WaveFunction u_animation_function;
		float u_animation_period;
		float u_animation_phase;
		float u_animation_scale;
		FunctionOut v_animation_source;
		WaveFunction v_animation_function;
		float v_animation_period;
		float v_animation_phase;
		float v_animation_scale;
		FunctionOut rotation_animation_source;
		WaveFunction rotation_animation_function;
		float rotation_animation_period;
		float rotation_animation_phase;
		Angle rotation_animation_scale;
		Point2D rotation_animation_center;
		PADDING(4);
		float zsprite_radius_scale;
		PADDING(20);
	};
	static_assert(sizeof(WeatherParticleSystemParticleType) == 604);

	struct WeatherParticleSystem {
		IsUnusedFlag flags;
		PADDING(32);
		TagReflexive<WeatherParticleSystemParticleType> particle_types;
	};
	static_assert(sizeof(WeatherParticleSystem) == 48);

}

#endif


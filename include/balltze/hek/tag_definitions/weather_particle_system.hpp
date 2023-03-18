// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__WEATHER_PARTICLE_SYSTEM_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__WEATHER_PARTICLE_SYSTEM_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "particle.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<WeatherParticleSystemParticleTypeFlags> flags;
		Memory::BigEndian<float> fade_in_start_distance;
		Memory::BigEndian<float> fade_in_end_distance;
		Memory::BigEndian<float> fade_out_start_distance;
		Memory::BigEndian<float> fade_out_end_distance;
		Memory::BigEndian<float> fade_in_start_height;
		Memory::BigEndian<float> fade_in_end_height;
		Memory::BigEndian<float> fade_out_start_height;
		Memory::BigEndian<float> fade_out_end_height;
		PADDING(96);
		Memory::BigEndian<float> particle_count[2];
		TagDependency physics;
		PADDING(16);
		Memory::BigEndian<float> acceleration_magnitude[2];
		Fraction acceleration_turning_rate;
		Memory::BigEndian<float> acceleration_change_rate;
		PADDING(32);
		Memory::BigEndian<float> particle_radius[2];
		Memory::BigEndian<float> animation_rate[2];
		Angle rotation_rate[2];
		PADDING(32);
		ColorARGB color_lower_bound;
		ColorARGB color_upper_bound;
		Memory::BigEndian<float> sprite_size;
		PADDING(60);
		TagDependency sprite_bitmap;
		Memory::BigEndian<ParticleOrientation> render_mode;
		Memory::BigEndian<WeatherParticleSystemRenderDirectionSource> render_direction_source;
		PADDING(36);
		Memory::BigEndian<std::uint32_t> not_broken;
		Memory::BigEndian<ParticleShaderFlags> shader_flags;
		Memory::BigEndian<FramebufferBlendFunction> framebuffer_blend_function;
		Memory::BigEndian<FramebufferFadeMode> framebuffer_fade_mode;
		Memory::BigEndian<IsUnfilteredFlag> map_flags;
		PADDING(28);
		TagDependency bitmap;
		Memory::BigEndian<ParticleAnchor> anchor;
		Memory::BigEndian<IsUnfilteredFlag> flags_1;
		Memory::BigEndian<FunctionOut> u_animation_source;
		Memory::BigEndian<WaveFunction> u_animation_function;
		Memory::BigEndian<float> u_animation_period;
		Memory::BigEndian<float> u_animation_phase;
		Memory::BigEndian<float> u_animation_scale;
		Memory::BigEndian<FunctionOut> v_animation_source;
		Memory::BigEndian<WaveFunction> v_animation_function;
		Memory::BigEndian<float> v_animation_period;
		Memory::BigEndian<float> v_animation_phase;
		Memory::BigEndian<float> v_animation_scale;
		Memory::BigEndian<FunctionOut> rotation_animation_source;
		Memory::BigEndian<WaveFunction> rotation_animation_function;
		Memory::BigEndian<float> rotation_animation_period;
		Memory::BigEndian<float> rotation_animation_phase;
		Angle rotation_animation_scale;
		Point2D rotation_animation_center;
		PADDING(4);
		Memory::BigEndian<float> zsprite_radius_scale;
		PADDING(20);
	};
	static_assert(sizeof(WeatherParticleSystemParticleType) == 604);

	struct WeatherParticleSystem {
		Memory::BigEndian<IsUnusedFlag> flags;
		PADDING(32);
		TagReflexive<WeatherParticleSystemParticleType> particle_types;
	};
	static_assert(sizeof(WeatherParticleSystem) == 48);

}

#endif


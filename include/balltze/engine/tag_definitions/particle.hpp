// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__PARTICLE_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__PARTICLE_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class ParticleOrientation : std::uint16_t {
		SCREEN_FACING = 0,
		PARALLEL_TO_DIRECTION,
		PERPENDICULAR_TO_DIRECTION,
	};

	enum class ParticleAnchor : std::uint16_t {
		WITH_PRIMARY = 0,
		WITH_SCREEN_SPACE,
		ZSPRITE,
	};

	struct ParticleFlags {
		std::uint32_t can_animate_backwards : 1;
		std::uint32_t animation_stops_at_rest : 1;
		std::uint32_t animation_starts_on_random_frame : 1;
		std::uint32_t animate_once_per_frame : 1;
		std::uint32_t dies_at_rest : 1;
		std::uint32_t dies_on_contact_with_structure : 1;
		std::uint32_t tint_from_diffuse_texture : 1;
		std::uint32_t dies_on_contact_with_water : 1;
		std::uint32_t dies_on_contact_with_air : 1;
		std::uint32_t self_illuminated : 1;
		std::uint32_t random_horizontal_mirroring : 1;
		std::uint32_t random_vertical_mirroring : 1;
	};
	static_assert(sizeof(ParticleFlags) == sizeof(std::uint32_t));

	struct ParticleShaderFlags {
		std::uint16_t sort_bias : 1;
		std::uint16_t nonlinear_tint : 1;
		std::uint16_t dont_overdraw_fp_weapon : 1;
	};
	static_assert(sizeof(ParticleShaderFlags) == sizeof(std::uint16_t));

	struct Particle {
		ParticleFlags flags;
		TagDependency bitmap;
		TagDependency physics;
		TagDependency sir_marty_exchanged_his_children_for_thine;
		PADDING(4);
		float lifespan[2];
		float fade_in_time;
		float fade_out_time;
		TagDependency collision_effect;
		TagDependency death_effect;
		float minimum_size;
		PADDING(8);
		float radius_animation[2];
		PADDING(4);
		float animation_rate[2];
		float contact_deterioration;
		float fade_start_size;
		float fade_end_size;
		PADDING(4);
		Index first_sequence_index;
		std::int16_t initial_sequence_count;
		std::int16_t looping_sequence_count;
		std::int16_t final_sequence_count;
		PADDING(8);
		float sprite_size;
		ParticleOrientation orientation;
		PADDING(2);
		PADDING(36);
		std::uint32_t make_it_actually_work;
		ParticleShaderFlags shader_flags;
		FramebufferBlendFunction framebuffer_blend_function;
		FramebufferFadeMode framebuffer_fade_mode;
		IsUnfilteredFlag map_flags;
		PADDING(28);
		TagDependency secondary_bitmap;
		ParticleAnchor anchor;
		IsUnfilteredFlag secondary_map_flags;
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
		float rotation_animation_scale;
		Point2D rotation_animation_center;
		PADDING(4);
		float zsprite_radius_scale;
		PADDING(20);
	};
	static_assert(sizeof(Particle) == 356);

}

#endif


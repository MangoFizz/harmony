// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__PARTICLE_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__PARTICLE_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<ParticleFlags> flags;
		TagDependency bitmap;
		TagDependency physics;
		TagDependency sir_marty_exchanged_his_children_for_thine;
		PADDING(4);
		Memory::BigEndian<float> lifespan[2];
		Memory::BigEndian<float> fade_in_time;
		Memory::BigEndian<float> fade_out_time;
		TagDependency collision_effect;
		TagDependency death_effect;
		Memory::BigEndian<float> minimum_size;
		PADDING(8);
		Memory::BigEndian<float> radius_animation[2];
		PADDING(4);
		Memory::BigEndian<float> animation_rate[2];
		Memory::BigEndian<float> contact_deterioration;
		Memory::BigEndian<float> fade_start_size;
		Memory::BigEndian<float> fade_end_size;
		PADDING(4);
		Index first_sequence_index;
		Memory::BigEndian<std::int16_t> initial_sequence_count;
		Memory::BigEndian<std::int16_t> looping_sequence_count;
		Memory::BigEndian<std::int16_t> final_sequence_count;
		PADDING(8);
		Memory::BigEndian<float> sprite_size;
		Memory::BigEndian<ParticleOrientation> orientation;
		PADDING(2);
		PADDING(36);
		Memory::BigEndian<std::uint32_t> make_it_actually_work;
		Memory::BigEndian<ParticleShaderFlags> shader_flags;
		Memory::BigEndian<FramebufferBlendFunction> framebuffer_blend_function;
		Memory::BigEndian<FramebufferFadeMode> framebuffer_fade_mode;
		Memory::BigEndian<IsUnfilteredFlag> map_flags;
		PADDING(28);
		TagDependency secondary_bitmap;
		Memory::BigEndian<ParticleAnchor> anchor;
		Memory::BigEndian<IsUnfilteredFlag> secondary_map_flags;
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
		Memory::BigEndian<float> rotation_animation_scale;
		Point2D rotation_animation_center;
		PADDING(4);
		Memory::BigEndian<float> zsprite_radius_scale;
		PADDING(20);
	};
	static_assert(sizeof(Particle) == 356);

}

#endif


// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__PARTICLE_SYSTEM_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__PARTICLE_SYSTEM_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "particle.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class ParticleSystemParticleCreationPhysics : std::uint16_t {
		DEFAULT = 0,
		EXPLOSION,
		JET,
	};

	enum class ParticleSystemParticleUpdatePhysics : std::uint16_t {
		DEFAULT = 0,
	};

	enum class ParticleSystemComplexSpriteRenderModes : std::uint16_t {
		SIMPLE = 0,
		ROTATIONAL,
	};

	enum class ParticleSystemSystemUpdatePhysics : std::uint16_t {
		DEFAULT = 0,
		EXPLOSION,
	};

	struct ParticleSystemTypeFlags {
		std::uint32_t type_states_loop : 1;
		std::uint32_t forward_backward : 1;
		std::uint32_t particle_states_loop : 1;
		std::uint32_t forward_backward_1 : 1;
		std::uint32_t particles_die_in_water : 1;
		std::uint32_t particles_die_in_air : 1;
		std::uint32_t particles_die_on_ground : 1;
		std::uint32_t rotational_sprites_animate_sideways : 1;
		std::uint32_t disabled : 1;
		std::uint32_t tint_by_effect_color : 1;
		std::uint32_t initial_count_scales_with_effect : 1;
		std::uint32_t minimum_count_scales_with_effect : 1;
		std::uint32_t creation_rate_scales_with_effect : 1;
		std::uint32_t scale_scales_with_effect : 1;
		std::uint32_t animation_rate_scales_with_effect : 1;
		std::uint32_t rotation_rate_scales_with_effect : 1;
		std::uint32_t do_not_draw_in_first_person : 1;
		std::uint32_t do_not_draw_in_third_person : 1;
	};
	static_assert(sizeof(ParticleSystemTypeFlags) == sizeof(std::uint32_t));

	struct ParticleSystemPhysicsConstant {
		float k;
	};
	static_assert(sizeof(ParticleSystemPhysicsConstant) == 4);

	struct ParticleSystemTypeStates {
		TagString name;
		float duration_bounds[2];
		float transition_time_bounds[2];
		PADDING(4);
		float scale_multiplier;
		float animation_rate_multiplier;
		float rotation_rate_multiplier;
		ColorARGB color_multiplier;
		float radius_multiplier;
		float minimum_particle_count;
		float particle_creation_rate;
		PADDING(84);
		ParticleSystemParticleCreationPhysics particle_creation_physics;
		ParticleSystemParticleUpdatePhysics particle_update_physics;
		TagReflexive<ParticleSystemPhysicsConstant> physics_constants;
	};
	static_assert(sizeof(ParticleSystemTypeStates) == 192);

	struct ParticleSystemTypeParticleState {
		TagString name;
		float duration_bounds[2];
		float transition_time_bounds[2];
		TagDependency bitmaps;
		Index sequence_index;
		PADDING(2);
		PADDING(4);
		float scale[2];
		float animation_rate[2];
		Angle rotation_rate[2];
		ColorARGB color_1;
		ColorARGB color_2;
		float radius_multiplier;
		TagDependency point_physics;
		PADDING(36);
		PADDING(36);
		std::uint32_t unknown_int;
		ParticleShaderFlags shader_flags;
		FramebufferBlendFunction framebuffer_blend_function;
		FramebufferFadeMode framebuffer_fade_mode;
		IsUnfilteredFlag map_flags;
		PADDING(28);
		TagDependency secondary_map_bitmap;
		ParticleAnchor anchor;
		IsUnfilteredFlag flags;
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
		TagReflexive<ParticleSystemPhysicsConstant> physics_constants;
	};
	static_assert(sizeof(ParticleSystemTypeParticleState) == 376);

	struct ParticleSystemType {
		TagString name;
		ParticleSystemTypeFlags flags;
		std::uint16_t initial_particle_count;
		PADDING(2);
		ParticleSystemComplexSpriteRenderModes complex_sprite_render_modes;
		PADDING(2);
		float radius;
		PADDING(36);
		ParticleSystemParticleCreationPhysics particle_creation_physics;
		PADDING(2);
		IsUnusedFlag physics_flags;
		TagReflexive<ParticleSystemPhysicsConstant> physics_constants;
		TagReflexive<ParticleSystemTypeStates> states;
		TagReflexive<ParticleSystemTypeParticleState> particle_states;
	};
	static_assert(sizeof(ParticleSystemType) == 128);

	struct ParticleSystem {
		PADDING(4);
		PADDING(52);
		TagDependency point_physics;
		ParticleSystemSystemUpdatePhysics system_update_physics;
		PADDING(2);
		IsUnusedFlag physics_flags;
		TagReflexive<ParticleSystemPhysicsConstant> physics_constants;
		TagReflexive<ParticleSystemType> particle_types;
	};
	static_assert(sizeof(ParticleSystem) == 104);

}

#endif


// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__PROJECTILE_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__PROJECTILE_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "object.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class ProjectileResponse : std::uint16_t {
		DISAPPEAR = 0,
		DETONATE,
		REFLECT,
		OVERPENETRATE,
		ATTACH,
	};

	enum class ProjectileScaleEffectsBy : std::uint16_t {
		DAMAGE = 0,
		ANGLE,
	};

	enum class ProjectileDetonationTimerStarts : std::uint16_t {
		IMMEDIATELY = 0,
		AFTER_FIRST_BOUNCE,
		WHEN_AT_REST,
	};

	enum class ProjectileFunctionIn : std::uint16_t {
		NONE = 0,
		RANGE_REMAINING,
		TIME_REMAINING,
		TRACER,
	};

	struct ProjectileFlags {
		std::uint32_t oriented_along_velocity : 1;
		std::uint32_t ai_must_use_ballistic_aiming : 1;
		std::uint32_t detonation_max_time_if_attached : 1;
		std::uint32_t has_super_combining_explosion : 1;
		std::uint32_t combine_initial_velocity_with_parent_velocity : 1;
		std::uint32_t random_attached_detonation_time : 1;
		std::uint32_t minimum_unattached_detonation_time : 1;
	};
	static_assert(sizeof(ProjectileFlags) == sizeof(std::uint32_t));

	struct ProjectileMaterialResponseFlags {
		std::uint16_t cannot_be_overpenetrated : 1;
	};
	static_assert(sizeof(ProjectileMaterialResponseFlags) == sizeof(std::uint16_t));

	struct ProjectileMaterialResponsePotentialFlags {
		std::uint16_t only_against_units : 1;
		std::uint16_t never_against_units : 1;
	};
	static_assert(sizeof(ProjectileMaterialResponsePotentialFlags) == sizeof(std::uint16_t));

	struct ProjectileMaterialResponse {
		Memory::BigEndian<ProjectileMaterialResponseFlags> flags;
		Memory::BigEndian<ProjectileResponse> default_response;
		TagDependency default_effect;
		PADDING(16);
		Memory::BigEndian<ProjectileResponse> potential_response;
		Memory::BigEndian<ProjectileMaterialResponsePotentialFlags> potential_flags;
		Fraction potential_skip_fraction;
		Angle potential_between[2];
		Memory::BigEndian<float> potential_and[2];
		TagDependency potential_effect;
		PADDING(16);
		Memory::BigEndian<ProjectileScaleEffectsBy> scale_effects_by;
		PADDING(2);
		Angle angular_noise;
		Memory::BigEndian<float> velocity_noise;
		TagDependency detonation_effect;
		PADDING(24);
		Memory::BigEndian<float> initial_friction;
		Memory::BigEndian<float> maximum_distance;
		Memory::BigEndian<float> parallel_friction;
		Memory::BigEndian<float> perpendicular_friction;
	};
	static_assert(sizeof(ProjectileMaterialResponse) == 160);

	struct Projectile : public Object {
		Memory::BigEndian<ProjectileFlags> projectile_flags;
		Memory::BigEndian<ProjectileDetonationTimerStarts> detonation_timer_starts;
		Memory::BigEndian<ObjectNoise> impact_noise;
		Memory::BigEndian<ProjectileFunctionIn> projectile_a_in;
		Memory::BigEndian<ProjectileFunctionIn> projectile_b_in;
		Memory::BigEndian<ProjectileFunctionIn> projectile_c_in;
		Memory::BigEndian<ProjectileFunctionIn> projectile_d_in;
		TagDependency super_detonation;
		Memory::BigEndian<float> ai_perception_radius;
		Memory::BigEndian<float> collision_radius;
		Memory::BigEndian<float> arming_time;
		Memory::BigEndian<float> danger_radius;
		TagDependency effect;
		Memory::BigEndian<float> timer[2];
		Memory::BigEndian<float> minimum_velocity;
		Memory::BigEndian<float> maximum_range;
		Memory::BigEndian<float> air_gravity_scale;
		Memory::BigEndian<float> air_damage_range[2];
		Memory::BigEndian<float> water_gravity_scale;
		Memory::BigEndian<float> water_damage_range[2];
		Memory::BigEndian<float> initial_velocity;
		Memory::BigEndian<float> final_velocity;
		Angle guided_angular_velocity;
		Memory::BigEndian<ObjectNoise> detonation_noise;
		PADDING(2);
		TagDependency detonation_started;
		TagDependency flyby_sound;
		TagDependency attached_detonation_damage;
		TagDependency impact_damage;
		PADDING(12);
		TagReflexive<ProjectileMaterialResponse> projectile_material_response;
	};
	static_assert(sizeof(Projectile) == 588);

}

#endif


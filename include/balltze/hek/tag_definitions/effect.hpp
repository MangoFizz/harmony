// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__EFFECT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__EFFECT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class EffectCreateIn : std::uint16_t {
		ANY_ENVIRONMENT = 0,
		AIR_ONLY,
		WATER_ONLY,
		SPACE_ONLY,
	};

	enum class EffectViolenceMode : std::uint16_t {
		EITHER_MODE = 0,
		VIOLENT_MODE_ONLY,
		NONVIOLENT_MODE_ONLY,
	};

	enum class EffectCreate : std::uint16_t {
		INDEPENDENT_OF_CAMERA_MODE = 0,
		ONLY_IN_FIRST_PERSON,
		ONLY_IN_THIRD_PERSON,
		IN_FIRST_PERSON_IF_POSSIBLE,
	};

	enum class EffectDistributionFunction : std::uint16_t {
		START = 0,
		END,
		CONSTANT,
		BUILDUP,
		FALLOFF,
		BUILDUP_AND_FALLOFF,
	};

	struct EffectPartFlags {
		std::uint16_t face_down_regardless_of_location_decals : 1;
		std::uint16_t unused : 1;
		std::uint16_t make_effect_work : 1;
	};
	static_assert(sizeof(EffectPartFlags) == sizeof(std::uint16_t));

	struct EffectPartScalesValues {
		std::uint32_t velocity : 1;
		std::uint32_t velocity_delta : 1;
		std::uint32_t velocity_cone_angle : 1;
		std::uint32_t angular_velocity : 1;
		std::uint32_t angular_velocity_delta : 1;
		std::uint32_t type_specific_scale : 1;
	};
	static_assert(sizeof(EffectPartScalesValues) == sizeof(std::uint32_t));

	struct EffectParticleFlags {
		std::uint32_t stay_attached_to_marker : 1;
		std::uint32_t random_initial_angle : 1;
		std::uint32_t tint_from_object_color : 1;
		std::uint32_t interpolate_tint_as_hsv : 1;
		std::uint32_t across_the_long_hue_path : 1;
	};
	static_assert(sizeof(EffectParticleFlags) == sizeof(std::uint32_t));

	struct EffectParticleScalesValues {
		std::uint32_t velocity : 1;
		std::uint32_t velocity_delta : 1;
		std::uint32_t velocity_cone_angle : 1;
		std::uint32_t angular_velocity : 1;
		std::uint32_t angular_velocity_delta : 1;
		std::uint32_t count : 1;
		std::uint32_t count_delta : 1;
		std::uint32_t distribution_radius : 1;
		std::uint32_t distribution_radius_delta : 1;
		std::uint32_t particle_radius : 1;
		std::uint32_t particle_radius_delta : 1;
		std::uint32_t tint : 1;
	};
	static_assert(sizeof(EffectParticleScalesValues) == sizeof(std::uint32_t));

	struct EffectFlags {
		std::uint32_t deleted_when_attachment_deactivates : 1;
		std::uint32_t must_be_deterministic_xbox : 1;
		std::uint32_t must_be_deterministic_pc : 1;
		std::uint32_t disabled_in_anniversary_by_blood_setting : 1;
	};
	static_assert(sizeof(EffectFlags) == sizeof(std::uint32_t));

	struct EffectLocation {
		TagString marker_name;
	};
	static_assert(sizeof(EffectLocation) == 32);

	struct EffectPart {
		Memory::BigEndian<EffectCreateIn> create_in;
		Memory::BigEndian<EffectViolenceMode> violence_mode;
		Index location;
		Memory::BigEndian<EffectPartFlags> flags;
		PADDING(12);
		Memory::BigEndian<std::uint32_t> type_class;
		TagDependency type;
		PADDING(24);
		Memory::BigEndian<float> velocity_bounds[2];
		Angle velocity_cone_angle;
		Angle angular_velocity_bounds[2];
		Memory::BigEndian<float> radius_modifier_bounds[2];
		PADDING(4);
		Memory::BigEndian<EffectPartScalesValues> a_scales_values;
		Memory::BigEndian<EffectPartScalesValues> b_scales_values;
	};
	static_assert(sizeof(EffectPart) == 104);

	struct EffectParticle {
		Memory::BigEndian<EffectCreateIn> create_in;
		Memory::BigEndian<EffectViolenceMode> violence_mode;
		Memory::BigEndian<EffectCreate> create;
		PADDING(2);
		Index location;
		PADDING(2);
		Euler2D relative_direction;
		Point3D relative_offset;
		Vector3D relative_direction_vector;
		PADDING(40);
		TagDependency particle_type;
		Memory::BigEndian<EffectParticleFlags> flags;
		Memory::BigEndian<EffectDistributionFunction> distribution_function;
		PADDING(2);
		Memory::BigEndian<std::int16_t> count[2];
		Memory::BigEndian<float> distribution_radius[2];
		PADDING(12);
		Memory::BigEndian<float> velocity[2];
		Angle velocity_cone_angle;
		Angle angular_velocity[2];
		PADDING(8);
		Memory::BigEndian<float> radius[2];
		PADDING(8);
		ColorARGB tint_lower_bound;
		ColorARGB tint_upper_bound;
		PADDING(16);
		Memory::BigEndian<EffectParticleScalesValues> a_scales_values;
		Memory::BigEndian<EffectParticleScalesValues> b_scales_values;
	};
	static_assert(sizeof(EffectParticle) == 232);

	struct EffectEvent {
		PADDING(4);
		Fraction skip_fraction;
		Memory::BigEndian<float> delay_bounds[2];
		Memory::BigEndian<float> duration_bounds[2];
		PADDING(20);
		TagReflexive<EffectPart> parts;
		TagReflexive<EffectParticle> particles;
	};
	static_assert(sizeof(EffectEvent) == 68);

	struct Effect {
		Memory::BigEndian<EffectFlags> flags;
		Index loop_start_event;
		Index loop_stop_event;
		Memory::BigEndian<float> maximum_damage_radius;
		PADDING(28);
		TagReflexive<EffectLocation> locations;
		TagReflexive<EffectEvent> events;
	};
	static_assert(sizeof(Effect) == 64);

}

#endif


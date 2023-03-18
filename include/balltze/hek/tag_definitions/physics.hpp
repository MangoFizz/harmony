// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__PHYSICS_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__PHYSICS_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class PhysicsFrictionType : std::uint16_t {
		POINT = 0,
		FORWARD,
		LEFT,
		UP,
	};

	struct PhysicsPoweredMassPointFlags {
		std::uint32_t ground_friction : 1;
		std::uint32_t water_friction : 1;
		std::uint32_t air_friction : 1;
		std::uint32_t water_lift : 1;
		std::uint32_t air_lift : 1;
		std::uint32_t thrust : 1;
		std::uint32_t antigrav : 1;
	};
	static_assert(sizeof(PhysicsPoweredMassPointFlags) == sizeof(std::uint32_t));

	struct PhysicsMassPointFlags {
		std::uint32_t metallic : 1;
	};
	static_assert(sizeof(PhysicsMassPointFlags) == sizeof(std::uint32_t));

	struct PhysicsInertialMatrix {
		Matrix matrix;
	};
	static_assert(sizeof(PhysicsInertialMatrix) == 36);

	struct PhysicsPoweredMassPoint {
		TagString name;
		Memory::BigEndian<PhysicsPoweredMassPointFlags> flags;
		Memory::BigEndian<float> antigrav_strength;
		Memory::BigEndian<float> antigrav_offset;
		Memory::BigEndian<float> antigrav_height;
		Memory::BigEndian<float> antigrav_damp_fraction;
		Memory::BigEndian<float> antigrav_normal_k1;
		Memory::BigEndian<float> antigrav_normal_k0;
		PADDING(68);
	};
	static_assert(sizeof(PhysicsPoweredMassPoint) == 128);

	struct PhysicsMassPoint {
		TagString name;
		Memory::BigEndian<std::int16_t> powered_mass_point;
		Memory::BigEndian<std::int16_t> model_node;
		Memory::BigEndian<PhysicsMassPointFlags> flags;
		Memory::BigEndian<float> relative_mass;
		Memory::BigEndian<float> mass;
		Memory::BigEndian<float> relative_density;
		Memory::BigEndian<float> density;
		Point3D position;
		Vector3D forward;
		Vector3D up;
		Memory::BigEndian<PhysicsFrictionType> friction_type;
		PADDING(2);
		Memory::BigEndian<float> friction_parallel_scale;
		Memory::BigEndian<float> friction_perpendicular_scale;
		Memory::BigEndian<float> radius;
		PADDING(20);
	};
	static_assert(sizeof(PhysicsMassPoint) == 128);

	struct Physics {
		Memory::BigEndian<float> radius;
		Fraction moment_scale;
		Memory::BigEndian<float> mass;
		Point3D center_of_mass;
		Memory::BigEndian<float> density;
		Memory::BigEndian<float> gravity_scale;
		Memory::BigEndian<float> ground_friction;
		Memory::BigEndian<float> ground_depth;
		Fraction ground_damp_fraction;
		Memory::BigEndian<float> ground_normal_k1;
		Memory::BigEndian<float> ground_normal_k0;
		PADDING(4);
		Memory::BigEndian<float> water_friction;
		Memory::BigEndian<float> water_depth;
		Memory::BigEndian<float> water_density;
		PADDING(4);
		Fraction air_friction;
		PADDING(4);
		Memory::BigEndian<float> xx_moment;
		Memory::BigEndian<float> yy_moment;
		Memory::BigEndian<float> zz_moment;
		TagReflexive<PhysicsInertialMatrix> inertial_matrix_and_inverse;
		TagReflexive<PhysicsPoweredMassPoint> powered_mass_points;
		TagReflexive<PhysicsMassPoint> mass_points;
	};
	static_assert(sizeof(Physics) == 128);

}

#endif


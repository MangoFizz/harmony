// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__POINT_PHYSICS_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__POINT_PHYSICS_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct PointPhysicsFlags {
		std::uint32_t flamethrower_particle_collision : 1;
		std::uint32_t collides_with_structures : 1;
		std::uint32_t collides_with_water_surface : 1;
		std::uint32_t uses_simple_wind : 1;
		std::uint32_t uses_damped_wind : 1;
		std::uint32_t no_gravity : 1;
	};
	static_assert(sizeof(PointPhysicsFlags) == sizeof(std::uint32_t));

	struct PointPhysics {
		Memory::BigEndian<PointPhysicsFlags> flags;
		Memory::BigEndian<float> unknown_constant;
		Memory::BigEndian<float> water_gravity_scale;
		Memory::BigEndian<float> air_gravity_scale;
		PADDING(16);
		Memory::BigEndian<float> density;
		Memory::BigEndian<float> air_friction;
		Memory::BigEndian<float> water_friction;
		Memory::BigEndian<float> surface_friction;
		Memory::BigEndian<float> elasticity;
		PADDING(12);
	};
	static_assert(sizeof(PointPhysics) == 64);

}

#endif


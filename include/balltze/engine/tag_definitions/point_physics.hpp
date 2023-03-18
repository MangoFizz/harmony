// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__POINT_PHYSICS_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__POINT_PHYSICS_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
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
		PointPhysicsFlags flags;
		float unknown_constant;
		float water_gravity_scale;
		float air_gravity_scale;
		PADDING(16);
		float density;
		float air_friction;
		float water_friction;
		float surface_friction;
		float elasticity;
		PADDING(12);
	};
	static_assert(sizeof(PointPhysics) == 64);

}

#endif


// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__VEHICLE_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__VEHICLE_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "unit.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class VehicleType : std::uint16_t {
		HUMAN_TANK = 0,
		HUMAN_JEEP,
		HUMAN_BOAT,
		HUMAN_PLANE,
		ALIEN_SCOUT,
		ALIEN_FIGHTER,
		TURRET,
	};

	enum class VehicleFunctionIn : std::uint16_t {
		NONE = 0,
		SPEED_ABSOLUTE,
		SPEED_FORWARD,
		SPEED_BACKWARD,
		SLIDE_ABSOLUTE,
		SLIDE_LEFT,
		SLIDE_RIGHT,
		SPEED_SLIDE_MAXIMUM,
		TURN_ABSOLUTE,
		TURN_LEFT,
		TURN_RIGHT,
		CROUCH,
		JUMP,
		WALK,
		VELOCITY_AIR,
		VELOCITY_WATER,
		VELOCITY_GROUND,
		VELOCITY_FORWARD,
		VELOCITY_LEFT,
		VELOCITY_UP,
		LEFT_TREAD_POSITION,
		RIGHT_TREAD_POSITION,
		LEFT_TREAD_VELOCITY,
		RIGHT_TREAD_VELOCITY,
		FRONT_LEFT_TIRE_POSITION,
		FRONT_RIGHT_TIRE_POSITION,
		BACK_LEFT_TIRE_POSITION,
		BACK_RIGHT_TIRE_POSITION,
		FRONT_LEFT_TIRE_VELOCITY,
		FRONT_RIGHT_TIRE_VELOCITY,
		BACK_LEFT_TIRE_VELOCITY,
		BACK_RIGHT_TIRE_VELOCITY,
		WINGTIP_CONTRAIL,
		HOVER,
		THRUST,
		ENGINE_HACK,
		WINGTIP_CONTRAIL_NEW,
	};

	struct VehicleFlags {
		std::uint32_t speed_wakes_physics : 1;
		std::uint32_t turn_wakes_physics : 1;
		std::uint32_t driver_power_wakes_physics : 1;
		std::uint32_t gunner_power_wakes_physics : 1;
		std::uint32_t control_opposite_speed_sets_brake : 1;
		std::uint32_t slide_wakes_physics : 1;
		std::uint32_t kills_riders_at_terminal_velocity : 1;
		std::uint32_t causes_collision_damage : 1;
		std::uint32_t ai_weapon_cannot_rotate : 1;
		std::uint32_t ai_does_not_require_driver : 1;
		std::uint32_t ai_unused : 1;
		std::uint32_t ai_driver_enable : 1;
		std::uint32_t ai_driver_flying : 1;
		std::uint32_t ai_driver_can_sidestep : 1;
		std::uint32_t ai_driver_hovering : 1;
		std::uint32_t vehicle_steers_directly : 1;
		std::uint32_t unused : 1;
		std::uint32_t has_ebrake : 1;
		std::uint32_t noncombat_vehicle : 1;
		std::uint32_t no_friction_with_driver : 1;
		std::uint32_t can_trigger_automatic_opening_doors : 1;
		std::uint32_t autoaim_when_teamless : 1;
	};
	static_assert(sizeof(VehicleFlags) == sizeof(std::uint32_t));

	struct Vehicle : public Unit {
		VehicleFlags vehicle_flags;
		VehicleType vehicle_type;
		PADDING(2);
		float maximum_forward_speed;
		float maximum_reverse_speed;
		float speed_acceleration;
		float speed_deceleration;
		float maximum_left_turn;
		float maximum_right_turn;
		float wheel_circumference;
		float turn_rate;
		float blur_speed;
		VehicleFunctionIn vehicle_a_in;
		VehicleFunctionIn vehicle_b_in;
		VehicleFunctionIn vehicle_c_in;
		VehicleFunctionIn vehicle_d_in;
		PADDING(12);
		float maximum_left_slide;
		float maximum_right_slide;
		float slide_acceleration;
		float slide_deceleration;
		float minimum_flipping_angular_velocity;
		float maximum_flipping_angular_velocity;
		PADDING(24);
		float fixed_gun_yaw;
		float fixed_gun_pitch;
		PADDING(24);
		float ai_sideslip_distance;
		float ai_destination_radius;
		float ai_avoidance_distance;
		float ai_pathfinding_radius;
		float ai_charge_repeat_timeout;
		float ai_strafing_abort_range;
		float ai_oversteering_bounds[2];
		Angle ai_steering_maximum;
		float ai_throttle_maximum;
		float ai_move_position_time;
		PADDING(4);
		TagDependency suspension_sound;
		TagDependency crash_sound;
		TagDependency material_effects;
		TagDependency effect;
	};
	static_assert(sizeof(Vehicle) == 1008);

}

#endif


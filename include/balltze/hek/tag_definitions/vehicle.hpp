// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__VEHICLE_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__VEHICLE_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "unit.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<VehicleFlags> vehicle_flags;
		Memory::BigEndian<VehicleType> vehicle_type;
		PADDING(2);
		Memory::BigEndian<float> maximum_forward_speed;
		Memory::BigEndian<float> maximum_reverse_speed;
		Memory::BigEndian<float> speed_acceleration;
		Memory::BigEndian<float> speed_deceleration;
		Memory::BigEndian<float> maximum_left_turn;
		Memory::BigEndian<float> maximum_right_turn;
		Memory::BigEndian<float> wheel_circumference;
		Memory::BigEndian<float> turn_rate;
		Memory::BigEndian<float> blur_speed;
		Memory::BigEndian<VehicleFunctionIn> vehicle_a_in;
		Memory::BigEndian<VehicleFunctionIn> vehicle_b_in;
		Memory::BigEndian<VehicleFunctionIn> vehicle_c_in;
		Memory::BigEndian<VehicleFunctionIn> vehicle_d_in;
		PADDING(12);
		Memory::BigEndian<float> maximum_left_slide;
		Memory::BigEndian<float> maximum_right_slide;
		Memory::BigEndian<float> slide_acceleration;
		Memory::BigEndian<float> slide_deceleration;
		Memory::BigEndian<float> minimum_flipping_angular_velocity;
		Memory::BigEndian<float> maximum_flipping_angular_velocity;
		PADDING(24);
		Memory::BigEndian<float> fixed_gun_yaw;
		Memory::BigEndian<float> fixed_gun_pitch;
		PADDING(24);
		Memory::BigEndian<float> ai_sideslip_distance;
		Memory::BigEndian<float> ai_destination_radius;
		Memory::BigEndian<float> ai_avoidance_distance;
		Memory::BigEndian<float> ai_pathfinding_radius;
		Memory::BigEndian<float> ai_charge_repeat_timeout;
		Memory::BigEndian<float> ai_strafing_abort_range;
		Memory::BigEndian<float> ai_oversteering_bounds[2];
		Angle ai_steering_maximum;
		Memory::BigEndian<float> ai_throttle_maximum;
		Memory::BigEndian<float> ai_move_position_time;
		PADDING(4);
		TagDependency suspension_sound;
		TagDependency crash_sound;
		TagDependency material_effects;
		TagDependency effect;
	};
	static_assert(sizeof(Vehicle) == 1008);

}

#endif


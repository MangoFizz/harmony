// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__BIPED_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__BIPED_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "unit.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class BipedFunctionIn : std::uint16_t {
		NONE = 0,
		FLYING_VELOCITY,
	};

	struct BipedFlags {
		std::uint32_t turns_without_animating : 1;
		std::uint32_t uses_player_physics : 1;
		std::uint32_t flying : 1;
		std::uint32_t physics_pill_centered_at_origin : 1;
		std::uint32_t spherical : 1;
		std::uint32_t passes_through_other_bipeds : 1;
		std::uint32_t can_climb_any_surface : 1;
		std::uint32_t immune_to_falling_damage : 1;
		std::uint32_t rotate_while_airborne : 1;
		std::uint32_t uses_limp_body_physics : 1;
		std::uint32_t has_no_dying_airborne : 1;
		std::uint32_t random_speed_increase : 1;
		std::uint32_t unit_uses_old_ntsc_player_physics : 1;
	};
	static_assert(sizeof(BipedFlags) == sizeof(std::uint32_t));

	struct BipedContactPoint {
		PADDING(32);
		TagString marker_name;
	};
	static_assert(sizeof(BipedContactPoint) == 64);

	struct Biped : public Unit {
		Angle moving_turning_speed;
		Memory::BigEndian<BipedFlags> biped_flags;
		Angle stationary_turning_threshold;
		PADDING(16);
		Memory::BigEndian<BipedFunctionIn> biped_a_in;
		Memory::BigEndian<BipedFunctionIn> biped_b_in;
		Memory::BigEndian<BipedFunctionIn> biped_c_in;
		Memory::BigEndian<BipedFunctionIn> biped_d_in;
		TagDependency dont_use;
		Angle bank_angle;
		Memory::BigEndian<float> bank_apply_time;
		Memory::BigEndian<float> bank_decay_time;
		Memory::BigEndian<float> pitch_ratio;
		Memory::BigEndian<float> max_velocity;
		Memory::BigEndian<float> max_sidestep_velocity;
		Memory::BigEndian<float> acceleration;
		Memory::BigEndian<float> deceleration;
		Angle angular_velocity_maximum;
		Angle angular_acceleration_maximum;
		Memory::BigEndian<float> crouch_velocity_modifier;
		PADDING(8);
		Angle maximum_slope_angle;
		Angle downhill_falloff_angle;
		Angle downhill_cutoff_angle;
		Memory::BigEndian<float> downhill_velocity_scale;
		Angle uphill_falloff_angle;
		Angle uphill_cutoff_angle;
		Memory::BigEndian<float> uphill_velocity_scale;
		PADDING(24);
		TagDependency footsteps;
		PADDING(24);
		Memory::BigEndian<float> jump_velocity;
		PADDING(28);
		Memory::BigEndian<float> maximum_soft_landing_time;
		Memory::BigEndian<float> maximum_hard_landing_time;
		Memory::BigEndian<float> minimum_soft_landing_velocity;
		Memory::BigEndian<float> minimum_hard_landing_velocity;
		Memory::BigEndian<float> maximum_hard_landing_velocity;
		Memory::BigEndian<float> death_hard_landing_velocity;
		PADDING(20);
		Memory::BigEndian<float> standing_camera_height;
		Memory::BigEndian<float> crouching_camera_height;
		Memory::BigEndian<float> crouch_transition_time;
		PADDING(24);
		Memory::BigEndian<float> standing_collision_height;
		Memory::BigEndian<float> crouching_collision_height;
		Memory::BigEndian<float> collision_radius;
		PADDING(40);
		Memory::BigEndian<float> autoaim_width;
		PADDING(108);
		Memory::BigEndian<float> cosine_stationary_turning_threshold;
		Memory::BigEndian<float> crouch_camera_velocity;
		Memory::BigEndian<float> cosine_maximum_slope_angle;
		Memory::BigEndian<float> negative_sine_downhill_falloff_angle;
		Memory::BigEndian<float> negative_sine_downhill_cutoff_angle;
		Memory::BigEndian<float> sine_uphill_falloff_angle;
		Memory::BigEndian<float> sine_uphill_cutoff_angle;
		Index pelvis_model_node_index;
		Index head_model_node_index;
		TagReflexive<BipedContactPoint> contact_point;
	};
	static_assert(sizeof(Biped) == 1268);

}

#endif


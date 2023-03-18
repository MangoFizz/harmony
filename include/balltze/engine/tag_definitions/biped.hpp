// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__BIPED_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__BIPED_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "unit.hpp"

namespace Balltze::Engine::TagDefinitions { 
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
		BipedFlags biped_flags;
		Angle stationary_turning_threshold;
		PADDING(16);
		BipedFunctionIn biped_a_in;
		BipedFunctionIn biped_b_in;
		BipedFunctionIn biped_c_in;
		BipedFunctionIn biped_d_in;
		TagDependency dont_use;
		Angle bank_angle;
		float bank_apply_time;
		float bank_decay_time;
		float pitch_ratio;
		float max_velocity;
		float max_sidestep_velocity;
		float acceleration;
		float deceleration;
		Angle angular_velocity_maximum;
		Angle angular_acceleration_maximum;
		float crouch_velocity_modifier;
		PADDING(8);
		Angle maximum_slope_angle;
		Angle downhill_falloff_angle;
		Angle downhill_cutoff_angle;
		float downhill_velocity_scale;
		Angle uphill_falloff_angle;
		Angle uphill_cutoff_angle;
		float uphill_velocity_scale;
		PADDING(24);
		TagDependency footsteps;
		PADDING(24);
		float jump_velocity;
		PADDING(28);
		float maximum_soft_landing_time;
		float maximum_hard_landing_time;
		float minimum_soft_landing_velocity;
		float minimum_hard_landing_velocity;
		float maximum_hard_landing_velocity;
		float death_hard_landing_velocity;
		PADDING(20);
		float standing_camera_height;
		float crouching_camera_height;
		float crouch_transition_time;
		PADDING(24);
		float standing_collision_height;
		float crouching_collision_height;
		float collision_radius;
		PADDING(40);
		float autoaim_width;
		PADDING(108);
		float cosine_stationary_turning_threshold;
		float crouch_camera_velocity;
		float cosine_maximum_slope_angle;
		float negative_sine_downhill_falloff_angle;
		float negative_sine_downhill_cutoff_angle;
		float sine_uphill_falloff_angle;
		float sine_uphill_cutoff_angle;
		Index pelvis_model_node_index;
		Index head_model_node_index;
		TagReflexive<BipedContactPoint> contact_point;
	};
	static_assert(sizeof(Biped) == 1268);

}

#endif


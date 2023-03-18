// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__ACTOR_VARIANT_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__ACTOR_VARIANT_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "unit.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class ActorVariantMovementType : std::uint16_t {
		ALWAYS_RUN = 0,
		ALWAYS_CROUCH,
		SWITCH_TYPES,
	};

	enum class ActorVariantSpecialFireMode : std::uint16_t {
		NONE = 0,
		OVERCHARGE,
		SECONDARY_TRIGGER,
	};

	enum class ActorVariantSpecialFireSituation : std::uint16_t {
		NEVER = 0,
		ENEMY_VISIBLE,
		ENEMY_OUT_OF_SIGHT,
		STRAFING,
	};

	enum class ActorVariantTrajectoryType : std::uint16_t {
		TOSS = 0,
		LOB,
		BOUNCE,
	};

	enum class ActorVariantGrenadeStimulus : std::uint16_t {
		NEVER = 0,
		VISIBLE_TARGET,
		SEEK_COVER,
	};

	struct ActorVariantFlags {
		std::uint32_t can_shoot_while_flying : 1;
		std::uint32_t interpolate_color_in_hsv : 1;
		std::uint32_t has_unlimited_grenades : 1;
		std::uint32_t movement_switching_try_to_stay_with_friends : 1;
		std::uint32_t active_camouflage : 1;
		std::uint32_t super_active_camouflage : 1;
		std::uint32_t cannot_use_ranged_weapons : 1;
		std::uint32_t prefer_passenger_seat : 1;
	};
	static_assert(sizeof(ActorVariantFlags) == sizeof(std::uint32_t));

	struct ActorVariantChangeColors {
		ColorRGB color_lower_bound;
		ColorRGB color_upper_bound;
		PADDING(8);
	};
	static_assert(sizeof(ActorVariantChangeColors) == 32);

	struct ActorVariant {
		ActorVariantFlags flags;
		TagDependency actor_definition;
		TagDependency unit;
		TagDependency major_variant;
		MetagameType metagame_type;
		MetagameClass metagame_class;
		PADDING(20);
		ActorVariantMovementType movement_type;
		PADDING(2);
		float initial_crouch_chance;
		float crouch_time[2];
		float run_time[2];
		TagDependency weapon;
		float maximum_firing_distance;
		float rate_of_fire;
		Angle projectile_error;
		float first_burst_delay_time[2];
		float new_target_firing_pattern_time;
		float surprise_delay_time;
		float surprise_fire_wildly_time;
		float death_fire_wildly_chance;
		float death_fire_wildly_time;
		float desired_combat_range[2];
		Vector3D custom_stand_gun_offset;
		Vector3D custom_crouch_gun_offset;
		float target_tracking;
		float target_leading;
		float weapon_damage_modifier;
		float damage_per_second;
		float burst_origin_radius;
		Angle burst_origin_angle;
		float burst_return_length[2];
		Angle burst_return_angle;
		float burst_duration[2];
		float burst_separation[2];
		Angle burst_angular_velocity;
		PADDING(4);
		float special_damage_modifier;
		Angle special_projectile_error;
		float new_target_burst_duration;
		float new_target_burst_separation;
		float new_target_rate_of_fire;
		float new_target_projectile_error;
		PADDING(8);
		float moving_burst_duration;
		float moving_burst_separation;
		float moving_rate_of_fire;
		float moving_projectile_error;
		PADDING(8);
		float berserk_burst_duration;
		float berserk_burst_separation;
		float berserk_rate_of_fire;
		float berserk_projectile_error;
		PADDING(8);
		float super_ballistic_range;
		float bombardment_range;
		float modified_vision_range;
		ActorVariantSpecialFireMode special_fire_mode;
		ActorVariantSpecialFireSituation special_fire_situation;
		float special_fire_chance;
		float special_fire_delay;
		float melee_range;
		float melee_abort_range;
		float berserk_firing_ranges[2];
		float berserk_melee_range;
		float berserk_melee_abort_range;
		PADDING(8);
		GrenadeType grenade_type;
		ActorVariantTrajectoryType trajectory_type;
		ActorVariantGrenadeStimulus grenade_stimulus;
		std::int16_t minimum_enemy_count;
		float enemy_radius;
		PADDING(4);
		float grenade_velocity;
		float grenade_ranges[2];
		float collateral_damage_radius;
		Fraction grenade_chance;
		float grenade_check_time;
		float encounter_grenade_timeout;
		PADDING(20);
		TagDependency equipment;
		std::int16_t grenade_count[2];
		float dont_drop_grenades_chance;
		float drop_weapon_loaded[2];
		std::int16_t drop_weapon_ammo[2];
		PADDING(12);
		PADDING(16);
		float body_vitality;
		float shield_vitality;
		float shield_sapping_radius;
		Index forced_shader_permutation;
		PADDING(2);
		PADDING(16);
		PADDING(12);
		TagReflexive<ActorVariantChangeColors> change_colors;
	};
	static_assert(sizeof(ActorVariant) == 568);

}

#endif


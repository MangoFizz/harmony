// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__ACTOR_VARIANT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__ACTOR_VARIANT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "unit.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<ActorVariantFlags> flags;
		TagDependency actor_definition;
		TagDependency unit;
		TagDependency major_variant;
		Memory::BigEndian<MetagameType> metagame_type;
		Memory::BigEndian<MetagameClass> metagame_class;
		PADDING(20);
		Memory::BigEndian<ActorVariantMovementType> movement_type;
		PADDING(2);
		Memory::BigEndian<float> initial_crouch_chance;
		Memory::BigEndian<float> crouch_time[2];
		Memory::BigEndian<float> run_time[2];
		TagDependency weapon;
		Memory::BigEndian<float> maximum_firing_distance;
		Memory::BigEndian<float> rate_of_fire;
		Angle projectile_error;
		Memory::BigEndian<float> first_burst_delay_time[2];
		Memory::BigEndian<float> new_target_firing_pattern_time;
		Memory::BigEndian<float> surprise_delay_time;
		Memory::BigEndian<float> surprise_fire_wildly_time;
		Memory::BigEndian<float> death_fire_wildly_chance;
		Memory::BigEndian<float> death_fire_wildly_time;
		Memory::BigEndian<float> desired_combat_range[2];
		Vector3D custom_stand_gun_offset;
		Vector3D custom_crouch_gun_offset;
		Memory::BigEndian<float> target_tracking;
		Memory::BigEndian<float> target_leading;
		Memory::BigEndian<float> weapon_damage_modifier;
		Memory::BigEndian<float> damage_per_second;
		Memory::BigEndian<float> burst_origin_radius;
		Angle burst_origin_angle;
		Memory::BigEndian<float> burst_return_length[2];
		Angle burst_return_angle;
		Memory::BigEndian<float> burst_duration[2];
		Memory::BigEndian<float> burst_separation[2];
		Angle burst_angular_velocity;
		PADDING(4);
		Memory::BigEndian<float> special_damage_modifier;
		Angle special_projectile_error;
		Memory::BigEndian<float> new_target_burst_duration;
		Memory::BigEndian<float> new_target_burst_separation;
		Memory::BigEndian<float> new_target_rate_of_fire;
		Memory::BigEndian<float> new_target_projectile_error;
		PADDING(8);
		Memory::BigEndian<float> moving_burst_duration;
		Memory::BigEndian<float> moving_burst_separation;
		Memory::BigEndian<float> moving_rate_of_fire;
		Memory::BigEndian<float> moving_projectile_error;
		PADDING(8);
		Memory::BigEndian<float> berserk_burst_duration;
		Memory::BigEndian<float> berserk_burst_separation;
		Memory::BigEndian<float> berserk_rate_of_fire;
		Memory::BigEndian<float> berserk_projectile_error;
		PADDING(8);
		Memory::BigEndian<float> super_ballistic_range;
		Memory::BigEndian<float> bombardment_range;
		Memory::BigEndian<float> modified_vision_range;
		Memory::BigEndian<ActorVariantSpecialFireMode> special_fire_mode;
		Memory::BigEndian<ActorVariantSpecialFireSituation> special_fire_situation;
		Memory::BigEndian<float> special_fire_chance;
		Memory::BigEndian<float> special_fire_delay;
		Memory::BigEndian<float> melee_range;
		Memory::BigEndian<float> melee_abort_range;
		Memory::BigEndian<float> berserk_firing_ranges[2];
		Memory::BigEndian<float> berserk_melee_range;
		Memory::BigEndian<float> berserk_melee_abort_range;
		PADDING(8);
		Memory::BigEndian<GrenadeType> grenade_type;
		Memory::BigEndian<ActorVariantTrajectoryType> trajectory_type;
		Memory::BigEndian<ActorVariantGrenadeStimulus> grenade_stimulus;
		Memory::BigEndian<std::int16_t> minimum_enemy_count;
		Memory::BigEndian<float> enemy_radius;
		PADDING(4);
		Memory::BigEndian<float> grenade_velocity;
		Memory::BigEndian<float> grenade_ranges[2];
		Memory::BigEndian<float> collateral_damage_radius;
		Fraction grenade_chance;
		Memory::BigEndian<float> grenade_check_time;
		Memory::BigEndian<float> encounter_grenade_timeout;
		PADDING(20);
		TagDependency equipment;
		Memory::BigEndian<std::int16_t> grenade_count[2];
		Memory::BigEndian<float> dont_drop_grenades_chance;
		Memory::BigEndian<float> drop_weapon_loaded[2];
		Memory::BigEndian<std::int16_t> drop_weapon_ammo[2];
		PADDING(12);
		PADDING(16);
		Memory::BigEndian<float> body_vitality;
		Memory::BigEndian<float> shield_vitality;
		Memory::BigEndian<float> shield_sapping_radius;
		Index forced_shader_permutation;
		PADDING(2);
		PADDING(16);
		PADDING(12);
		TagReflexive<ActorVariantChangeColors> change_colors;
	};
	static_assert(sizeof(ActorVariant) == 568);

}

#endif


// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__WEAPON_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__WEAPON_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "item.hpp"
#include "object.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class WeaponSecondaryTriggerMode : std::uint16_t {
		NORMAL = 0,
		SLAVED_TO_PRIMARY,
		INHIBITS_PRIMARY,
		LOADS_ALTERATE_AMMUNITION,
		LOADS_MULTIPLE_PRIMARY_AMMUNITION,
	};

	enum class WeaponFunctionIn : std::uint16_t {
		NONE = 0,
		HEAT,
		PRIMARY_AMMUNITION,
		SECONDARY_AMMUNITION,
		PRIMARY_RATE_OF_FIRE,
		SECONDARY_RATE_OF_FIRE,
		READY,
		PRIMARY_EJECTION_PORT,
		SECONDARY_EJECTION_PORT,
		OVERHEATED,
		PRIMARY_CHARGED,
		SECONDARY_CHARGED,
		ILLUMINATION,
		AGE,
		INTEGRATED_LIGHT,
		PRIMARY_FIRING,
		SECONDARY_FIRING,
		PRIMARY_FIRING_ON,
		SECONDARY_FIRING_ON,
	};

	enum class WeaponMovementPenalized : std::uint16_t {
		ALWAYS = 0,
		WHEN_ZOOMED,
		WHEN_ZOOMED_OR_RELOADING,
	};

	enum class WeaponType : std::uint16_t {
		UNDEFINED = 0,
		SHOTGUN,
		NEEDLER,
		PLASMA_PISTOL,
		PLASMA_RIFLE,
		ROCKET_LAUNCHER,
	};

	enum class WeaponPredictionType : std::uint16_t {
		NONE = 0,
		CONTINUOUS,
		INSTANT,
	};

	enum class WeaponOverchargedAction : std::uint16_t {
		NONE = 0,
		EXPLODE,
		DISCHARGE,
	};

	enum class WeaponDistributionFunction : std::uint16_t {
		POINT = 0,
		HORIZONTAL_FAN,
	};

	struct WeaponMagazineFlags {
		std::uint32_t wastes_rounds_when_reloaded : 1;
		std::uint32_t every_round_must_be_chambered : 1;
	};
	static_assert(sizeof(WeaponMagazineFlags) == sizeof(std::uint32_t));

	struct WeaponTriggerFlags {
		std::uint32_t tracks_fired_projectile : 1;
		std::uint32_t random_firing_effects : 1;
		std::uint32_t can_fire_with_partial_ammo : 1;
		std::uint32_t does_not_repeat_automatically : 1;
		std::uint32_t locks_in_on_off_state : 1;
		std::uint32_t projectiles_use_weapon_origin : 1;
		std::uint32_t sticks_when_dropped : 1;
		std::uint32_t ejects_during_chamber : 1;
		std::uint32_t discharging_spews : 1;
		std::uint32_t analog_rate_of_fire : 1;
		std::uint32_t use_error_when_unzoomed : 1;
		std::uint32_t projectile_vector_cannot_be_adjusted : 1;
		std::uint32_t projectiles_have_identical_error : 1;
		std::uint32_t projectile_is_client_side_only : 1;
		std::uint32_t use_original_unit_adjust_projectile_ray : 1;
	};
	static_assert(sizeof(WeaponTriggerFlags) == sizeof(std::uint32_t));

	struct WeaponFlags {
		std::uint32_t vertical_heat_display : 1;
		std::uint32_t mutually_exclusive_triggers : 1;
		std::uint32_t attacks_automatically_on_bump : 1;
		std::uint32_t must_be_readied : 1;
		std::uint32_t doesnt_count_toward_maximum : 1;
		std::uint32_t aim_assists_only_when_zoomed : 1;
		std::uint32_t prevents_grenade_throwing : 1;
		std::uint32_t must_be_picked_up : 1;
		std::uint32_t holds_triggers_when_dropped : 1;
		std::uint32_t prevents_melee_attack : 1;
		std::uint32_t detonates_when_dropped : 1;
		std::uint32_t cannot_fire_at_maximum_age : 1;
		std::uint32_t secondary_trigger_overrides_grenades : 1;
		std::uint32_t obsolete_does_not_depower_active_camo_in_multilplayer : 1;
		std::uint32_t enables_integrated_night_vision : 1;
		std::uint32_t ais_use_weapon_melee_damage : 1;
	};
	static_assert(sizeof(WeaponFlags) == sizeof(std::uint32_t));

	struct WeaponMagazineObject {
		std::int16_t rounds;
		PADDING(10);
		TagDependency equipment;
	};
	static_assert(sizeof(WeaponMagazineObject) == 28);

	struct WeaponMagazine {
		WeaponMagazineFlags flags;
		std::int16_t rounds_recharged;
		std::int16_t rounds_total_initial;
		std::int16_t rounds_reserved_maximum;
		std::int16_t rounds_loaded_maximum;
		PADDING(8);
		float reload_time;
		std::int16_t rounds_reloaded;
		PADDING(2);
		float chamber_time;
		PADDING(8);
		PADDING(16);
		TagDependency reloading_effect;
		TagDependency chambering_effect;
		PADDING(12);
		TagReflexive<WeaponMagazineObject> magazine_objects;
	};
	static_assert(sizeof(WeaponMagazine) == 112);

	struct WeaponTriggerFiringEffect {
		std::int16_t shot_count_lower_bound;
		std::int16_t shot_count_upper_bound;
		PADDING(32);
		TagDependency firing_effect;
		TagDependency misfire_effect;
		TagDependency empty_effect;
		TagDependency firing_damage;
		TagDependency misfire_damage;
		TagDependency empty_damage;
	};
	static_assert(sizeof(WeaponTriggerFiringEffect) == 132);

	struct WeaponTrigger {
		WeaponTriggerFlags flags;
		float maximum_rate_of_fire[2];
		float acceleration_time;
		float deceleration_time;
		Fraction blurred_rate_of_fire;
		PADDING(8);
		Index magazine;
		std::int16_t rounds_per_shot;
		std::int16_t minimum_rounds_loaded;
		std::int16_t projectiles_between_contrails;
		PADDING(4);
		WeaponPredictionType prediction_type;
		ObjectNoise firing_noise;
		float error[2];
		float error_acceleration_time;
		float error_deceleration_time;
		PADDING(8);
		float charging_time;
		float charged_time;
		WeaponOverchargedAction overcharged_action;
		PADDING(2);
		float charged_illumination;
		float spew_time;
		TagDependency charging_effect;
		WeaponDistributionFunction distribution_function;
		std::int16_t projectiles_per_shot;
		Angle distribution_angle;
		PADDING(4);
		Angle minimum_error;
		Angle error_angle[2];
		Point3D first_person_offset;
		PADDING(4);
		TagDependency projectile;
		float ejection_port_recovery_time;
		float illumination_recovery_time;
		PADDING(12);
		Fraction heat_generated_per_round;
		Fraction age_generated_per_round;
		PADDING(4);
		float overload_time;
		PADDING(8);
		PADDING(32);
		float illumination_recovery_rate;
		float ejection_port_recovery_rate;
		float firing_acceleration_rate;
		float firing_deceleration_rate;
		float error_acceleration_rate;
		float error_deceleration_rate;
		TagReflexive<WeaponTriggerFiringEffect> firing_effects;
	};
	static_assert(sizeof(WeaponTrigger) == 276);

	struct Weapon : public Item {
		WeaponFlags weapon_flags;
		TagString label;
		WeaponSecondaryTriggerMode secondary_trigger_mode;
		std::int16_t maximum_alternate_shots_loaded;
		WeaponFunctionIn weapon_a_in;
		WeaponFunctionIn weapon_b_in;
		WeaponFunctionIn weapon_c_in;
		WeaponFunctionIn weapon_d_in;
		float ready_time;
		TagDependency ready_effect;
		Fraction heat_recovery_threshold;
		Fraction overheated_threshold;
		Fraction heat_detonation_threshold;
		Fraction heat_detonation_fraction;
		Fraction heat_loss_rate;
		Fraction heat_illumination;
		PADDING(16);
		TagDependency overheated;
		TagDependency overheat_detonation;
		TagDependency player_melee_damage;
		TagDependency player_melee_response;
		PADDING(8);
		TagDependency actor_firing_parameters;
		float near_reticle_range;
		float far_reticle_range;
		float intersection_reticle_range;
		PADDING(2);
		std::int16_t zoom_levels;
		float zoom_magnification_range[2];
		Angle autoaim_angle;
		float autoaim_range;
		Angle magnetism_angle;
		float magnetism_range;
		Angle deviation_angle;
		PADDING(4);
		WeaponMovementPenalized movement_penalized;
		PADDING(2);
		Fraction forward_movement_penalty;
		Fraction sideways_movement_penalty;
		PADDING(4);
		float minimum_target_range;
		float looking_time_modifier;
		PADDING(4);
		float light_power_on_time;
		float light_power_off_time;
		TagDependency light_power_on_effect;
		TagDependency light_power_off_effect;
		float age_heat_recovery_penalty;
		float age_rate_of_fire_penalty;
		Fraction age_misfire_start;
		Fraction age_misfire_chance;
		PADDING(12);
		TagDependency first_person_model;
		TagDependency first_person_animations;
		PADDING(4);
		TagDependency hud_interface;
		TagDependency pickup_sound;
		TagDependency zoom_in_sound;
		TagDependency zoom_out_sound;
		PADDING(12);
		float active_camo_ding;
		float active_camo_regrowth_rate;
		PADDING(12);
		PADDING(2);
		WeaponType weapon_type;
		TagReflexive<PredictedResource> more_predicted_resources;
		TagReflexive<WeaponMagazine> magazines;
		TagReflexive<WeaponTrigger> triggers;
	};
	static_assert(sizeof(Weapon) == 1288);

}

#endif


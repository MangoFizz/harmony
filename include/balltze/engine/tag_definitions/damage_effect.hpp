// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__DAMAGE_EFFECT_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__DAMAGE_EFFECT_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class DamageEffectScreenFlashType : std::uint16_t {
		NONE = 0,
		LIGHTEN,
		DARKEN,
		MAX,
		MIN,
		INVERT,
		TINT,
	};

	enum class DamageEffectScreenFlashPriority : std::uint16_t {
		LOW = 0,
		MEDIUM,
		HIGH,
	};

	enum class DamageEffectSideEffect : std::uint16_t {
		NONE = 0,
		HARMLESS,
		LETHAL_TO_THE_UNSUSPECTING,
		EMP,
	};

	enum class DamageEffectCategory : std::uint16_t {
		NONE = 0,
		FALLING,
		BULLET,
		GRENADE,
		HIGH_EXPLOSIVE,
		SNIPER,
		MELEE,
		FLAME,
		MOUNTED_WEAPON,
		VEHICLE,
		PLASMA,
		NEEDLE,
		SHOTGUN,
	};

	struct DamageEffectDamageFlags {
		std::uint32_t does_not_hurt_owner : 1;
		std::uint32_t can_cause_headshots : 1;
		std::uint32_t pings_resistant_units : 1;
		std::uint32_t does_not_hurt_friends : 1;
		std::uint32_t does_not_ping_units : 1;
		std::uint32_t detonates_explosives : 1;
		std::uint32_t only_hurts_shields : 1;
		std::uint32_t causes_flaming_death : 1;
		std::uint32_t damage_indicators_always_point_down : 1;
		std::uint32_t skips_shields : 1;
		std::uint32_t only_hurts_one_infection_form : 1;
		std::uint32_t can_cause_multiplayer_headshots : 1;
		std::uint32_t infection_form_pop : 1;
		std::uint32_t ignore_seat_scale_for_dir_dmg : 1;
		std::uint32_t forces_hard_ping : 1;
		std::uint32_t does_not_hurt_players : 1;
		std::uint32_t use_3d_instantaneous_acceleration : 1;
		std::uint32_t allow_any_non_zero_acceleration_value : 1;
	};
	static_assert(sizeof(DamageEffectDamageFlags) == sizeof(std::uint32_t));

	struct DamageEffectFlags {
		std::uint32_t do_not_scale_damage_by_distance : 1;
	};
	static_assert(sizeof(DamageEffectFlags) == sizeof(std::uint32_t));

	struct DamageEffect {
		float radius[2];
		float cutoff_scale;
		DamageEffectFlags flags;
		PADDING(16);
		PADDING(4);
		DamageEffectScreenFlashType type;
		DamageEffectScreenFlashPriority priority;
		PADDING(8);
		PADDING(4);
		float duration;
		FunctionType fade_function;
		PADDING(2);
		PADDING(4);
		PADDING(4);
		float maximum_intensity;
		PADDING(4);
		ColorARGB color;
		float low_frequency_vibrate_frequency;
		float low_frequency_vibrate_duration;
		FunctionType low_frequency_vibrate_fade_function;
		PADDING(2);
		PADDING(8);
		float high_frequency_vibrate_frequency;
		float high_frequency_vibrate_duration;
		FunctionType high_frequency_vibrate_fade_function;
		PADDING(2);
		PADDING(4);
		PADDING(16);
		PADDING(8);
		float temporary_camera_impulse_duration;
		FunctionType temporary_camera_impulse_fade_function;
		PADDING(2);
		Angle temporary_camera_impulse_rotation;
		float temporary_camera_impulse_pushback;
		float jitter[2];
		PADDING(8);
		Angle permanent_camera_impulse_angle;
		PADDING(4);
		PADDING(12);
		float camera_shaking_duration;
		FunctionType camera_shaking_falloff_function;
		PADDING(2);
		float camera_shaking_random_translation;
		Angle camera_shaking_random_rotation;
		PADDING(4);
		PADDING(8);
		WaveFunction camera_shaking_wobble_function;
		PADDING(2);
		float camera_shaking_wobble_period;
		float camera_shaking_wobble_weight;
		PADDING(12);
		PADDING(16);
		PADDING(4);
		TagDependency sound;
		PADDING(108);
		PADDING(4);
		float breaking_effect_forward_velocity;
		float breaking_effect_forward_radius;
		float breaking_effect_forward_exponent;
		PADDING(4);
		PADDING(8);
		float breaking_effect_outward_velocity;
		float breaking_effect_outward_radius;
		float breaking_effect_outward_exponent;
		PADDING(8);
		PADDING(4);
		DamageEffectSideEffect damage_side_effect;
		DamageEffectCategory damage_category;
		DamageEffectDamageFlags damage_flags;
		float damage_aoe_core_radius;
		float damage_lower_bound;
		float damage_upper_bound[2];
		float damage_vehicle_passthrough_penalty;
		float damage_active_camouflage_damage;
		float damage_stun;
		float damage_maximum_stun;
		float damage_stun_time;
		PADDING(4);
		Vector3D damage_instantaneous_acceleration;
		float dirt;
		float sand;
		float stone;
		float snow;
		float wood;
		float metal_hollow;
		float metal_thin;
		float metal_thick;
		float rubber;
		float glass;
		float force_field;
		float grunt;
		float hunter_armor;
		float hunter_skin;
		float elite;
		float jackal;
		float jackal_energy_shield;
		float engineer_skin;
		float engineer_force_field;
		float flood_combat_form;
		float flood_carrier_form;
		float cyborg_armor;
		float cyborg_energy_shield;
		float human_armor;
		float human_skin;
		float sentinel;
		float monitor;
		float plastic;
		float water;
		float leaves;
		float elite_energy_shield;
		float ice;
		float hunter_shield;
		PADDING(12);
		PADDING(16);
	};
	static_assert(sizeof(DamageEffect) == 672);

}

#endif


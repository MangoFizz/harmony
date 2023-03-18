// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__DAMAGE_EFFECT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__DAMAGE_EFFECT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<float> radius[2];
		Memory::BigEndian<float> cutoff_scale;
		Memory::BigEndian<DamageEffectFlags> flags;
		PADDING(16);
		PADDING(4);
		Memory::BigEndian<DamageEffectScreenFlashType> type;
		Memory::BigEndian<DamageEffectScreenFlashPriority> priority;
		PADDING(8);
		PADDING(4);
		Memory::BigEndian<float> duration;
		Memory::BigEndian<FunctionType> fade_function;
		PADDING(2);
		PADDING(4);
		PADDING(4);
		Memory::BigEndian<float> maximum_intensity;
		PADDING(4);
		ColorARGB color;
		Memory::BigEndian<float> low_frequency_vibrate_frequency;
		Memory::BigEndian<float> low_frequency_vibrate_duration;
		Memory::BigEndian<FunctionType> low_frequency_vibrate_fade_function;
		PADDING(2);
		PADDING(8);
		Memory::BigEndian<float> high_frequency_vibrate_frequency;
		Memory::BigEndian<float> high_frequency_vibrate_duration;
		Memory::BigEndian<FunctionType> high_frequency_vibrate_fade_function;
		PADDING(2);
		PADDING(4);
		PADDING(16);
		PADDING(8);
		Memory::BigEndian<float> temporary_camera_impulse_duration;
		Memory::BigEndian<FunctionType> temporary_camera_impulse_fade_function;
		PADDING(2);
		Angle temporary_camera_impulse_rotation;
		Memory::BigEndian<float> temporary_camera_impulse_pushback;
		Memory::BigEndian<float> jitter[2];
		PADDING(8);
		Angle permanent_camera_impulse_angle;
		PADDING(4);
		PADDING(12);
		Memory::BigEndian<float> camera_shaking_duration;
		Memory::BigEndian<FunctionType> camera_shaking_falloff_function;
		PADDING(2);
		Memory::BigEndian<float> camera_shaking_random_translation;
		Angle camera_shaking_random_rotation;
		PADDING(4);
		PADDING(8);
		Memory::BigEndian<WaveFunction> camera_shaking_wobble_function;
		PADDING(2);
		Memory::BigEndian<float> camera_shaking_wobble_period;
		Memory::BigEndian<float> camera_shaking_wobble_weight;
		PADDING(12);
		PADDING(16);
		PADDING(4);
		TagDependency sound;
		PADDING(108);
		PADDING(4);
		Memory::BigEndian<float> breaking_effect_forward_velocity;
		Memory::BigEndian<float> breaking_effect_forward_radius;
		Memory::BigEndian<float> breaking_effect_forward_exponent;
		PADDING(4);
		PADDING(8);
		Memory::BigEndian<float> breaking_effect_outward_velocity;
		Memory::BigEndian<float> breaking_effect_outward_radius;
		Memory::BigEndian<float> breaking_effect_outward_exponent;
		PADDING(8);
		PADDING(4);
		Memory::BigEndian<DamageEffectSideEffect> damage_side_effect;
		Memory::BigEndian<DamageEffectCategory> damage_category;
		Memory::BigEndian<DamageEffectDamageFlags> damage_flags;
		Memory::BigEndian<float> damage_aoe_core_radius;
		Memory::BigEndian<float> damage_lower_bound;
		Memory::BigEndian<float> damage_upper_bound[2];
		Memory::BigEndian<float> damage_vehicle_passthrough_penalty;
		Memory::BigEndian<float> damage_active_camouflage_damage;
		Memory::BigEndian<float> damage_stun;
		Memory::BigEndian<float> damage_maximum_stun;
		Memory::BigEndian<float> damage_stun_time;
		PADDING(4);
		Vector3D damage_instantaneous_acceleration;
		Memory::BigEndian<float> dirt;
		Memory::BigEndian<float> sand;
		Memory::BigEndian<float> stone;
		Memory::BigEndian<float> snow;
		Memory::BigEndian<float> wood;
		Memory::BigEndian<float> metal_hollow;
		Memory::BigEndian<float> metal_thin;
		Memory::BigEndian<float> metal_thick;
		Memory::BigEndian<float> rubber;
		Memory::BigEndian<float> glass;
		Memory::BigEndian<float> force_field;
		Memory::BigEndian<float> grunt;
		Memory::BigEndian<float> hunter_armor;
		Memory::BigEndian<float> hunter_skin;
		Memory::BigEndian<float> elite;
		Memory::BigEndian<float> jackal;
		Memory::BigEndian<float> jackal_energy_shield;
		Memory::BigEndian<float> engineer_skin;
		Memory::BigEndian<float> engineer_force_field;
		Memory::BigEndian<float> flood_combat_form;
		Memory::BigEndian<float> flood_carrier_form;
		Memory::BigEndian<float> cyborg_armor;
		Memory::BigEndian<float> cyborg_energy_shield;
		Memory::BigEndian<float> human_armor;
		Memory::BigEndian<float> human_skin;
		Memory::BigEndian<float> sentinel;
		Memory::BigEndian<float> monitor;
		Memory::BigEndian<float> plastic;
		Memory::BigEndian<float> water;
		Memory::BigEndian<float> leaves;
		Memory::BigEndian<float> elite_energy_shield;
		Memory::BigEndian<float> ice;
		Memory::BigEndian<float> hunter_shield;
		PADDING(12);
		PADDING(16);
	};
	static_assert(sizeof(DamageEffect) == 672);

}

#endif


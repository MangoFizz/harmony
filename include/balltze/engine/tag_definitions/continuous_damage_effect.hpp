// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__CONTINUOUS_DAMAGE_EFFECT_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__CONTINUOUS_DAMAGE_EFFECT_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "damage_effect.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct ContinuousDamageEffect {
		float radius[2];
		float cutoff_scale;
		PADDING(24);
		float low_frequency_vibrate_frequency;
		float high_frequency_vibrate_frequency;
		PADDING(24);
		float camera_shaking_random_translation;
		Angle camera_shaking_random_rotation;
		PADDING(12);
		WaveFunction camera_shaking_wobble_function;
		PADDING(2);
		float camera_shaking_wobble_period;
		float camera_shaking_wobble_weight;
		PADDING(4);
		PADDING(20);
		PADDING(8);
		PADDING(160);
		DamageEffectSideEffect damage_side_effect;
		DamageEffectCategory damage_category;
		DamageEffectDamageFlags damage_flags;
		PADDING(4);
		float damage_lower_bound;
		float damage_upper_bound[2];
		float damage_vehicle_passthrough_penalty;
		PADDING(4);
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
		PADDING(28);
	};
	static_assert(sizeof(ContinuousDamageEffect) == 512);

}

#endif


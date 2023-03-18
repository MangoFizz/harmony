// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__CONTINUOUS_DAMAGE_EFFECT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__CONTINUOUS_DAMAGE_EFFECT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "damage_effect.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct ContinuousDamageEffect {
		Memory::BigEndian<float> radius[2];
		Memory::BigEndian<float> cutoff_scale;
		PADDING(24);
		Memory::BigEndian<float> low_frequency_vibrate_frequency;
		Memory::BigEndian<float> high_frequency_vibrate_frequency;
		PADDING(24);
		Memory::BigEndian<float> camera_shaking_random_translation;
		Angle camera_shaking_random_rotation;
		PADDING(12);
		Memory::BigEndian<WaveFunction> camera_shaking_wobble_function;
		PADDING(2);
		Memory::BigEndian<float> camera_shaking_wobble_period;
		Memory::BigEndian<float> camera_shaking_wobble_weight;
		PADDING(4);
		PADDING(20);
		PADDING(8);
		PADDING(160);
		Memory::BigEndian<DamageEffectSideEffect> damage_side_effect;
		Memory::BigEndian<DamageEffectCategory> damage_category;
		Memory::BigEndian<DamageEffectDamageFlags> damage_flags;
		PADDING(4);
		Memory::BigEndian<float> damage_lower_bound;
		Memory::BigEndian<float> damage_upper_bound[2];
		Memory::BigEndian<float> damage_vehicle_passthrough_penalty;
		PADDING(4);
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
		PADDING(28);
	};
	static_assert(sizeof(ContinuousDamageEffect) == 512);

}

#endif


// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__EQUIPMENT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__EQUIPMENT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "item.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class EquipmentPowerupType : std::uint16_t {
		NONE = 0,
		DOUBLE_SPEED,
		OVER_SHIELD,
		ACTIVE_CAMOUFLAGE,
		FULL_SPECTRUM_VISION,
		HEALTH,
		GRENADE,
	};

	struct Equipment : public Item {
		Memory::BigEndian<EquipmentPowerupType> powerup_type;
		Memory::BigEndian<GrenadeType> grenade_type;
		Memory::BigEndian<float> powerup_time;
		TagDependency pickup_sound;
		PADDING(144);
	};
	static_assert(sizeof(Equipment) == 944);

}

#endif


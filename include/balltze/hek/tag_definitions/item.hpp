// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__ITEM_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__ITEM_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "object.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct ItemFlags {
		std::uint32_t always_maintains_z_up : 1;
		std::uint32_t destroyed_by_explosions : 1;
		std::uint32_t unaffected_by_gravity : 1;
	};
	static_assert(sizeof(ItemFlags) == sizeof(std::uint32_t));

	struct Item : public Object {
		Memory::BigEndian<ItemFlags> item_flags;
		Index pickup_text_index;
		Memory::BigEndian<std::int16_t> sort_order;
		Memory::BigEndian<float> scale;
		Memory::BigEndian<std::int16_t> hud_message_value_scale;
		PADDING(2);
		PADDING(16);
		Memory::BigEndian<ObjectFunctionIn> item_a_in;
		Memory::BigEndian<ObjectFunctionIn> item_b_in;
		Memory::BigEndian<ObjectFunctionIn> item_c_in;
		Memory::BigEndian<ObjectFunctionIn> item_d_in;
		PADDING(164);
		TagDependency material_effects;
		TagDependency collision_sound;
		PADDING(120);
		Memory::BigEndian<float> detonation_delay[2];
		TagDependency detonating_effect;
		TagDependency detonation_effect;
	};
	static_assert(sizeof(Item) == 776);

}

#endif


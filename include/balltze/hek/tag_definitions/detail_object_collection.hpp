// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__DETAIL_OBJECT_COLLECTION_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__DETAIL_OBJECT_COLLECTION_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class DetailObjectCollectionType : std::uint16_t {
		SCREEN_FACING = 0,
		VIEWER_FACING,
	};

	struct DetailObjectCollectionTypeFlags {
		std::uint8_t unused_a : 1;
		std::uint8_t unused_b : 1;
		std::uint8_t interpolate_color_in_hsv : 1;
		std::uint8_t more_colors : 1;
	};
	static_assert(sizeof(DetailObjectCollectionTypeFlags) == sizeof(std::uint8_t));

	struct DetailObjectCollectionObjectType {
		TagString name;
		Memory::BigEndian<std::uint8_t> sequence_index;
		Memory::BigEndian<DetailObjectCollectionTypeFlags> flags;
		Memory::BigEndian<std::uint8_t> first_sprite_index;
		Memory::BigEndian<std::uint8_t> sprite_count;
		Fraction color_override_factor;
		PADDING(8);
		Memory::BigEndian<float> near_fade_distance;
		Memory::BigEndian<float> far_fade_distance;
		Memory::BigEndian<float> size;
		PADDING(4);
		ColorRGB minimum_color;
		ColorRGB maximum_color;
		ColorARGBInt ambient_color;
		PADDING(4);
	};
	static_assert(sizeof(DetailObjectCollectionObjectType) == 96);

	struct DetailObjectCollection {
		Memory::BigEndian<DetailObjectCollectionType> collection_type;
		PADDING(2);
		Memory::BigEndian<float> global_z_offset;
		PADDING(44);
		TagDependency sprite_plate;
		TagReflexive<DetailObjectCollectionObjectType> types;
		PADDING(48);
	};
	static_assert(sizeof(DetailObjectCollection) == 128);

}

#endif


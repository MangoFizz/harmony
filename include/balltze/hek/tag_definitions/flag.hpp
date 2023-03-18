// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__FLAG_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__FLAG_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class FlagTrailingEdgeShape : std::uint16_t {
		FLAT = 0,
		CONCAVE_TRIANGULAR,
		CONVEX_TRIANGULAR,
		TRAPEZOID_SHORT_TOP,
		TRAPEZOID_SHORT_BOTTOM,
	};

	enum class FlagAttachedEdgeShape : std::uint16_t {
		FLAT = 0,
		CONCAVE_TRIANGULAR,
	};

	struct FlagAttachmentPoint {
		Memory::BigEndian<std::int16_t> height_to_next_attachment;
		PADDING(2);
		PADDING(16);
		TagString marker_name;
	};
	static_assert(sizeof(FlagAttachmentPoint) == 52);

	struct Flag {
		Memory::BigEndian<IsUnusedFlag> flags;
		Memory::BigEndian<FlagTrailingEdgeShape> trailing_edge_shape;
		Memory::BigEndian<std::int16_t> trailing_edge_shape_offset;
		Memory::BigEndian<FlagAttachedEdgeShape> attached_edge_shape;
		PADDING(2);
		Memory::BigEndian<std::int16_t> width;
		Memory::BigEndian<std::int16_t> height;
		Memory::BigEndian<float> cell_width;
		Memory::BigEndian<float> cell_height;
		TagDependency red_flag_shader;
		TagDependency physics;
		Memory::BigEndian<float> wind_noise;
		PADDING(8);
		TagDependency blue_flag_shader;
		TagReflexive<FlagAttachmentPoint> attachment_points;
	};
	static_assert(sizeof(Flag) == 96);

}

#endif


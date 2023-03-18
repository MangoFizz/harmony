// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__FLAG_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__FLAG_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
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
		std::int16_t height_to_next_attachment;
		PADDING(2);
		PADDING(16);
		TagString marker_name;
	};
	static_assert(sizeof(FlagAttachmentPoint) == 52);

	struct Flag {
		IsUnusedFlag flags;
		FlagTrailingEdgeShape trailing_edge_shape;
		std::int16_t trailing_edge_shape_offset;
		FlagAttachedEdgeShape attached_edge_shape;
		PADDING(2);
		std::int16_t width;
		std::int16_t height;
		float cell_width;
		float cell_height;
		TagDependency red_flag_shader;
		TagDependency physics;
		float wind_noise;
		PADDING(8);
		TagDependency blue_flag_shader;
		TagReflexive<FlagAttachmentPoint> attachment_points;
	};
	static_assert(sizeof(Flag) == 96);

}

#endif


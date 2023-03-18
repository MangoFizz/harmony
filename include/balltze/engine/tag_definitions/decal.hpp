// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__DECAL_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__DECAL_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class DecalType : std::uint16_t {
		SCRATCH = 0,
		SPLATTER,
		BURN,
		PAINTED_SIGN,
	};

	enum class DecalLayer : std::uint16_t {
		PRIMARY = 0,
		SECONDARY,
		LIGHT,
		ALPHA_TESTED,
		WATER,
	};

	struct DecalFlags {
		std::uint16_t geometry_inherited_by_next_decal_in_chain : 1;
		std::uint16_t interpolate_color_in_hsv : 1;
		std::uint16_t more_colors : 1;
		std::uint16_t no_random_rotation : 1;
		std::uint16_t water_effect : 1;
		std::uint16_t sapien_snap_to_axis : 1;
		std::uint16_t sapien_incremental_counter : 1;
		std::uint16_t animation_loop : 1;
		std::uint16_t preserve_aspect : 1;
		std::uint16_t disabled_in_anniversary_by_blood_setting : 1;
	};
	static_assert(sizeof(DecalFlags) == sizeof(std::uint16_t));

	struct Decal {
		DecalFlags flags;
		DecalType type;
		DecalLayer layer;
		PADDING(2);
		TagDependency next_decal_in_chain;
		float radius[2];
		PADDING(12);
		Fraction intensity[2];
		ColorRGB color_lower_bounds;
		ColorRGB color_upper_bounds;
		PADDING(12);
		std::int16_t animation_loop_frame;
		std::int16_t animation_speed;
		PADDING(28);
		float lifetime[2];
		float decay_time[2];
		PADDING(12);
		PADDING(40);
		PADDING(2);
		PADDING(2);
		FramebufferBlendFunction framebuffer_blend_function;
		PADDING(2);
		PADDING(20);
		TagDependency map;
		PADDING(20);
		float maximum_sprite_extent;
		PADDING(4);
		PADDING(8);
	};
	static_assert(sizeof(Decal) == 268);

}

#endif


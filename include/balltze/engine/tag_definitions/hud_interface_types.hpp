// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__HUD_INTERFACE_TYPES_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__HUD_INTERFACE_TYPES_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class HUDInterfaceDestinationType : std::uint16_t {
		TINT_0_1 = 0,
		HORIZONTAL_OFFSET,
		VERTICAL_OFFSET,
		FADE_0_1,
	};

	enum class HUDInterfaceDestination : std::uint16_t {
		GEOMETRY_OFFSET = 0,
		PRIMARY_MAP,
		SECONDARY_MAP,
		TERTIARY_MAP,
	};

	enum class HUDInterfaceSource : std::uint16_t {
		PLAYER_PITCH = 0,
		PLAYER_PITCH_TANGENT,
		PLAYER_YAW,
		WEAPON_AMMO_TOTAL,
		WEAPON_AMMO_LOADED,
		WEAPON_HEAT,
		EXPLICIT_USES_LOW_BOUND,
		WEAPON_ZOOM_LEVEL,
	};

	enum class HUDInterfaceMultitextureOverlayAnchor : std::uint16_t {
		TEXTURE = 0,
		SCREEN,
	};

	enum class HUDInterfaceZeroToOneBlendFunction : std::uint16_t {
		ADD = 0,
		SUBTRACT,
		MULTIPLY,
		MULTIPLY2X,
		DOT,
	};

	enum class HUDInterfaceWrapMode : std::uint16_t {
		CLAMP = 0,
		WRAP,
	};

	enum class HUDInterfaceAnchor : std::uint16_t {
		TOP_LEFT = 0,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		CENTER,
	};

	enum class HUDInterfaceChildAnchor : std::uint16_t {
		FROM_PARENT = 0,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		CENTER,
	};

	struct HUDInterfaceMeterFlags {
		std::uint8_t use_min_max_for_state_changes : 1;
		std::uint8_t interpolate_between_min_max_flash_colors_as_state_changes : 1;
		std::uint8_t interpolate_color_along_hsv_space : 1;
		std::uint8_t more_colors_for_hsv_interpolation : 1;
		std::uint8_t invert_interpolation : 1;
		std::uint8_t use_xbox_shading : 1;
	};
	static_assert(sizeof(HUDInterfaceMeterFlags) == sizeof(std::uint8_t));

	struct HUDInterfaceScalingFlags {
		std::uint16_t dont_scale_offset : 1;
		std::uint16_t dont_scale_size : 1;
		std::uint16_t use_high_res_scale : 1;
	};
	static_assert(sizeof(HUDInterfaceScalingFlags) == sizeof(std::uint16_t));

	struct HUDInterfaceFlashFlags {
		std::uint16_t reverse_default_flashing_colors : 1;
	};
	static_assert(sizeof(HUDInterfaceFlashFlags) == sizeof(std::uint16_t));

	struct HUDInterfaceNumberFlags {
		std::uint8_t show_leading_zeros : 1;
		std::uint8_t only_show_when_zoomed : 1;
		std::uint8_t draw_a_trailing_m : 1;
	};
	static_assert(sizeof(HUDInterfaceNumberFlags) == sizeof(std::uint8_t));

	struct HUDInterfaceOverlayFlashFlags {
		std::uint32_t flashes_when_active : 1;
	};
	static_assert(sizeof(HUDInterfaceOverlayFlashFlags) == sizeof(std::uint32_t));

	struct HUDInterfaceMessagingFlags {
		std::uint8_t use_text_from_string_list_instead : 1;
		std::uint8_t override_default_color : 1;
		std::uint8_t width_offset_is_absolute_icon_width : 1;
	};
	static_assert(sizeof(HUDInterfaceMessagingFlags) == sizeof(std::uint8_t));

	struct HUDInterfaceMultitextureOverlayEffector {
		PADDING(64);
		HUDInterfaceDestinationType destination_type;
		HUDInterfaceDestination destination;
		HUDInterfaceSource source;
		PADDING(2);
		float in_bounds[2];
		float out_bounds[2];
		PADDING(64);
		ColorRGB tint_color_lower_bound;
		ColorRGB tint_color_upper_bound;
		WaveFunction periodic_function;
		PADDING(2);
		float function_period;
		float function_phase;
		PADDING(32);
	};
	static_assert(sizeof(HUDInterfaceMultitextureOverlayEffector) == 220);

	struct HUDInterfaceMultitextureOverlay {
		PADDING(2);
		std::int16_t type;
		FramebufferBlendFunction framebuffer_blend_function;
		PADDING(2);
		PADDING(32);
		HUDInterfaceMultitextureOverlayAnchor primary_anchor;
		HUDInterfaceMultitextureOverlayAnchor secondary_anchor;
		HUDInterfaceMultitextureOverlayAnchor tertiary_anchor;
		HUDInterfaceZeroToOneBlendFunction zero_to_one_blend_function;
		HUDInterfaceZeroToOneBlendFunction one_to_two_blend_function;
		PADDING(2);
		Point2D primary_scale;
		Point2D secondary_scale;
		Point2D tertiary_scale;
		Point2D primary_offset;
		Point2D secondary_offset;
		Point2D tertiary_offset;
		TagDependency primary;
		TagDependency secondary;
		TagDependency tertiary;
		HUDInterfaceWrapMode primary_wrap_mode;
		HUDInterfaceWrapMode secondary_wrap_mode;
		HUDInterfaceWrapMode tertiary_wrap_mode;
		PADDING(2);
		PADDING(184);
		TagReflexive<HUDInterfaceMultitextureOverlayEffector> effectors;
		PADDING(128);
	};
	static_assert(sizeof(HUDInterfaceMultitextureOverlay) == 480);

}

#endif


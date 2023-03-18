// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__HUD_GLOBALS_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__HUD_GLOBALS_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "hud_interface_types.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class HUDGlobalsAnniversaryRemapTargetLanguage : std::uint16_t {
		ENGLISH = 0,
		FRENCH,
		SPANISH,
		ITALIAN,
		GERMAN,
		TRADITIONAL_CHINESE,
		JAPANESE,
		KOREAN,
		PORTUGUESE,
		LATAM_SPANISH,
		POLISH,
		RUSSIAN,
		SIMPLIFIED_CHINESE,
	};

	struct HUDGlobalsWaypointArrowFlags {
		std::uint32_t dont_rotate_when_pointing_offscreen : 1;
	};
	static_assert(sizeof(HUDGlobalsWaypointArrowFlags) == sizeof(std::uint32_t));

	struct HUDGlobalsAnniversaryRemapTargetFlags {
		std::uint16_t legacy_mode : 1;
	};
	static_assert(sizeof(HUDGlobalsAnniversaryRemapTargetFlags) == sizeof(std::uint16_t));

	struct HUDGlobalsButtonIcon {
		Index sequence_index;
		std::int16_t width_offset;
		Point2DInt offset_from_reference_corner;
		ColorARGBInt override_icon_color;
		std::int8_t frame_rate;
		HUDInterfaceMessagingFlags flags;
		Index text_index;
	};
	static_assert(sizeof(HUDGlobalsButtonIcon) == 16);

	struct HUDGlobalsAnniversaryRemapTarget {
		TagDependency target_bitmap;
		HUDGlobalsAnniversaryRemapTargetLanguage language;
		HUDGlobalsAnniversaryRemapTargetFlags flags;
	};
	static_assert(sizeof(HUDGlobalsAnniversaryRemapTarget) == 20);

	struct HUDGlobalsAnniversaryRemap {
		TagDependency source_bitmap;
		TagReflexive<HUDGlobalsAnniversaryRemapTarget> targets;
	};
	static_assert(sizeof(HUDGlobalsAnniversaryRemap) == 28);

	struct HUDGlobalsWaypointArrow {
		TagString name;
		PADDING(8);
		ColorARGBInt color;
		float opacity;
		float translucency;
		Index on_screen_sequence_index;
		Index off_screen_sequence_index;
		Index occluded_sequence_index;
		PADDING(2);
		PADDING(16);
		HUDGlobalsWaypointArrowFlags flags;
		PADDING(24);
	};
	static_assert(sizeof(HUDGlobalsWaypointArrow) == 104);

	struct HudGlobals {
		HUDInterfaceAnchor anchor;
		PADDING(2);
		PADDING(32);
		Point2DInt anchor_offset;
		float width_scale;
		float height_scale;
		HUDInterfaceScalingFlags scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency single_player_font;
		TagDependency multi_player_font;
		float up_time;
		float fade_time;
		ColorARGB icon_color;
		ColorARGB text_color;
		float text_spacing;
		TagDependency item_message_text;
		TagDependency icon_bitmap;
		TagDependency alternate_icon_text;
		TagReflexive<HUDGlobalsButtonIcon> button_icons;
		ColorARGBInt hud_help_default_color;
		ColorARGBInt hud_help_flashing_color;
		float hud_help_flash_period;
		float hud_help_flash_delay;
		std::int16_t hud_help_number_of_flashes;
		HUDInterfaceFlashFlags hud_help_flash_flags;
		float hud_help_flash_length;
		ColorARGBInt hud_help_disabled_color;
		PADDING(4);
		TagDependency hud_messages;
		ColorARGBInt objective_default_color;
		ColorARGBInt objective_flashing_color;
		float objective_flash_period;
		float objective_flash_delay;
		std::int16_t objective_number_of_flashes;
		HUDInterfaceFlashFlags objective_flash_flags;
		float objective_flash_length;
		ColorARGBInt objective_disabled_color;
		std::int16_t objective_uptime_ticks;
		std::int16_t objective_fade_ticks;
		float top_offset;
		float bottom_offset;
		float left_offset;
		float right_offset;
		PADDING(32);
		TagDependency arrow_bitmap;
		TagReflexive<HUDGlobalsWaypointArrow> waypoint_arrows;
		PADDING(80);
		float hud_scale_in_multiplayer;
		PADDING(256);
		TagDependency default_weapon_hud;
		float motion_sensor_range;
		float motion_sensor_velocity_sensitivity;
		float motion_sensor_scale;
		Rectangle2D default_chapter_title_bounds;
		PADDING(44);
		std::int16_t hud_damage_top_offset;
		std::int16_t hud_damage_bottom_offset;
		std::int16_t hud_damage_left_offset;
		std::int16_t hud_damage_right_offset;
		PADDING(32);
		TagDependency hud_damage_indicator_bitmap;
		Index hud_damage_sequence_index;
		Index hud_damage_multiplayer_sequence_index;
		ColorARGBInt hud_damage_color;
		PADDING(16);
		ColorARGBInt not_much_time_left_default_color;
		ColorARGBInt not_much_time_left_flashing_color;
		float not_much_time_left_flash_period;
		float not_much_time_left_flash_delay;
		std::int16_t not_much_time_left_number_of_flashes;
		HUDInterfaceFlashFlags not_much_time_left_flash_flags;
		float not_much_time_left_flash_length;
		ColorARGBInt not_much_time_left_disabled_color;
		PADDING(4);
		ColorARGBInt time_out_flash_default_color;
		ColorARGBInt time_out_flash_flashing_color;
		float time_out_flash_flash_period;
		float time_out_flash_flash_delay;
		std::int16_t time_out_flash_number_of_flashes;
		HUDInterfaceFlashFlags time_out_flash_flash_flags;
		float time_out_flash_flash_length;
		ColorARGBInt time_out_flash_disabled_color;
		PADDING(4);
		PADDING(40);
		TagDependency carnage_report_bitmap;
		Index loading_begin_text;
		Index loading_end_text;
		Index checkpoint_begin_text;
		Index checkpoint_end_text;
		TagDependency checkpoint_sound;
		TagReflexive<HUDGlobalsAnniversaryRemap> anniversary_hud_remaps;
		PADDING(84);
	};
	static_assert(sizeof(HudGlobals) == 1104);

}

#endif


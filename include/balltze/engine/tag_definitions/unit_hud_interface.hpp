// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__UNIT_HUD_INTERFACE_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__UNIT_HUD_INTERFACE_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "hud_interface_types.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class UnitHUDInterfacePanelType : std::uint16_t {
		INTEGRATED_LIGHT = 0,
	};

	struct UnitHUDInterfaceAuxiliaryOverlayFlags {
		std::uint16_t use_team_color : 1;
	};
	static_assert(sizeof(UnitHUDInterfaceAuxiliaryOverlayFlags) == sizeof(std::uint16_t));

	struct UnitHUDInterfaceHUDSoundLatchedTo {
		std::uint32_t shield_recharging : 1;
		std::uint32_t shield_damaged : 1;
		std::uint32_t shield_low : 1;
		std::uint32_t shield_empty : 1;
		std::uint32_t health_low : 1;
		std::uint32_t health_empty : 1;
		std::uint32_t health_minor_damage : 1;
		std::uint32_t health_major_damage : 1;
	};
	static_assert(sizeof(UnitHUDInterfaceHUDSoundLatchedTo) == sizeof(std::uint32_t));

	struct UnitHUDInterfaceAuxiliaryPanelMeterMoreFlags {
		std::uint32_t show_only_when_active : 1;
		std::uint32_t flash_once_if_activated_while_disabled : 1;
	};
	static_assert(sizeof(UnitHUDInterfaceAuxiliaryPanelMeterMoreFlags) == sizeof(std::uint32_t));

	struct UnitHUDInterfaceAuxiliaryOverlay {
		Point2DInt anchor_offset;
		float width_scale;
		float height_scale;
		HUDInterfaceScalingFlags scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency interface_bitmap;
		ColorARGBInt default_color;
		ColorARGBInt flashing_color;
		float flash_period;
		float flash_delay;
		std::int16_t number_of_flashes;
		HUDInterfaceFlashFlags flash_flags;
		float flash_length;
		ColorARGBInt disabled_color;
		PADDING(4);
		Index sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> multitex_overlay;
		PADDING(4);
		UnitHUDInterfacePanelType type;
		UnitHUDInterfaceAuxiliaryOverlayFlags flags;
		PADDING(24);
	};
	static_assert(sizeof(UnitHUDInterfaceAuxiliaryOverlay) == 132);

	struct UnitHUDInterfaceHUDSound {
		TagDependency sound;
		UnitHUDInterfaceHUDSoundLatchedTo latched_to;
		float scale;
		PADDING(32);
	};
	static_assert(sizeof(UnitHUDInterfaceHUDSound) == 56);

	struct UnitHUDInterfaceAuxiliaryPanel {
		UnitHUDInterfacePanelType type;
		PADDING(2);
		PADDING(16);
		Point2DInt background_anchor_offset;
		float background_width_scale;
		float background_height_scale;
		HUDInterfaceScalingFlags background_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency background_interface_bitmap;
		ColorARGBInt background_default_color;
		ColorARGBInt background_flashing_color;
		float background_flash_period;
		float background_flash_delay;
		std::int16_t background_number_of_flashes;
		HUDInterfaceFlashFlags background_flash_flags;
		float background_flash_length;
		ColorARGBInt background_disabled_color;
		PADDING(4);
		Index background_sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> background_multitex_overlay;
		PADDING(4);
		Point2DInt meter_anchor_offset;
		float meter_width_scale;
		float meter_height_scale;
		HUDInterfaceScalingFlags meter_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency meter_meter_bitmap;
		ColorARGBInt meter_color_at_meter_minimum;
		ColorARGBInt meter_color_at_meter_maximum;
		ColorARGBInt meter_flash_color;
		ColorARGBInt meter_empty_color;
		HUDInterfaceMeterFlags meter_flags;
		std::int8_t meter_minimum_meter_value;
		Index meter_sequence_index;
		std::int8_t meter_alpha_multiplier;
		std::int8_t meter_alpha_bias;
		std::int16_t meter_value_scale;
		float meter_opacity;
		float meter_translucency;
		ColorARGBInt meter_disabled_color;
		float meter_min_alpha;
		PADDING(12);
		float meter_minimum_fraction_cutoff;
		UnitHUDInterfaceAuxiliaryPanelMeterMoreFlags meter_more_flags;
		PADDING(24);
		PADDING(64);
	};
	static_assert(sizeof(UnitHUDInterfaceAuxiliaryPanel) == 324);

	struct UnitHudInterface {
		HUDInterfaceAnchor anchor;
		PADDING(2);
		PADDING(32);
		Point2DInt hud_background_anchor_offset;
		float hud_background_width_scale;
		float hud_background_height_scale;
		HUDInterfaceScalingFlags hud_background_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency hud_background_interface_bitmap;
		ColorARGBInt hud_background_default_color;
		ColorARGBInt hud_background_flashing_color;
		float hud_background_flash_period;
		float hud_background_flash_delay;
		std::int16_t hud_background_number_of_flashes;
		HUDInterfaceFlashFlags hud_background_flash_flags;
		float hud_background_flash_length;
		ColorARGBInt hud_background_disabled_color;
		PADDING(4);
		Index hud_background_sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> hud_background_multitex_overlay;
		PADDING(4);
		Point2DInt shield_panel_background_anchor_offset;
		float shield_panel_background_width_scale;
		float shield_panel_background_height_scale;
		HUDInterfaceScalingFlags shield_panel_background_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency shield_panel_background_interface_bitmap;
		ColorARGBInt shield_panel_background_default_color;
		ColorARGBInt shield_panel_background_flashing_color;
		float shield_panel_background_flash_period;
		float shield_panel_background_flash_delay;
		std::int16_t shield_panel_background_number_of_flashes;
		HUDInterfaceFlashFlags shield_panel_background_flash_flags;
		float shield_panel_background_flash_length;
		ColorARGBInt shield_panel_background_disabled_color;
		PADDING(4);
		Index shield_panel_background_sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> shield_panel_background_multitex_overlay;
		PADDING(4);
		Point2DInt shield_panel_meter_anchor_offset;
		float shield_panel_meter_width_scale;
		float shield_panel_meter_height_scale;
		HUDInterfaceScalingFlags shield_panel_meter_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency shield_panel_meter_meter_bitmap;
		ColorARGBInt shield_panel_meter_color_at_meter_minimum;
		ColorARGBInt shield_panel_meter_color_at_meter_maximum;
		ColorARGBInt shield_panel_meter_flash_color;
		ColorARGBInt shield_panel_meter_empty_color;
		HUDInterfaceMeterFlags shield_panel_meter_flags;
		std::int8_t shield_panel_meter_minimum_meter_value;
		Index shield_panel_meter_sequence_index;
		std::int8_t shield_panel_meter_alpha_multiplier;
		std::int8_t shield_panel_meter_alpha_bias;
		std::int16_t shield_panel_meter_value_scale;
		float shield_panel_meter_opacity;
		float shield_panel_meter_translucency;
		ColorARGBInt shield_panel_meter_disabled_color;
		float shield_panel_meter_min_alpha;
		PADDING(12);
		ColorARGBInt shield_panel_meter_overcharge_minimum_color;
		ColorARGBInt shield_panel_meter_overcharge_maximum_color;
		ColorARGBInt shield_panel_meter_overcharge_flash_color;
		ColorARGBInt shield_panel_meter_overcharge_empty_color;
		PADDING(16);
		Point2DInt health_panel_background_anchor_offset;
		float health_panel_background_width_scale;
		float health_panel_background_height_scale;
		HUDInterfaceScalingFlags health_panel_background_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency health_panel_background_interface_bitmap;
		ColorARGBInt health_panel_background_default_color;
		ColorARGBInt health_panel_background_flashing_color;
		float health_panel_background_flash_period;
		float health_panel_background_flash_delay;
		std::int16_t health_panel_background_number_of_flashes;
		HUDInterfaceFlashFlags health_panel_background_flash_flags;
		float health_panel_background_flash_length;
		ColorARGBInt health_panel_background_disabled_color;
		PADDING(4);
		Index health_panel_background_sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> health_panel_background_multitex_overlay;
		PADDING(4);
		Point2DInt health_panel_meter_anchor_offset;
		float health_panel_meter_width_scale;
		float health_panel_meter_height_scale;
		HUDInterfaceScalingFlags health_panel_meter_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency health_panel_meter_meter_bitmap;
		ColorARGBInt health_panel_meter_color_at_meter_minimum;
		ColorARGBInt health_panel_meter_color_at_meter_maximum;
		ColorARGBInt health_panel_meter_flash_color;
		ColorARGBInt health_panel_meter_empty_color;
		HUDInterfaceMeterFlags health_panel_meter_flags;
		std::int8_t health_panel_meter_minimum_meter_value;
		Index health_panel_meter_sequence_index;
		std::int8_t health_panel_meter_alpha_multiplier;
		std::int8_t health_panel_meter_alpha_bias;
		std::int16_t health_panel_meter_value_scale;
		float health_panel_meter_opacity;
		float health_panel_meter_translucency;
		ColorARGBInt health_panel_meter_disabled_color;
		float health_panel_meter_min_alpha;
		PADDING(12);
		ColorARGBInt health_panel_meter_medium_health_left_color;
		float health_panel_meter_max_color_health_fraction_cutoff;
		float health_panel_meter_min_color_health_fraction_cutoff;
		PADDING(20);
		Point2DInt motion_sensor_background_anchor_offset;
		float motion_sensor_background_width_scale;
		float motion_sensor_background_height_scale;
		HUDInterfaceScalingFlags motion_sensor_background_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency motion_sensor_background_interface_bitmap;
		ColorARGBInt motion_sensor_background_default_color;
		ColorARGBInt motion_sensor_background_flashing_color;
		float motion_sensor_background_flash_period;
		float motion_sensor_background_flash_delay;
		std::int16_t motion_sensor_background_number_of_flashes;
		HUDInterfaceFlashFlags motion_sensor_background_flash_flags;
		float motion_sensor_background_flash_length;
		ColorARGBInt motion_sensor_background_disabled_color;
		PADDING(4);
		Index motion_sensor_background_sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> motion_sensor_background_multitex_overlays;
		PADDING(4);
		Point2DInt motion_sensor_foreground_anchor_offset;
		float motion_sensor_foreground_width_scale;
		float motion_sensor_foreground_height_scale;
		HUDInterfaceScalingFlags motion_sensor_foreground_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency motion_sensor_foreground_interface_bitmap;
		ColorARGBInt motion_sensor_foreground_default_color;
		ColorARGBInt motion_sensor_foreground_flashing_color;
		float motion_sensor_foreground_flash_period;
		float motion_sensor_foreground_flash_delay;
		std::int16_t motion_sensor_foreground_number_of_flashes;
		HUDInterfaceFlashFlags motion_sensor_foreground_flash_flags;
		float motion_sensor_foreground_flash_length;
		ColorARGBInt motion_sensor_foreground_disabled_color;
		PADDING(4);
		Index motion_sensor_foreground_sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> motion_sensor_foreground_multitex_overlays;
		PADDING(4);
		PADDING(32);
		Point2DInt motion_sensor_center_anchor_offset;
		float motion_sensor_center_width_scale;
		float motion_sensor_center_height_scale;
		HUDInterfaceScalingFlags motion_sensor_center_scaling_flags;
		PADDING(2);
		PADDING(20);
		HUDInterfaceAnchor auxiliary_overlay_anchor;
		PADDING(2);
		PADDING(32);
		TagReflexive<UnitHUDInterfaceAuxiliaryOverlay> overlays;
		PADDING(16);
		TagReflexive<UnitHUDInterfaceHUDSound> sounds;
		TagReflexive<UnitHUDInterfaceAuxiliaryPanel> meters;
		PADDING(356);
		PADDING(48);
	};
	static_assert(sizeof(UnitHudInterface) == 1388);

}

#endif


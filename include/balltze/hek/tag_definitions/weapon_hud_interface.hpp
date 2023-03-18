// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__WEAPON_HUD_INTERFACE_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__WEAPON_HUD_INTERFACE_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "hud_interface_types.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class WeaponHUDInterfaceStateAttachedTo : std::uint16_t {
		TOTAL_AMMO = 0,
		LOADED_AMMO,
		HEAT,
		AGE,
		SECONDARY_WEAPON_TOTAL_AMMO,
		SECONDARY_WEAPON_LOADED_AMMO,
		DISTANCE_TO_TARGET,
		ELEVATION_TO_TARGET,
	};

	enum class WeaponHUDInterfaceViewType : std::uint16_t {
		ANY = 0,
		FULLSCREEN,
		SPLITSCREEN,
	};

	enum class WeaponHUDInterfaceCrosshairType : std::uint16_t {
		AIM = 0,
		ZOOM_OVERLAY,
		CHARGE,
		SHOULD_RELOAD,
		FLASH_HEAT,
		FLASH_TOTAL_AMMO,
		FLASH_BATTERY,
		RELOAD_OVERHEAT,
		FLASH_WHEN_FIRING_AND_NO_AMMO,
		FLASH_WHEN_THROWING_AND_NO_GRENADE,
		LOW_AMMO_AND_NONE_LEFT_TO_RELOAD,
		SHOULD_RELOAD_SECONDARY_TRIGGER,
		FLASH_SECONDARY_TOTAL_AMMO,
		FLASH_SECONDARY_RELOAD,
		FLASH_WHEN_FIRING_SECONDARY_TRIGGER_WITH_NO_AMMO,
		LOW_SECONDARY_AMMO_AND_NONE_LEFT_TO_RELOAD,
		PRIMARY_TRIGGER_READY,
		SECONDARY_TRIGGER_READY,
		FLASH_WHEN_FIRING_WITH_DEPLETED_BATTERY,
	};

	struct WeaponHUDInterfaceCrosshairTypeFlags {
		std::uint32_t aim : 1;
		std::uint32_t zoom_overlay : 1;
		std::uint32_t charge : 1;
		std::uint32_t should_reload : 1;
		std::uint32_t flash_heat : 1;
		std::uint32_t flash_total_ammo : 1;
		std::uint32_t flash_battery : 1;
		std::uint32_t reload_overheat : 1;
		std::uint32_t flash_when_firing_and_no_ammo : 1;
		std::uint32_t flash_when_throwing_and_no_grenade : 1;
		std::uint32_t low_ammo_and_none_left_to_reload : 1;
		std::uint32_t should_reload_secondary_trigger : 1;
		std::uint32_t flash_secondary_total_ammo : 1;
		std::uint32_t flash_secondary_reload : 1;
		std::uint32_t flash_when_firing_secondary_trigger_with_no_ammo : 1;
		std::uint32_t low_secondary_ammo_and_none_left_to_reload : 1;
		std::uint32_t primary_trigger_ready : 1;
		std::uint32_t secondary_trigger_ready : 1;
		std::uint32_t flash_when_firing_with_depleted_battery : 1;
	};
	static_assert(sizeof(WeaponHUDInterfaceCrosshairTypeFlags) == sizeof(std::uint32_t));

	struct WeaponHUDInterfaceNumberWeaponSpecificFlags {
		std::uint16_t divide_number_by_clip_size : 1;
	};
	static_assert(sizeof(WeaponHUDInterfaceNumberWeaponSpecificFlags) == sizeof(std::uint16_t));

	struct WeaponHUDInterfaceCrosshairOverlayFlags {
		std::uint32_t flashes_when_active : 1;
		std::uint32_t not_a_sprite : 1;
		std::uint32_t show_only_when_zoomed : 1;
		std::uint32_t show_sniper_data : 1;
		std::uint32_t hide_area_outside_reticle : 1;
		std::uint32_t one_zoom_level : 1;
		std::uint32_t dont_show_when_zoomed : 1;
	};
	static_assert(sizeof(WeaponHUDInterfaceCrosshairOverlayFlags) == sizeof(std::uint32_t));

	struct WeaponHUDInterfaceOverlayType {
		std::uint16_t show_on_flashing : 1;
		std::uint16_t show_on_empty : 1;
		std::uint16_t show_on_reload_overheating : 1;
		std::uint16_t show_on_default : 1;
		std::uint16_t show_always : 1;
	};
	static_assert(sizeof(WeaponHUDInterfaceOverlayType) == sizeof(std::uint16_t));

	struct WeaponHUDInterfaceScreenEffectDefinitionMaskFlags {
		std::uint16_t only_when_zoomed : 1;
	};
	static_assert(sizeof(WeaponHUDInterfaceScreenEffectDefinitionMaskFlags) == sizeof(std::uint16_t));

	struct WeaponHUDInterfaceScreenEffectDefinitionNightVisionFlags {
		std::uint16_t only_when_zoomed : 1;
		std::uint16_t connect_to_flashlight : 1;
		std::uint16_t masked : 1;
	};
	static_assert(sizeof(WeaponHUDInterfaceScreenEffectDefinitionNightVisionFlags) == sizeof(std::uint16_t));

	struct WeaponHUDInterfaceScreenEffectDefinitionDesaturationFlags {
		std::uint16_t only_when_zoomed : 1;
		std::uint16_t connect_to_flashlight : 1;
		std::uint16_t additive : 1;
		std::uint16_t masked : 1;
	};
	static_assert(sizeof(WeaponHUDInterfaceScreenEffectDefinitionDesaturationFlags) == sizeof(std::uint16_t));

	struct WeaponHUDInterfaceFlags {
		std::uint16_t use_parent_hud_flashing_parameters : 1;
	};
	static_assert(sizeof(WeaponHUDInterfaceFlags) == sizeof(std::uint16_t));

	struct WeaponHUDInterfaceStaticElement {
		Memory::BigEndian<WeaponHUDInterfaceStateAttachedTo> state_attached_to;
		PADDING(2);
		Memory::BigEndian<WeaponHUDInterfaceViewType> allowed_view_type;
		Memory::BigEndian<HUDInterfaceChildAnchor> anchor;
		PADDING(28);
		Point2DInt anchor_offset;
		Memory::BigEndian<float> width_scale;
		Memory::BigEndian<float> height_scale;
		Memory::BigEndian<HUDInterfaceScalingFlags> scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency interface_bitmap;
		ColorARGBInt default_color;
		ColorARGBInt flashing_color;
		Memory::BigEndian<float> flash_period;
		Memory::BigEndian<float> flash_delay;
		Memory::BigEndian<std::int16_t> number_of_flashes;
		Memory::BigEndian<HUDInterfaceFlashFlags> flash_flags;
		Memory::BigEndian<float> flash_length;
		ColorARGBInt disabled_color;
		PADDING(4);
		Index sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> multitexture_overlays;
		PADDING(4);
		PADDING(40);
	};
	static_assert(sizeof(WeaponHUDInterfaceStaticElement) == 180);

	struct WeaponHUDInterfaceMeter {
		Memory::BigEndian<WeaponHUDInterfaceStateAttachedTo> state_attached_to;
		PADDING(2);
		Memory::BigEndian<WeaponHUDInterfaceViewType> allowed_view_type;
		Memory::BigEndian<HUDInterfaceChildAnchor> anchor;
		PADDING(28);
		Point2DInt anchor_offset;
		Memory::BigEndian<float> width_scale;
		Memory::BigEndian<float> height_scale;
		Memory::BigEndian<HUDInterfaceScalingFlags> scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency meter_bitmap;
		ColorARGBInt color_at_meter_minimum;
		ColorARGBInt color_at_meter_maximum;
		ColorARGBInt flash_color;
		ColorARGBInt empty_color;
		Memory::BigEndian<HUDInterfaceMeterFlags> flags;
		Memory::BigEndian<std::int8_t> minimum_meter_value;
		Index sequence_index;
		Memory::BigEndian<std::int8_t> alpha_multiplier;
		Memory::BigEndian<std::int8_t> alpha_bias;
		Memory::BigEndian<std::int16_t> value_scale;
		Memory::BigEndian<float> opacity;
		Memory::BigEndian<float> translucency;
		ColorARGBInt disabled_color;
		Memory::BigEndian<float> min_alpha;
		PADDING(12);
		PADDING(40);
	};
	static_assert(sizeof(WeaponHUDInterfaceMeter) == 180);

	struct WeaponHUDInterfaceNumber {
		Memory::BigEndian<WeaponHUDInterfaceStateAttachedTo> state_attached_to;
		PADDING(2);
		Memory::BigEndian<WeaponHUDInterfaceViewType> allowed_view_type;
		Memory::BigEndian<HUDInterfaceChildAnchor> anchor;
		PADDING(28);
		Point2DInt anchor_offset;
		Memory::BigEndian<float> width_scale;
		Memory::BigEndian<float> height_scale;
		Memory::BigEndian<HUDInterfaceScalingFlags> scaling_flags;
		PADDING(2);
		PADDING(20);
		ColorARGBInt default_color;
		ColorARGBInt flashing_color;
		Memory::BigEndian<float> flash_period;
		Memory::BigEndian<float> flash_delay;
		Memory::BigEndian<std::int16_t> number_of_flashes;
		Memory::BigEndian<HUDInterfaceFlashFlags> flash_flags;
		Memory::BigEndian<float> flash_length;
		ColorARGBInt disabled_color;
		PADDING(4);
		Memory::BigEndian<std::int8_t> maximum_number_of_digits;
		Memory::BigEndian<HUDInterfaceNumberFlags> flags;
		Memory::BigEndian<std::int8_t> number_of_fractional_digits;
		PADDING(1);
		PADDING(12);
		Memory::BigEndian<WeaponHUDInterfaceNumberWeaponSpecificFlags> weapon_specific_flags;
		PADDING(2);
		PADDING(36);
	};
	static_assert(sizeof(WeaponHUDInterfaceNumber) == 160);

	struct WeaponHUDInterfaceCrosshairOverlay {
		Point2DInt anchor_offset;
		Memory::BigEndian<float> width_scale;
		Memory::BigEndian<float> height_scale;
		Memory::BigEndian<HUDInterfaceScalingFlags> scaling_flags;
		PADDING(2);
		PADDING(20);
		ColorARGBInt default_color;
		ColorARGBInt flashing_color;
		Memory::BigEndian<float> flash_period;
		Memory::BigEndian<float> flash_delay;
		Memory::BigEndian<std::int16_t> number_of_flashes;
		Memory::BigEndian<HUDInterfaceFlashFlags> flash_flags;
		Memory::BigEndian<float> flash_length;
		ColorARGBInt disabled_color;
		PADDING(4);
		Memory::BigEndian<std::int16_t> frame_rate;
		Index sequence_index;
		Memory::BigEndian<WeaponHUDInterfaceCrosshairOverlayFlags> flags;
		PADDING(32);
	};
	static_assert(sizeof(WeaponHUDInterfaceCrosshairOverlay) == 108);

	struct WeaponHUDInterfaceCrosshair {
		Memory::BigEndian<WeaponHUDInterfaceCrosshairType> crosshair_type;
		PADDING(2);
		Memory::BigEndian<WeaponHUDInterfaceViewType> allowed_view_type;
		PADDING(2);
		PADDING(28);
		TagDependency crosshair_bitmap;
		TagReflexive<WeaponHUDInterfaceCrosshairOverlay> crosshair_overlays;
		PADDING(40);
	};
	static_assert(sizeof(WeaponHUDInterfaceCrosshair) == 104);

	struct WeaponHUDInterfaceOverlay {
		Point2DInt anchor_offset;
		Memory::BigEndian<float> width_scale;
		Memory::BigEndian<float> height_scale;
		Memory::BigEndian<HUDInterfaceScalingFlags> scaling_flags;
		PADDING(2);
		PADDING(20);
		ColorARGBInt default_color;
		ColorARGBInt flashing_color;
		Memory::BigEndian<float> flash_period;
		Memory::BigEndian<float> flash_delay;
		Memory::BigEndian<std::int16_t> number_of_flashes;
		Memory::BigEndian<HUDInterfaceFlashFlags> flash_flags;
		Memory::BigEndian<float> flash_length;
		ColorARGBInt disabled_color;
		PADDING(4);
		Memory::BigEndian<std::int16_t> frame_rate;
		PADDING(2);
		Index sequence_index;
		Memory::BigEndian<WeaponHUDInterfaceOverlayType> type;
		Memory::BigEndian<HUDInterfaceOverlayFlashFlags> flags;
		PADDING(16);
		PADDING(40);
	};
	static_assert(sizeof(WeaponHUDInterfaceOverlay) == 136);

	struct WeaponHUDInterfaceOverlayElement {
		Memory::BigEndian<WeaponHUDInterfaceStateAttachedTo> state_attached_to;
		PADDING(2);
		Memory::BigEndian<WeaponHUDInterfaceViewType> allowed_view_type;
		Memory::BigEndian<HUDInterfaceChildAnchor> anchor;
		PADDING(28);
		TagDependency overlay_bitmap;
		TagReflexive<WeaponHUDInterfaceOverlay> overlays;
		PADDING(40);
	};
	static_assert(sizeof(WeaponHUDInterfaceOverlayElement) == 104);

	struct WeaponHUDInterfaceScreenEffect {
		PADDING(4);
		Memory::BigEndian<WeaponHUDInterfaceScreenEffectDefinitionMaskFlags> mask_flags;
		PADDING(2);
		PADDING(16);
		TagDependency mask_fullscreen;
		TagDependency mask_splitscreen;
		PADDING(8);
		Memory::BigEndian<WeaponHUDInterfaceScreenEffectDefinitionMaskFlags> convolution_flags;
		PADDING(2);
		Angle convolution_fov_in_bounds[2];
		Memory::BigEndian<float> convolution_radius_out_bounds[2];
		PADDING(24);
		Memory::BigEndian<WeaponHUDInterfaceScreenEffectDefinitionNightVisionFlags> even_more_flags;
		Memory::BigEndian<std::int16_t> night_vision_script_source;
		Fraction night_vision_intensity;
		PADDING(24);
		Memory::BigEndian<WeaponHUDInterfaceScreenEffectDefinitionDesaturationFlags> desaturation_flags;
		Memory::BigEndian<std::int16_t> desaturation_script_source;
		Fraction desaturation_intensity;
		ColorRGB effect_tint;
		PADDING(24);
	};
	static_assert(sizeof(WeaponHUDInterfaceScreenEffect) == 184);

	struct WeaponHudInterface {
		TagDependency child_hud;
		Memory::BigEndian<WeaponHUDInterfaceFlags> flags;
		PADDING(2);
		Memory::BigEndian<std::int16_t> total_ammo_cutoff;
		Memory::BigEndian<std::int16_t> loaded_ammo_cutoff;
		Memory::BigEndian<std::int16_t> heat_cutoff;
		Memory::BigEndian<std::int16_t> age_cutoff;
		PADDING(32);
		Memory::BigEndian<HUDInterfaceAnchor> anchor;
		PADDING(2);
		PADDING(32);
		TagReflexive<WeaponHUDInterfaceStaticElement> static_elements;
		TagReflexive<WeaponHUDInterfaceMeter> meter_elements;
		TagReflexive<WeaponHUDInterfaceNumber> number_elements;
		TagReflexive<WeaponHUDInterfaceCrosshair> crosshairs;
		TagReflexive<WeaponHUDInterfaceOverlayElement> overlay_elements;
		Memory::BigEndian<WeaponHUDInterfaceCrosshairTypeFlags> crosshair_types;
		PADDING(12);
		TagReflexive<WeaponHUDInterfaceScreenEffect> screen_effect;
		PADDING(132);
		Index sequence_index;
		Memory::BigEndian<std::int16_t> width_offset;
		Point2DInt offset_from_reference_corner;
		ColorARGBInt override_icon_color;
		Memory::BigEndian<std::int8_t> frame_rate;
		Memory::BigEndian<HUDInterfaceMessagingFlags> more_flags;
		Index text_index;
		PADDING(48);
	};
	static_assert(sizeof(WeaponHudInterface) == 380);

}

#endif


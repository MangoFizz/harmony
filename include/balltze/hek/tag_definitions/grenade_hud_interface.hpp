// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__GRENADE_HUD_INTERFACE_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__GRENADE_HUD_INTERFACE_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "hud_interface_types.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct GrenadeHUDInterfaceOverlayType {
		std::uint16_t show_on_flashing : 1;
		std::uint16_t show_on_empty : 1;
		std::uint16_t show_on_default : 1;
		std::uint16_t show_always : 1;
	};
	static_assert(sizeof(GrenadeHUDInterfaceOverlayType) == sizeof(std::uint16_t));

	struct GrenadeHUDInterfaceSoundLatchedTo {
		std::uint32_t low_grenade_count : 1;
		std::uint32_t no_grenades_left : 1;
		std::uint32_t throw_on_no_grenades : 1;
	};
	static_assert(sizeof(GrenadeHUDInterfaceSoundLatchedTo) == sizeof(std::uint32_t));

	struct GrenadeHUDInterfaceOverlay {
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
		Memory::BigEndian<float> frame_rate;
		Index sequence_index;
		Memory::BigEndian<GrenadeHUDInterfaceOverlayType> type;
		Memory::BigEndian<HUDInterfaceOverlayFlashFlags> flags;
		PADDING(16);
		PADDING(40);
	};
	static_assert(sizeof(GrenadeHUDInterfaceOverlay) == 136);

	struct GrenadeHUDInterfaceSound {
		TagDependency sound;
		Memory::BigEndian<GrenadeHUDInterfaceSoundLatchedTo> latched_to;
		Memory::BigEndian<float> scale;
		PADDING(32);
	};
	static_assert(sizeof(GrenadeHUDInterfaceSound) == 56);

	struct GrenadeHudInterface {
		Memory::BigEndian<HUDInterfaceAnchor> anchor;
		PADDING(2);
		PADDING(32);
		Point2DInt background_anchor_offset;
		Memory::BigEndian<float> background_width_scale;
		Memory::BigEndian<float> background_height_scale;
		Memory::BigEndian<HUDInterfaceScalingFlags> background_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency background_interface_bitmap;
		ColorARGBInt background_default_color;
		ColorARGBInt background_flashing_color;
		Memory::BigEndian<float> background_flash_period;
		Memory::BigEndian<float> background_flash_delay;
		Memory::BigEndian<std::int16_t> background_number_of_flashes;
		Memory::BigEndian<HUDInterfaceFlashFlags> background_flash_flags;
		Memory::BigEndian<float> background_flash_length;
		ColorARGBInt background_disabled_color;
		PADDING(4);
		Index background_sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> background_multitexture_overlays;
		PADDING(4);
		Point2DInt total_grenades_background_anchor_offset;
		Memory::BigEndian<float> total_grenades_background_width_scale;
		Memory::BigEndian<float> total_grenades_background_height_scale;
		Memory::BigEndian<HUDInterfaceScalingFlags> total_grenades_background_scaling_flags;
		PADDING(2);
		PADDING(20);
		TagDependency total_grenades_background_interface_bitmap;
		ColorARGBInt total_grenades_background_default_color;
		ColorARGBInt total_grenades_background_flashing_color;
		Memory::BigEndian<float> total_grenades_background_flash_period;
		Memory::BigEndian<float> total_grenades_background_flash_delay;
		Memory::BigEndian<std::int16_t> total_grenades_background_number_of_flashes;
		Memory::BigEndian<HUDInterfaceFlashFlags> total_grenades_background_flash_flags;
		Memory::BigEndian<float> total_grenades_background_flash_length;
		ColorARGBInt total_grenades_background_disabled_color;
		PADDING(4);
		Index total_grenades_background_sequence_index;
		PADDING(2);
		TagReflexive<HUDInterfaceMultitextureOverlay> total_grenades_background_multitexture_overlays;
		PADDING(4);
		Point2DInt total_grenades_numbers_anchor_offset;
		Memory::BigEndian<float> total_grenades_numbers_width_scale;
		Memory::BigEndian<float> total_grenades_numbers_height_scale;
		Memory::BigEndian<HUDInterfaceScalingFlags> total_grenades_numbers_scaling_flags;
		PADDING(2);
		PADDING(20);
		ColorARGBInt total_grenades_numbers_default_color;
		ColorARGBInt total_grenades_numbers_flashing_color;
		Memory::BigEndian<float> total_grenades_numbers_flash_period;
		Memory::BigEndian<float> total_grenades_numbers_flash_delay;
		Memory::BigEndian<std::int16_t> total_grenades_numbers_number_of_flashes;
		Memory::BigEndian<HUDInterfaceFlashFlags> total_grenades_numbers_flash_flags;
		Memory::BigEndian<float> total_grenades_numbers_flash_length;
		ColorARGBInt total_grenades_numbers_disabled_color;
		PADDING(4);
		Memory::BigEndian<std::int8_t> total_grenades_numbers_maximum_number_of_digits;
		Memory::BigEndian<HUDInterfaceNumberFlags> total_grenades_numbers_flags;
		Memory::BigEndian<std::int8_t> total_grenades_numbers_number_of_fractional_digits;
		PADDING(1);
		PADDING(12);
		Memory::BigEndian<std::int16_t> flash_cutoff;
		PADDING(2);
		TagDependency total_grenades_overlay_bitmap;
		TagReflexive<GrenadeHUDInterfaceOverlay> total_grenades_overlays;
		TagReflexive<GrenadeHUDInterfaceSound> total_grenades_warning_sounds;
		PADDING(68);
		Index messaging_information_sequence_index;
		Memory::BigEndian<std::int16_t> messaging_information_width_offset;
		Point2DInt messaging_information_offset_from_reference_corner;
		ColorARGBInt messaging_information_override_icon_color;
		Memory::BigEndian<std::int8_t> messaging_information_frame_rate;
		Memory::BigEndian<HUDInterfaceMessagingFlags> messaging_information_flags;
		Index messaging_information_text_index;
		PADDING(48);
	};
	static_assert(sizeof(GrenadeHudInterface) == 504);

}

#endif


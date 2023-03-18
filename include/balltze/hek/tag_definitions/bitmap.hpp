// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__BITMAP_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__BITMAP_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class BitmapDataType : std::uint16_t {
		_2D_TEXTURE = 0,
		_3D_TEXTURE,
		CUBE_MAP,
		WHITE,
	};

	enum class BitmapDataFormat : std::uint16_t {
		A8 = 0,
		Y8,
		AY8,
		A8Y8,
		UNUSED1,
		UNUSED2,
		R5G6B5,
		UNUSED3,
		A1R5G5B5,
		A4R4G4B4,
		X8R8G8B8,
		A8R8G8B8,
		UNUSED4,
		UNUSED5,
		DXT1,
		DXT3,
		DXT5,
		P8_BUMP,
	};

	enum class BitmapType : std::uint16_t {
		_2D_TEXTURES = 0,
		_3D_TEXTURES,
		CUBE_MAPS,
		SPRITES,
		INTERFACE_BITMAPS,
	};

	enum class BitmapFormat : std::uint16_t {
		DXT1 = 0,
		DXT3,
		DXT5,
		_16_BIT,
		_32_BIT,
		MONOCHROME,
	};

	enum class BitmapUsage : std::uint16_t {
		ALPHA_BLEND = 0,
		DEFAULT,
		HEIGHT_MAP,
		DETAIL_MAP,
		LIGHT_MAP,
		VECTOR_MAP,
	};

	enum class BitmapSpriteBudgetSize : std::uint16_t {
		_32X32 = 0,
		_64X64,
		_128X128,
		_256X256,
		_512X512,
		_1024X1024,
	};

	enum class BitmapSpriteUsage : std::uint16_t {
		BLEND_ADD_SUBTRACT_MAX = 0,
		MULTIPLY_MIN,
		DOUBLE_MULTIPLY,
	};

	struct BitmapDataFlags {
		std::uint16_t power_of_two_dimensions : 1;
		std::uint16_t compressed : 1;
		std::uint16_t palettized : 1;
		std::uint16_t swizzled : 1;
		std::uint16_t linear : 1;
		std::uint16_t v16u16 : 1;
		std::uint16_t unused : 1;
		std::uint16_t make_it_actually_work : 1;
		std::uint16_t external : 1;
		std::uint16_t environment : 1;
	};
	static_assert(sizeof(BitmapDataFlags) == sizeof(std::uint16_t));

	struct BitmapFlags {
		std::uint16_t enable_diffusion_dithering : 1;
		std::uint16_t disable_height_map_compression : 1;
		std::uint16_t uniform_sprite_sequences : 1;
		std::uint16_t filthy_sprite_bug_fix : 1;
		std::uint16_t half_hud_scale : 1;
	};
	static_assert(sizeof(BitmapFlags) == sizeof(std::uint16_t));

	struct BitmapGroupSprite {
		Index bitmap_index;
		PADDING(2);
		PADDING(4);
		Memory::BigEndian<float> left;
		Memory::BigEndian<float> right;
		Memory::BigEndian<float> top;
		Memory::BigEndian<float> bottom;
		Point2D registration_point;
	};
	static_assert(sizeof(BitmapGroupSprite) == 32);

	struct BitmapGroupSequence {
		TagString name;
		Index first_bitmap_index;
		Memory::BigEndian<std::uint16_t> bitmap_count;
		PADDING(16);
		TagReflexive<BitmapGroupSprite> sprites;
	};
	static_assert(sizeof(BitmapGroupSequence) == 64);

	struct BitmapData {
		TagFourCC bitmap_class;
		Memory::BigEndian<std::uint16_t> width;
		Memory::BigEndian<std::uint16_t> height;
		Memory::BigEndian<std::uint16_t> depth;
		Memory::BigEndian<BitmapDataType> type;
		Memory::BigEndian<BitmapDataFormat> format;
		Memory::BigEndian<BitmapDataFlags> flags;
		Point2DInt registration_point;
		Memory::BigEndian<std::uint16_t> mipmap_count;
		PADDING(2);
		Memory::BigEndian<std::uint32_t> pixel_data_offset;
		Memory::BigEndian<std::uint32_t> pixel_data_size;
		TagHandle bitmap_tag_id;
		std::byte *pointer;
		PADDING(4);
		PADDING(4);
	};
	static_assert(sizeof(BitmapData) == 48);

	struct Bitmap {
		Memory::BigEndian<BitmapType> type;
		Memory::BigEndian<BitmapFormat> encoding_format;
		Memory::BigEndian<BitmapUsage> usage;
		Memory::BigEndian<BitmapFlags> flags;
		Fraction detail_fade_factor;
		Fraction sharpen_amount;
		Fraction bump_height;
		Memory::BigEndian<BitmapSpriteBudgetSize> sprite_budget_size;
		Memory::BigEndian<std::uint16_t> sprite_budget_count;
		Memory::BigEndian<std::uint16_t> color_plate_width;
		Memory::BigEndian<std::uint16_t> color_plate_height;
		TagDataOffset compressed_color_plate_data;
		TagDataOffset processed_pixel_data;
		Memory::BigEndian<float> blur_filter_size;
		Memory::BigEndian<float> alpha_bias;
		Memory::BigEndian<std::uint16_t> mipmap_count;
		Memory::BigEndian<BitmapSpriteUsage> sprite_usage;
		Memory::BigEndian<std::uint16_t> sprite_spacing;
		PADDING(2);
		TagReflexive<BitmapGroupSequence> bitmap_group_sequence;
		TagReflexive<BitmapData> bitmap_data;
	};
	static_assert(sizeof(Bitmap) == 108);

}

#endif


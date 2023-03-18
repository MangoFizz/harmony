// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__ENUM_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__ENUM_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class FramebufferBlendFunction : std::uint16_t {
		ALPHA_BLEND = 0,
		MULTIPLY,
		DOUBLE_MULTIPLY,
		ADD,
		SUBTRACT,
		COMPONENT_MIN,
		COMPONENT_MAX,
		ALPHA_MULTIPLY_ADD,
	};

	enum class FramebufferFadeMode : std::uint16_t {
		NONE = 0,
		FADE_WHEN_PERPENDICULAR,
		FADE_WHEN_PARALLEL,
	};

	enum class FunctionOut : std::uint16_t {
		NONE = 0,
		A_OUT,
		B_OUT,
		C_OUT,
		D_OUT,
	};

	enum class WaveFunction : std::uint16_t {
		ONE = 0,
		ZERO,
		COSINE,
		COSINE_VARIABLE_PERIOD,
		DIAGONAL_WAVE,
		DIAGONAL_WAVE_VARIABLE_PERIOD,
		SLIDE,
		SLIDE_VARIABLE_PERIOD,
		NOISE,
		JITTER,
		WANDER,
		SPARK,
	};

	enum class MaterialType : std::uint16_t {
		DIRT = 0,
		SAND,
		STONE,
		SNOW,
		WOOD,
		METAL_HOLLOW,
		METAL_THIN,
		METAL_THICK,
		RUBBER,
		GLASS,
		FORCE_FIELD,
		GRUNT,
		HUNTER_ARMOR,
		HUNTER_SKIN,
		ELITE,
		JACKAL,
		JACKAL_ENERGY_SHIELD,
		ENGINEER_SKIN,
		ENGINEER_FORCE_FIELD,
		FLOOD_COMBAT_FORM,
		FLOOD_CARRIER_FORM,
		CYBORG_ARMOR,
		CYBORG_ENERGY_SHIELD,
		HUMAN_ARMOR,
		HUMAN_SKIN,
		SENTINEL,
		MONITOR,
		PLASTIC,
		WATER,
		LEAVES,
		ELITE_ENERGY_SHIELD,
		ICE,
		HUNTER_SHIELD,
	};

	enum class FunctionType : std::uint16_t {
		LINEAR = 0,
		EARLY,
		VERY_EARLY,
		LATE,
		VERY_LATE,
		COSINE,
	};

	enum class FunctionBoundsMode : std::uint16_t {
		CLIP = 0,
		CLIP_AND_NORMALIZE,
		SCALE_TO_FIT,
	};

	enum class FunctionScaleBy : std::uint16_t {
		NONE = 0,
		A_IN,
		B_IN,
		C_IN,
		D_IN,
		A_OUT,
		B_OUT,
		C_OUT,
		D_OUT,
	};

	enum class FunctionNameNullable : std::uint16_t {
		NONE = 0,
		A,
		B,
		C,
		D,
	};

	enum class GrenadeType : std::uint16_t {
		HUMAN_FRAGMENTATION = 0,
		COVENANT_PLASMA,
		GRENADE_TYPE_2,
		GRENADE_TYPE_3,
	};

	enum class VertexType : std::uint16_t {
		STRUCTURE_BSP_UNCOMPRESSED_RENDERED_VERTICES = 0,
		STRUCTURE_BSP_COMPRESSED_RENDERED_VERTICES,
		STRUCTURE_BSP_UNCOMPRESSED_LIGHTMAP_VERTICES,
		STRUCTURE_BSP_COMPRESSED_LIGHTMAP_VERTICES,
		MODEL_UNCOMPRESSED,
		MODEL_COMPRESSED,
	};

}

#endif


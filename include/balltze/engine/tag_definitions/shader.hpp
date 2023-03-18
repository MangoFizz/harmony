// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class ShaderDetailLevel : std::uint16_t {
		HIGH = 0,
		MEDIUM,
		LOW,
		TURD,
	};

	enum class ShaderColorFunctionType : std::uint16_t {
		CURRENT = 0,
		NEXT_MAP,
		MULTIPLY,
		DOUBLE_MULTIPLY,
		ADD,
		ADD_SIGNED_CURRENT,
		ADD_SIGNED_NEXT_MAP,
		SUBTRACT_CURRENT,
		SUBTRACT_NEXT_MAP,
		BLEND_CURRENT_ALPHA,
		BLEND_CURRENT_ALPHA_INVERSE,
		BLEND_NEXT_MAP_ALPHA,
		BLEND_NEXT_MAP_ALPHA_INVERSE,
	};

	enum class ShaderFirstMapType : std::uint16_t {
		_2D_MAP = 0,
		FIRST_MAP_IS_REFLECTION_CUBE_MAP,
		FIRST_MAP_IS_OBJECT_CENTERED_CUBE_MAP,
		FIRST_MAP_IS_VIEWER_CENTERED_CUBE_MAP,
	};

	enum class ShaderType : std::uint16_t {
		UNUSED = 0,
		UNUSED1,
		UNUSED2,
		SHADER_ENVIRONMENT,
		SHADER_MODEL,
		SHADER_TRANSPARENT_GENERIC,
		SHADER_TRANSPARENT_CHICAGO,
		SHADER_TRANSPARENT_CHICAGO_EXTENDED,
		SHADER_TRANSPARENT_WATER,
		SHADER_TRANSPARENT_GLASS,
		SHADER_TRANSPARENT_METER,
		SHADER_TRANSPARENT_PLASMA,
	};

	enum class ShaderDetailFunction : std::uint16_t {
		DOUBLE_BIASED_MULTIPLY = 0,
		MULTIPLY,
		DOUBLE_BIASED_ADD,
	};

	struct ShaderFlags {
		std::uint16_t simple_parameterization : 1;
		std::uint16_t ignore_normals : 1;
		std::uint16_t transparent_lit : 1;
	};
	static_assert(sizeof(ShaderFlags) == sizeof(std::uint16_t));

	struct ShaderPhysicsFlags {
		std::uint16_t unused : 1;
	};
	static_assert(sizeof(ShaderPhysicsFlags) == sizeof(std::uint16_t));

	struct ShaderTransparentExtraLayer {
		TagDependency shader;
	};
	static_assert(sizeof(ShaderTransparentExtraLayer) == 16);

	struct Shader {
		ShaderFlags shader_flags;
		ShaderDetailLevel detail_level;
		float power;
		ColorRGB color_of_emitted_light;
		ColorRGB tint_color;
		ShaderPhysicsFlags physics_flags;
		MaterialType material_type;
		std::uint16_t shader_type;
		PADDING(2);
	};
	static_assert(sizeof(Shader) == 40);

}

#endif


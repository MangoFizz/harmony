// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_ENVIRONMENT_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__SHADER_ENVIRONMENT_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class ShaderEnvironmentType : std::uint16_t {
		NORMAL = 0,
		BLENDED,
		BLENDED_BASE_SPECULAR,
	};

	enum class ShaderEnvironmentReflectionType : std::uint16_t {
		BUMPED_CUBE_MAP = 0,
		FLAT_CUBE_MAP,
		BUMPED_RADIOSITY,
	};

	struct ShaderEnvironmentFlags {
		std::uint16_t alpha_tested : 1;
		std::uint16_t bump_map_is_specular_mask : 1;
		std::uint16_t true_atmospheric_fog : 1;
	};
	static_assert(sizeof(ShaderEnvironmentFlags) == sizeof(std::uint16_t));

	struct ShaderEnvironmentDiffuseFlags {
		std::uint16_t rescale_detail_maps : 1;
		std::uint16_t rescale_bump_map : 1;
	};
	static_assert(sizeof(ShaderEnvironmentDiffuseFlags) == sizeof(std::uint16_t));

	struct ShaderEnvironmentSpecularFlags {
		std::uint16_t overbright : 1;
		std::uint16_t extra_shiny : 1;
		std::uint16_t lightmap_is_specular : 1;
	};
	static_assert(sizeof(ShaderEnvironmentSpecularFlags) == sizeof(std::uint16_t));

	struct ShaderEnvironmentReflectionFlags {
		std::uint16_t dynamic_mirror : 1;
	};
	static_assert(sizeof(ShaderEnvironmentReflectionFlags) == sizeof(std::uint16_t));

	struct ShaderEnvironment : public Shader {
		ShaderEnvironmentFlags shader_environment_flags;
		ShaderEnvironmentType shader_environment_type;
		float lens_flare_spacing;
		TagDependency lens_flare;
		PADDING(44);
		ShaderEnvironmentDiffuseFlags diffuse_flags;
		PADDING(2);
		PADDING(24);
		TagDependency base_map;
		PADDING(24);
		ShaderDetailFunction detail_map_function;
		PADDING(2);
		float primary_detail_map_scale;
		TagDependency primary_detail_map;
		float secondary_detail_map_scale;
		TagDependency secondary_detail_map;
		PADDING(24);
		ShaderDetailFunction micro_detail_map_function;
		PADDING(2);
		float micro_detail_map_scale;
		TagDependency micro_detail_map;
		ColorRGB material_color;
		PADDING(12);
		float bump_map_scale;
		TagDependency bump_map;
		Point2D bump_map_scale_xy;
		PADDING(16);
		WaveFunction u_animation_function;
		PADDING(2);
		float u_animation_period;
		float u_animation_scale;
		WaveFunction v_animation_function;
		PADDING(2);
		float v_animation_period;
		float v_animation_scale;
		PADDING(24);
		IsUnfilteredFlag self_illumination_flags;
		PADDING(2);
		PADDING(24);
		ColorRGB primary_on_color;
		ColorRGB primary_off_color;
		WaveFunction primary_animation_function;
		PADDING(2);
		float primary_animation_period;
		float primary_animation_phase;
		PADDING(24);
		ColorRGB secondary_on_color;
		ColorRGB secondary_off_color;
		WaveFunction secondary_animation_function;
		PADDING(2);
		float secondary_animation_period;
		float secondary_animation_phase;
		PADDING(24);
		ColorRGB plasma_on_color;
		ColorRGB plasma_off_color;
		WaveFunction plasma_animation_function;
		PADDING(2);
		float plasma_animation_period;
		float plasma_animation_phase;
		PADDING(24);
		float map_scale;
		TagDependency map;
		PADDING(24);
		ShaderEnvironmentSpecularFlags specular_flags;
		PADDING(2);
		PADDING(16);
		Fraction brightness;
		PADDING(20);
		ColorRGB perpendicular_color;
		ColorRGB parallel_color;
		PADDING(16);
		ShaderEnvironmentReflectionFlags reflection_flags;
		ShaderEnvironmentReflectionType reflection_type;
		Fraction lightmap_brightness_scale;
		PADDING(28);
		Fraction perpendicular_brightness;
		Fraction parallel_brightness;
		PADDING(16);
		PADDING(8);
		PADDING(16);
		TagDependency reflection_cube_map;
		PADDING(16);
	};
	static_assert(sizeof(ShaderEnvironment) == 836);

}

#endif


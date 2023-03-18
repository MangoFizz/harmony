// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__SHADER_ENVIRONMENT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__SHADER_ENVIRONMENT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "shader.hpp"

namespace Balltze::HEK::TagDefinitions { 
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
		Memory::BigEndian<ShaderEnvironmentFlags> shader_environment_flags;
		Memory::BigEndian<ShaderEnvironmentType> shader_environment_type;
		Memory::BigEndian<float> lens_flare_spacing;
		TagDependency lens_flare;
		PADDING(44);
		Memory::BigEndian<ShaderEnvironmentDiffuseFlags> diffuse_flags;
		PADDING(2);
		PADDING(24);
		TagDependency base_map;
		PADDING(24);
		Memory::BigEndian<ShaderDetailFunction> detail_map_function;
		PADDING(2);
		Memory::BigEndian<float> primary_detail_map_scale;
		TagDependency primary_detail_map;
		Memory::BigEndian<float> secondary_detail_map_scale;
		TagDependency secondary_detail_map;
		PADDING(24);
		Memory::BigEndian<ShaderDetailFunction> micro_detail_map_function;
		PADDING(2);
		Memory::BigEndian<float> micro_detail_map_scale;
		TagDependency micro_detail_map;
		ColorRGB material_color;
		PADDING(12);
		Memory::BigEndian<float> bump_map_scale;
		TagDependency bump_map;
		Point2D bump_map_scale_xy;
		PADDING(16);
		Memory::BigEndian<WaveFunction> u_animation_function;
		PADDING(2);
		Memory::BigEndian<float> u_animation_period;
		Memory::BigEndian<float> u_animation_scale;
		Memory::BigEndian<WaveFunction> v_animation_function;
		PADDING(2);
		Memory::BigEndian<float> v_animation_period;
		Memory::BigEndian<float> v_animation_scale;
		PADDING(24);
		Memory::BigEndian<IsUnfilteredFlag> self_illumination_flags;
		PADDING(2);
		PADDING(24);
		ColorRGB primary_on_color;
		ColorRGB primary_off_color;
		Memory::BigEndian<WaveFunction> primary_animation_function;
		PADDING(2);
		Memory::BigEndian<float> primary_animation_period;
		Memory::BigEndian<float> primary_animation_phase;
		PADDING(24);
		ColorRGB secondary_on_color;
		ColorRGB secondary_off_color;
		Memory::BigEndian<WaveFunction> secondary_animation_function;
		PADDING(2);
		Memory::BigEndian<float> secondary_animation_period;
		Memory::BigEndian<float> secondary_animation_phase;
		PADDING(24);
		ColorRGB plasma_on_color;
		ColorRGB plasma_off_color;
		Memory::BigEndian<WaveFunction> plasma_animation_function;
		PADDING(2);
		Memory::BigEndian<float> plasma_animation_period;
		Memory::BigEndian<float> plasma_animation_phase;
		PADDING(24);
		Memory::BigEndian<float> map_scale;
		TagDependency map;
		PADDING(24);
		Memory::BigEndian<ShaderEnvironmentSpecularFlags> specular_flags;
		PADDING(2);
		PADDING(16);
		Fraction brightness;
		PADDING(20);
		ColorRGB perpendicular_color;
		ColorRGB parallel_color;
		PADDING(16);
		Memory::BigEndian<ShaderEnvironmentReflectionFlags> reflection_flags;
		Memory::BigEndian<ShaderEnvironmentReflectionType> reflection_type;
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


// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__LIGHTNING_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__LIGHTNING_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "particle.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct LightningMarkerFlag {
		std::uint16_t not_connected_to_next_marker : 1;
	};
	static_assert(sizeof(LightningMarkerFlag) == sizeof(std::uint16_t));

	struct LightningMarker {
		TagString attachment_marker;
		Memory::BigEndian<LightningMarkerFlag> flags;
		PADDING(2);
		Memory::BigEndian<std::int16_t> octaves_to_next_marker;
		PADDING(2);
		PADDING(76);
		Vector3D random_position_bounds;
		Memory::BigEndian<float> random_jitter;
		Memory::BigEndian<float> thickness;
		ColorARGB tint;
		PADDING(76);
	};
	static_assert(sizeof(LightningMarker) == 228);

	struct LightningShader {
		PADDING(36);
		Memory::BigEndian<std::uint32_t> make_it_work;
		Memory::BigEndian<ParticleShaderFlags> shader_flags;
		Memory::BigEndian<FramebufferBlendFunction> framebuffer_blend_function;
		Memory::BigEndian<FramebufferFadeMode> framebuffer_fade_mode;
		Memory::BigEndian<IsUnfilteredFlag> map_flags;
		PADDING(28);
		PADDING(12);
		Memory::BigEndian<std::uint32_t> some_more_stuff_that_should_be_set_for_some_reason;
		PADDING(2);
		PADDING(2);
		PADDING(56);
		PADDING(28);
	};
	static_assert(sizeof(LightningShader) == 180);

	struct Lightning {
		PADDING(2);
		Memory::BigEndian<std::int16_t> count;
		PADDING(16);
		Memory::BigEndian<float> near_fade_distance;
		Memory::BigEndian<float> far_fade_distance;
		PADDING(16);
		Memory::BigEndian<FunctionOut> jitter_scale_source;
		Memory::BigEndian<FunctionOut> thickness_scale_source;
		Memory::BigEndian<FunctionNameNullable> tint_modulation_source;
		Memory::BigEndian<FunctionOut> brightness_scale_source;
		TagDependency bitmap;
		PADDING(84);
		TagReflexive<LightningMarker> markers;
		TagReflexive<LightningShader> shader;
		PADDING(88);
	};
	static_assert(sizeof(Lightning) == 264);

}

#endif


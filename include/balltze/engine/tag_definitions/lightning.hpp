// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__LIGHTNING_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__LIGHTNING_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "particle.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct LightningMarkerFlag {
		std::uint16_t not_connected_to_next_marker : 1;
	};
	static_assert(sizeof(LightningMarkerFlag) == sizeof(std::uint16_t));

	struct LightningMarker {
		TagString attachment_marker;
		LightningMarkerFlag flags;
		PADDING(2);
		std::int16_t octaves_to_next_marker;
		PADDING(2);
		PADDING(76);
		Vector3D random_position_bounds;
		float random_jitter;
		float thickness;
		ColorARGB tint;
		PADDING(76);
	};
	static_assert(sizeof(LightningMarker) == 228);

	struct LightningShader {
		PADDING(36);
		std::uint32_t make_it_work;
		ParticleShaderFlags shader_flags;
		FramebufferBlendFunction framebuffer_blend_function;
		FramebufferFadeMode framebuffer_fade_mode;
		IsUnfilteredFlag map_flags;
		PADDING(28);
		PADDING(12);
		std::uint32_t some_more_stuff_that_should_be_set_for_some_reason;
		PADDING(2);
		PADDING(2);
		PADDING(56);
		PADDING(28);
	};
	static_assert(sizeof(LightningShader) == 180);

	struct Lightning {
		PADDING(2);
		std::int16_t count;
		PADDING(16);
		float near_fade_distance;
		float far_fade_distance;
		PADDING(16);
		FunctionOut jitter_scale_source;
		FunctionOut thickness_scale_source;
		FunctionNameNullable tint_modulation_source;
		FunctionOut brightness_scale_source;
		TagDependency bitmap;
		PADDING(84);
		TagReflexive<LightningMarker> markers;
		TagReflexive<LightningShader> shader;
		PADDING(88);
	};
	static_assert(sizeof(Lightning) == 264);

}

#endif


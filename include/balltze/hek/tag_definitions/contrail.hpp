// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__CONTRAIL_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__CONTRAIL_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "particle.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class ContrailRenderType : std::uint16_t {
		VERTICAL_ORIENTATION = 0,
		HORIZONTAL_ORIENTATION,
		MEDIA_MAPPED,
		GROUND_MAPPED,
		VIEWER_FACING,
		DOUBLE_MARKER_LINKED,
	};

	struct ContrailPointStateScaleFlags {
		std::uint32_t duration : 1;
		std::uint32_t duration_delta : 1;
		std::uint32_t transition_duration : 1;
		std::uint32_t transition_duration_delta : 1;
		std::uint32_t width : 1;
		std::uint32_t color : 1;
	};
	static_assert(sizeof(ContrailPointStateScaleFlags) == sizeof(std::uint32_t));

	struct ContrailFlags {
		std::uint16_t first_point_unfaded : 1;
		std::uint16_t last_point_unfaded : 1;
		std::uint16_t points_start_pinned_to_media : 1;
		std::uint16_t points_start_pinned_to_ground : 1;
		std::uint16_t points_always_pinned_to_media : 1;
		std::uint16_t points_always_pinned_to_ground : 1;
		std::uint16_t edge_effect_fades_slowly : 1;
	};
	static_assert(sizeof(ContrailFlags) == sizeof(std::uint16_t));

	struct ContrailScaleFlags {
		std::uint16_t point_generation_rate : 1;
		std::uint16_t point_velocity : 1;
		std::uint16_t point_velocity_delta : 1;
		std::uint16_t point_velocity_cone_angle : 1;
		std::uint16_t inherited_velocity_fraction : 1;
		std::uint16_t sequence_animation_rate : 1;
		std::uint16_t texture_scale_u : 1;
		std::uint16_t texture_scale_v : 1;
		std::uint16_t texture_animation_u : 1;
		std::uint16_t texture_animation_v : 1;
	};
	static_assert(sizeof(ContrailScaleFlags) == sizeof(std::uint16_t));

	struct ContrailPointState {
		Memory::BigEndian<float> duration[2];
		Memory::BigEndian<float> transition_duration[2];
		TagDependency physics;
		PADDING(32);
		Memory::BigEndian<float> width;
		ColorARGB color_lower_bound;
		ColorARGB color_upper_bound;
		Memory::BigEndian<ContrailPointStateScaleFlags> scale_flags;
	};
	static_assert(sizeof(ContrailPointState) == 104);

	struct Contrail {
		Memory::BigEndian<ContrailFlags> flags;
		Memory::BigEndian<ContrailScaleFlags> scale_flags;
		Memory::BigEndian<float> point_generation_rate;
		Memory::BigEndian<float> point_velocity[2];
		Angle point_velocity_cone_angle;
		Fraction inherited_velocity_fraction;
		Memory::BigEndian<ContrailRenderType> render_type;
		PADDING(2);
		Memory::BigEndian<float> texture_repeats_u;
		Memory::BigEndian<float> texture_repeats_v;
		Memory::BigEndian<float> texture_animation_u;
		Memory::BigEndian<float> texture_animation_v;
		Memory::BigEndian<float> animation_rate;
		TagDependency bitmap;
		Index first_sequence_index;
		Memory::BigEndian<std::int16_t> sequence_count;
		PADDING(64);
		PADDING(36);
		Memory::BigEndian<std::uint32_t> unknown_int;
		Memory::BigEndian<ParticleShaderFlags> shader_flags;
		Memory::BigEndian<FramebufferBlendFunction> framebuffer_blend_function;
		Memory::BigEndian<FramebufferFadeMode> framebuffer_fade_mode;
		Memory::BigEndian<IsUnfilteredFlag> map_flags;
		PADDING(12);
		PADDING(16);
		TagDependency secondary_bitmap;
		Memory::BigEndian<ParticleAnchor> anchor;
		Memory::BigEndian<IsUnfilteredFlag> secondary_map_flags;
		Memory::BigEndian<FunctionOut> u_animation_source;
		Memory::BigEndian<WaveFunction> u_animation_function;
		Memory::BigEndian<float> u_animation_period;
		Memory::BigEndian<float> u_animation_phase;
		Memory::BigEndian<float> u_animation_scale;
		Memory::BigEndian<FunctionOut> v_animation_source;
		Memory::BigEndian<WaveFunction> v_animation_function;
		Memory::BigEndian<float> v_animation_period;
		Memory::BigEndian<float> v_animation_phase;
		Memory::BigEndian<float> v_animation_scale;
		Memory::BigEndian<FunctionOut> rotation_animation_source;
		Memory::BigEndian<WaveFunction> rotation_animation_function;
		Memory::BigEndian<float> rotation_animation_period;
		Memory::BigEndian<float> rotation_animation_phase;
		Angle rotation_animation_scale;
		Point2D rotation_animation_center;
		PADDING(4);
		Memory::BigEndian<float> zsprite_radius_scale;
		PADDING(20);
		TagReflexive<ContrailPointState> point_states;
	};
	static_assert(sizeof(Contrail) == 324);

}

#endif


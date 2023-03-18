// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__OBJECT_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__OBJECT_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	enum class PredictedResourceType : std::uint16_t {
		BITMAP = 0,
		SOUND,
	};

	enum class ObjectNoise : std::uint16_t {
		SILENT = 0,
		MEDIUM,
		LOUD,
		SHOUT,
		QUIET,
	};

	enum class ObjectFunctionIn : std::uint16_t {
		NONE = 0,
		BODY_VITALITY,
		SHIELD_VITALITY,
		RECENT_BODY_DAMAGE,
		RECENT_SHIELD_DAMAGE,
		RANDOM_CONSTANT,
		UMBRELLA_SHIELD_VITALITY,
		SHIELD_STUN,
		RECENT_UMBRELLA_SHIELD_VITALITY,
		UMBRELLA_SHIELD_STUN,
		REGION,
		REGION_1,
		REGION_2,
		REGION_3,
		REGION_4,
		REGION_5,
		REGION_6,
		REGION_7,
		ALIVE,
		COMPASS,
	};

	enum class ObjectType : std::uint16_t {
		BIPED = 0,
		VEHICLE,
		WEAPON,
		EQUIPMENT,
		GARBAGE,
		PROJECTILE,
		SCENERY,
		DEVICE_MACHINE,
		DEVICE_CONTROL,
		DEVICE_LIGHT_FIXTURE,
		PLACEHOLDER,
		SOUND_SCENERY,
	};

	struct ObjectFunctionFlags {
		std::uint32_t invert : 1;
		std::uint32_t additive : 1;
		std::uint32_t always_active : 1;
	};
	static_assert(sizeof(ObjectFunctionFlags) == sizeof(std::uint32_t));

	struct ObjectFlags {
		std::uint16_t does_not_cast_shadow : 1;
		std::uint16_t transparent_self_occlusion : 1;
		std::uint16_t brighter_than_it_should_be : 1;
		std::uint16_t not_a_pathfinding_obstacle : 1;
		std::uint16_t extension_of_parent : 1;
		std::uint16_t cast_shadow_by_default : 1;
		std::uint16_t does_not_have_anniversary_geometry : 1;
	};
	static_assert(sizeof(ObjectFlags) == sizeof(std::uint16_t));

	struct BaseObjectFlags {
		std::uint16_t off_in_pegasus : 1;
	};
	static_assert(sizeof(BaseObjectFlags) == sizeof(std::uint16_t));

	struct PredictedResource {
		PredictedResourceType type;
		Index resource_index;
		TagHandle tag;
	};
	static_assert(sizeof(PredictedResource) == 8);

	struct ObjectAttachment {
		TagDependency type;
		TagString marker;
		FunctionOut primary_scale;
		FunctionOut secondary_scale;
		FunctionNameNullable change_color;
		PADDING(2);
		PADDING(16);
	};
	static_assert(sizeof(ObjectAttachment) == 72);

	struct ObjectWidget {
		TagDependency reference;
		PADDING(16);
	};
	static_assert(sizeof(ObjectWidget) == 32);

	struct ObjectFunction {
		ObjectFunctionFlags flags;
		float period;
		FunctionScaleBy scale_period_by;
		WaveFunction function;
		FunctionScaleBy scale_function_by;
		WaveFunction wobble_function;
		float wobble_period;
		float wobble_magnitude;
		Fraction square_wave_threshold;
		std::int16_t step_count;
		FunctionType map_to;
		std::int16_t sawtooth_count;
		FunctionScaleBy add;
		FunctionScaleBy scale_result_by;
		FunctionBoundsMode bounds_mode;
		Fraction bounds[2];
		PADDING(4);
		PADDING(2);
		std::int16_t turn_off_with;
		float scale_by;
		PADDING(252);
		float inverse_bounds;
		float inverse_sawtooth;
		float inverse_step;
		float inverse_period;
		TagString usage;
	};
	static_assert(sizeof(ObjectFunction) == 360);

	struct ObjectChangeColorsPermutation {
		float weight;
		ColorRGB color_lower_bound;
		ColorRGB color_upper_bound;
	};
	static_assert(sizeof(ObjectChangeColorsPermutation) == 28);

	struct ObjectChangeColors {
		FunctionScaleBy darken_by;
		FunctionScaleBy scale_by;
		ColorInterpolationFlags flags;
		ColorRGB color_lower_bound;
		ColorRGB color_upper_bound;
		TagReflexive<ObjectChangeColorsPermutation> permutations;
	};
	static_assert(sizeof(ObjectChangeColors) == 44);

	struct Object {
		ObjectType object_type;
		ObjectFlags flags;
		float bounding_radius;
		Point3D bounding_offset;
		Point3D origin_offset;
		float acceleration_scale;
		std::uint32_t scales_change_colors;
		TagDependency model;
		TagDependency animation_graph;
		PADDING(40);
		TagDependency collision_model;
		TagDependency physics;
		TagDependency modifier_shader;
		TagDependency creation_effect;
		PADDING(84);
		float render_bounding_radius;
		ObjectFunctionIn a_in;
		ObjectFunctionIn b_in;
		ObjectFunctionIn c_in;
		ObjectFunctionIn d_in;
		PADDING(44);
		std::int16_t hud_text_message_index;
		std::int16_t forced_shader_permutation_index;
		TagReflexive<ObjectAttachment> attachments;
		TagReflexive<ObjectWidget> widgets;
		TagReflexive<ObjectFunction> functions;
		TagReflexive<ObjectChangeColors> change_colors;
		TagReflexive<PredictedResource> predicted_resources;
	};
	static_assert(sizeof(Object) == 380);

	struct BasicObject : public Object {
		PADDING(2);
		BaseObjectFlags more_flags;
		PADDING(124);
	};
	static_assert(sizeof(BasicObject) == 508);

}

#endif


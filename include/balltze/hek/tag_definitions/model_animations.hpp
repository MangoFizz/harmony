// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__MODEL_ANIMATIONS_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__MODEL_ANIMATIONS_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	enum class AnimationFunction : std::uint16_t {
		A_OUT = 0,
		B_OUT,
		C_OUT,
		D_OUT,
	};

	enum class AnimationFunctionControls : std::uint16_t {
		FRAME = 0,
		SCALE,
	};

	enum class AnimationType : std::uint16_t {
		BASE = 0,
		OVERLAY,
		REPLACEMENT,
	};

	enum class AnimationFrameInfoType : std::uint16_t {
		NONE = 0,
		DX_DY,
		DX_DY_DYAW,
		DX_DY_DZ_DYAW,
	};

	struct ModelAnimationsAnimationGraphNodeFlags {
		std::uint32_t ball_socket : 1;
		std::uint32_t hinge : 1;
		std::uint32_t no_movement : 1;
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphNodeFlags) == sizeof(std::uint32_t));

	struct ModelAnimationsAnimationFlags {
		std::uint16_t compressed_data : 1;
		std::uint16_t world_relative : 1;
		std::uint16_t _25hz_pal : 1;
	};
	static_assert(sizeof(ModelAnimationsAnimationFlags) == sizeof(std::uint16_t));

	struct ModelAnimationsFlags {
		std::uint16_t compress_all_animations : 1;
		std::uint16_t force_idle_compression : 1;
	};
	static_assert(sizeof(ModelAnimationsFlags) == sizeof(std::uint16_t));

	struct ModelAnimationsRotation {
		Memory::BigEndian<std::int16_t> rotation[4];
	};
	static_assert(sizeof(ModelAnimationsRotation) == 8);

	struct ModelAnimationsTransform {
		Point3D transform;
	};
	static_assert(sizeof(ModelAnimationsTransform) == 12);

	struct ModelAnimationscale {
		Fraction scale;
	};
	static_assert(sizeof(ModelAnimationscale) == 4);

	struct ModelAnimationsFrameInfoDxDy {
		Memory::BigEndian<float> dx;
		Memory::BigEndian<float> dy;
	};
	static_assert(sizeof(ModelAnimationsFrameInfoDxDy) == 8);

	struct ModelAnimationsFrameInfoDxDyDyaw {
		Memory::BigEndian<float> dx;
		Memory::BigEndian<float> dy;
		Memory::BigEndian<float> dyaw;
	};
	static_assert(sizeof(ModelAnimationsFrameInfoDxDyDyaw) == 12);

	struct ModelAnimationsFrameInfoDxDyDzDyaw {
		Memory::BigEndian<float> dx;
		Memory::BigEndian<float> dy;
		Memory::BigEndian<float> dz;
		Memory::BigEndian<float> dyaw;
	};
	static_assert(sizeof(ModelAnimationsFrameInfoDxDyDzDyaw) == 16);

	struct ModelAnimationsAnimationGraphObjectOverlay {
		Index animation;
		Memory::BigEndian<AnimationFunction> function;
		Memory::BigEndian<AnimationFunctionControls> function_controls;
		PADDING(2);
		PADDING(12);
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphObjectOverlay) == 20);

	struct ModelAnimationsUnitSeatAnimation {
		Index animation;
	};
	static_assert(sizeof(ModelAnimationsUnitSeatAnimation) == 2);

	struct ModelAnimationsAnimationGraphUnitSeatikPoint {
		TagString marker;
		TagString attach_to_marker;
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphUnitSeatikPoint) == 64);

	struct ModelAnimationsAnimationWeaponClassAnimation {
		Index animation;
	};
	static_assert(sizeof(ModelAnimationsAnimationWeaponClassAnimation) == 2);

	struct ModelAnimationsAnimationWeaponTypeAnimation {
		Index animation;
	};
	static_assert(sizeof(ModelAnimationsAnimationWeaponTypeAnimation) == 2);

	struct ModelAnimationsAnimationGraphWeaponType {
		TagString label;
		PADDING(16);
		TagReflexive<ModelAnimationsAnimationWeaponTypeAnimation> animations;
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphWeaponType) == 60);

	struct ModelAnimationsAnimationGraphWeapon {
		TagString name;
		TagString grip_marker;
		TagString hand_marker;
		Angle right_yaw_per_frame;
		Angle left_yaw_per_frame;
		Memory::BigEndian<std::uint16_t> right_frame_count;
		Memory::BigEndian<std::uint16_t> left_frame_count;
		Angle down_pitch_per_frame;
		Angle up_pitch_per_frame;
		Memory::BigEndian<std::uint16_t> down_pitch_frame_count;
		Memory::BigEndian<std::uint16_t> up_pitch_frame_count;
		PADDING(32);
		TagReflexive<ModelAnimationsAnimationWeaponClassAnimation> animations;
		TagReflexive<ModelAnimationsAnimationGraphUnitSeatikPoint> ik_point;
		TagReflexive<ModelAnimationsAnimationGraphWeaponType> weapon_types;
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphWeapon) == 188);

	struct ModelAnimationsAnimationGraphUnitSeat {
		TagString label;
		Angle right_yaw_per_frame;
		Angle left_yaw_per_frame;
		Memory::BigEndian<std::uint16_t> right_frame_count;
		Memory::BigEndian<std::uint16_t> left_frame_count;
		Angle down_pitch_per_frame;
		Angle up_pitch_per_frame;
		Memory::BigEndian<std::uint16_t> down_pitch_frame_count;
		Memory::BigEndian<std::uint16_t> up_pitch_frame_count;
		PADDING(8);
		TagReflexive<ModelAnimationsAnimationWeaponClassAnimation> animations;
		TagReflexive<ModelAnimationsAnimationGraphUnitSeatikPoint> ik_points;
		TagReflexive<ModelAnimationsAnimationGraphWeapon> weapons;
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphUnitSeat) == 100);

	struct ModelAnimationsWeaponAnimation {
		Index animation;
	};
	static_assert(sizeof(ModelAnimationsWeaponAnimation) == 2);

	struct ModelAnimationsAnimationGraphWeaponAnimations {
		PADDING(16);
		TagReflexive<ModelAnimationsWeaponAnimation> animations;
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphWeaponAnimations) == 28);

	struct ModelAnimationsVehicleAnimation {
		Index animation;
	};
	static_assert(sizeof(ModelAnimationsVehicleAnimation) == 2);

	struct ModelAnimationSuspensionAnimation {
		Index mass_point_index;
		Index animation;
		Memory::BigEndian<float> full_extension_ground_depth;
		Memory::BigEndian<float> full_compression_ground_depth;
		PADDING(8);
	};
	static_assert(sizeof(ModelAnimationSuspensionAnimation) == 20);

	struct ModelAnimationsAnimationGraphVehicleAnimations {
		Angle right_yaw_per_frame;
		Angle left_yaw_per_frame;
		Memory::BigEndian<std::uint16_t> right_frame_count;
		Memory::BigEndian<std::uint16_t> left_frame_count;
		Angle down_pitch_per_frame;
		Angle up_pitch_per_frame;
		Memory::BigEndian<std::uint16_t> down_pitch_frame_count;
		Memory::BigEndian<std::uint16_t> up_pitch_frame_count;
		PADDING(68);
		TagReflexive<ModelAnimationsVehicleAnimation> animations;
		TagReflexive<ModelAnimationSuspensionAnimation> suspension_animations;
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphVehicleAnimations) == 116);

	struct ModelAnimationsDeviceAnimation {
		Index animation;
	};
	static_assert(sizeof(ModelAnimationsDeviceAnimation) == 2);

	struct ModelAnimationsDeviceAnimations {
		PADDING(84);
		TagReflexive<ModelAnimationsDeviceAnimation> animations;
	};
	static_assert(sizeof(ModelAnimationsDeviceAnimations) == 96);

	struct ModelAnimationsUnitDamageAnimations {
		Index animation;
	};
	static_assert(sizeof(ModelAnimationsUnitDamageAnimations) == 2);

	struct ModelAnimationsFirstPersonWeapon {
		Index animation;
	};
	static_assert(sizeof(ModelAnimationsFirstPersonWeapon) == 2);

	struct ModelAnimationsAnimationGraphFirstPersonWeaponAnimations {
		PADDING(16);
		TagReflexive<ModelAnimationsFirstPersonWeapon> animations;
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphFirstPersonWeaponAnimations) == 28);

	struct ModelAnimationsAnimationGraphSoundReference {
		TagDependency sound;
		PADDING(4);
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphSoundReference) == 20);

	struct ModelAnimationsAnimationGraphNode {
		TagString name;
		Index next_sibling_node_index;
		Index first_child_node_index;
		Index parent_node_index;
		PADDING(2);
		Memory::BigEndian<ModelAnimationsAnimationGraphNodeFlags> node_joint_flags;
		Vector3D base_vector;
		Memory::BigEndian<float> vector_range;
		PADDING(4);
	};
	static_assert(sizeof(ModelAnimationsAnimationGraphNode) == 64);

	struct ModelAnimationsAnimation {
		TagString name;
		Memory::BigEndian<AnimationType> type;
		Memory::BigEndian<std::uint16_t> frame_count;
		Memory::BigEndian<std::uint16_t> frame_size;
		Memory::BigEndian<AnimationFrameInfoType> frame_info_type;
		Memory::BigEndian<std::int32_t> node_list_checksum;
		Memory::BigEndian<std::uint16_t> node_count;
		Index loop_frame_index;
		Fraction weight;
		Index key_frame_index;
		Index second_key_frame_index;
		Index next_animation;
		Memory::BigEndian<ModelAnimationsAnimationFlags> flags;
		Index sound;
		Index sound_frame_index;
		Memory::BigEndian<std::int8_t> left_foot_frame_index;
		Memory::BigEndian<std::int8_t> right_foot_frame_index;
		Memory::BigEndian<std::uint16_t> main_animation_index;
		Memory::BigEndian<float> relative_weight;
		TagDataOffset frame_info;
		Memory::BigEndian<std::uint32_t> node_transform_flag_data[2];
		PADDING(8);
		Memory::BigEndian<std::uint32_t> node_rotation_flag_data[2];
		PADDING(8);
		Memory::BigEndian<std::uint32_t> node_scale_flag_data[2];
		PADDING(4);
		Memory::BigEndian<std::uint32_t> offset_to_compressed_data;
		TagDataOffset default_data;
		TagDataOffset frame_data;
	};
	static_assert(sizeof(ModelAnimationsAnimation) == 180);

	struct ModelAnimations {
		TagReflexive<ModelAnimationsAnimationGraphObjectOverlay> objects;
		TagReflexive<ModelAnimationsAnimationGraphUnitSeat> units;
		TagReflexive<ModelAnimationsAnimationGraphWeaponAnimations> weapons;
		TagReflexive<ModelAnimationsAnimationGraphVehicleAnimations> vehicles;
		TagReflexive<ModelAnimationsDeviceAnimations> devices;
		TagReflexive<ModelAnimationsUnitDamageAnimations> unit_damage;
		TagReflexive<ModelAnimationsAnimationGraphFirstPersonWeaponAnimations> first_person_weapons;
		TagReflexive<ModelAnimationsAnimationGraphSoundReference> sound_references;
		Memory::BigEndian<float> limp_body_node_radius;
		Memory::BigEndian<ModelAnimationsFlags> flags;
		PADDING(2);
		TagReflexive<ModelAnimationsAnimationGraphNode> nodes;
		TagReflexive<ModelAnimationsAnimation> animations;
	};
	static_assert(sizeof(ModelAnimations) == 128);

}

#endif


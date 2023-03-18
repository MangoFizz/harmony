// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__MODEL_COLLISION_GEOMETRY_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__MODEL_COLLISION_GEOMETRY_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct ModelCollisionGeometryMaterialFlags {
		std::uint32_t head : 1;
	};
	static_assert(sizeof(ModelCollisionGeometryMaterialFlags) == sizeof(std::uint32_t));

	struct ModelCollisionGeometryRegionFlags {
		std::uint32_t lives_until_object_dies : 1;
		std::uint32_t forces_object_to_die : 1;
		std::uint32_t dies_when_object_dies : 1;
		std::uint32_t dies_when_object_is_damaged : 1;
		std::uint32_t disappears_when_shield_is_off : 1;
		std::uint32_t inhibits_melee_attack : 1;
		std::uint32_t inhibits_weapon_attack : 1;
		std::uint32_t inhibits_walking : 1;
		std::uint32_t forces_drop_weapon : 1;
		std::uint32_t causes_head_maimed_scream : 1;
	};
	static_assert(sizeof(ModelCollisionGeometryRegionFlags) == sizeof(std::uint32_t));

	struct ModelCollisionGeometryBSPLeafFlags {
		std::uint16_t contains_double_sided_surfaces : 1;
	};
	static_assert(sizeof(ModelCollisionGeometryBSPLeafFlags) == sizeof(std::uint16_t));

	struct ModelCollisionGeometryBSPSurfaceFlags {
		std::uint8_t two_sided : 1;
		std::uint8_t invisible : 1;
		std::uint8_t climbable : 1;
		std::uint8_t breakable : 1;
	};
	static_assert(sizeof(ModelCollisionGeometryBSPSurfaceFlags) == sizeof(std::uint8_t));

	struct ModelCollisionGeometryFlags {
		std::uint32_t takes_shield_damage_for_children : 1;
		std::uint32_t takes_body_damage_for_children : 1;
		std::uint32_t always_shields_friendly_damage : 1;
		std::uint32_t passes_area_damage_to_children : 1;
		std::uint32_t parent_never_takes_body_damage_for_us : 1;
		std::uint32_t only_damaged_by_explosives : 1;
		std::uint32_t only_damaged_while_occupied : 1;
	};
	static_assert(sizeof(ModelCollisionGeometryFlags) == sizeof(std::uint32_t));

	struct ModelCollisionGeometryMaterial {
		TagString name;
		Memory::BigEndian<ModelCollisionGeometryMaterialFlags> flags;
		Memory::BigEndian<MaterialType> material_type;
		PADDING(2);
		Fraction shield_leak_percentage;
		Memory::BigEndian<float> shield_damage_multiplier;
		PADDING(12);
		Memory::BigEndian<float> body_damage_multiplier;
		PADDING(8);
	};
	static_assert(sizeof(ModelCollisionGeometryMaterial) == 72);

	struct ModelCollisionGeometryPermutation {
		TagString name;
	};
	static_assert(sizeof(ModelCollisionGeometryPermutation) == 32);

	struct ModelCollisionGeometryRegion {
		TagString name;
		Memory::BigEndian<ModelCollisionGeometryRegionFlags> flags;
		PADDING(4);
		Memory::BigEndian<float> damage_threshold;
		PADDING(12);
		TagDependency destroyed_effect;
		TagReflexive<ModelCollisionGeometryPermutation> permutations;
	};
	static_assert(sizeof(ModelCollisionGeometryRegion) == 84);

	struct ModelCollisionGeometryModifier {
		PADDING(52);
	};
	static_assert(sizeof(ModelCollisionGeometryModifier) == 52);

	struct ModelCollisionGeometrySphere {
		Index node;
		PADDING(2);
		PADDING(12);
		Point3D center;
		Memory::BigEndian<float> radius;
	};
	static_assert(sizeof(ModelCollisionGeometrySphere) == 32);

	struct ModelCollisionGeometryBSP3DNode {
		Memory::BigEndian<std::uint32_t> plane;
		Memory::BigEndian<std::uint32_t> back_child;
		Memory::BigEndian<std::uint32_t> front_child;
	};
	static_assert(sizeof(ModelCollisionGeometryBSP3DNode) == 12);

	struct ModelCollisionGeometryBSPPlane {
		Plane3D plane;
	};
	static_assert(sizeof(ModelCollisionGeometryBSPPlane) == 16);

	struct ModelCollisionGeometryBSPLeaf {
		Memory::BigEndian<ModelCollisionGeometryBSPLeafFlags> flags;
		Memory::BigEndian<std::uint16_t> bsp2d_reference_count;
		Memory::BigEndian<std::uint32_t> first_bsp2d_reference;
	};
	static_assert(sizeof(ModelCollisionGeometryBSPLeaf) == 8);

	struct ModelCollisionGeometryBSP2DReference {
		Memory::BigEndian<std::uint32_t> plane;
		Memory::BigEndian<std::uint32_t> bsp2d_node;
	};
	static_assert(sizeof(ModelCollisionGeometryBSP2DReference) == 8);

	struct ModelCollisionGeometryBSP2DNode {
		Plane2D plane;
		Memory::BigEndian<std::uint32_t> left_child;
		Memory::BigEndian<std::uint32_t> right_child;
	};
	static_assert(sizeof(ModelCollisionGeometryBSP2DNode) == 20);

	struct ModelCollisionGeometryBSPSurface {
		Memory::BigEndian<std::uint32_t> plane;
		Memory::BigEndian<std::uint32_t> first_edge;
		Memory::BigEndian<ModelCollisionGeometryBSPSurfaceFlags> flags;
		Memory::BigEndian<std::int8_t> breakable_surface;
		Index material;
	};
	static_assert(sizeof(ModelCollisionGeometryBSPSurface) == 12);

	struct ModelCollisionGeometryBSPEdge {
		Memory::BigEndian<std::uint32_t> start_vertex;
		Memory::BigEndian<std::uint32_t> end_vertex;
		Memory::BigEndian<std::uint32_t> forward_edge;
		Memory::BigEndian<std::uint32_t> reverse_edge;
		Memory::BigEndian<std::uint32_t> left_surface;
		Memory::BigEndian<std::uint32_t> right_surface;
	};
	static_assert(sizeof(ModelCollisionGeometryBSPEdge) == 24);

	struct ModelCollisionGeometryBSPVertex {
		Point3D point;
		Memory::BigEndian<std::uint32_t> first_edge;
	};
	static_assert(sizeof(ModelCollisionGeometryBSPVertex) == 16);

	struct ModelCollisionGeometryBSP {
		TagReflexive<ModelCollisionGeometryBSP3DNode> bsp3d_nodes;
		TagReflexive<ModelCollisionGeometryBSPPlane> planes;
		TagReflexive<ModelCollisionGeometryBSPLeaf> leaves;
		TagReflexive<ModelCollisionGeometryBSP2DReference> bsp2d_references;
		TagReflexive<ModelCollisionGeometryBSP2DNode> bsp2d_nodes;
		TagReflexive<ModelCollisionGeometryBSPSurface> surfaces;
		TagReflexive<ModelCollisionGeometryBSPEdge> edges;
		TagReflexive<ModelCollisionGeometryBSPVertex> vertices;
	};
	static_assert(sizeof(ModelCollisionGeometryBSP) == 96);

	struct ModelCollisionGeometryNode {
		TagString name;
		Index region;
		Index parent_node;
		Index next_sibling_node;
		Index first_child_node;
		PADDING(10);
		Memory::BigEndian<std::int16_t> name_thing;
		TagReflexive<ModelCollisionGeometryBSP> bsps;
	};
	static_assert(sizeof(ModelCollisionGeometryNode) == 64);

	struct ModelCollisionGeometry {
		Memory::BigEndian<ModelCollisionGeometryFlags> flags;
		Index indirect_damage_material;
		PADDING(2);
		Memory::BigEndian<float> maximum_body_vitality;
		Memory::BigEndian<float> body_system_shock;
		PADDING(24);
		PADDING(28);
		Fraction friendly_damage_resistance;
		PADDING(8);
		PADDING(32);
		TagDependency localized_damage_effect;
		Memory::BigEndian<float> area_damage_effect_threshold;
		TagDependency area_damage_effect;
		Memory::BigEndian<float> body_damaged_threshold;
		TagDependency body_damaged_effect;
		TagDependency body_depleted_effect;
		Memory::BigEndian<float> body_destroyed_threshold;
		TagDependency body_destroyed_effect;
		Memory::BigEndian<float> maximum_shield_vitality;
		PADDING(2);
		Memory::BigEndian<MaterialType> shield_material_type;
		PADDING(24);
		Memory::BigEndian<FunctionType> shield_failure_function;
		PADDING(2);
		Fraction shield_failure_threshold;
		Fraction failing_shield_leak_fraction;
		PADDING(16);
		Memory::BigEndian<float> minimum_stun_damage;
		Memory::BigEndian<float> stun_time;
		Memory::BigEndian<float> recharge_time;
		PADDING(16);
		PADDING(96);
		Memory::BigEndian<float> shield_damaged_threshold;
		TagDependency shield_damaged_effect;
		TagDependency shield_depleted_effect;
		TagDependency shield_recharging_effect;
		PADDING(8);
		Memory::BigEndian<float> shield_recharge_rate;
		PADDING(112);
		TagReflexive<ModelCollisionGeometryMaterial> materials;
		TagReflexive<ModelCollisionGeometryRegion> regions;
		TagReflexive<ModelCollisionGeometryModifier> modifiers;
		PADDING(16);
		Memory::BigEndian<float> x[2];
		Memory::BigEndian<float> y[2];
		Memory::BigEndian<float> z[2];
		TagReflexive<ModelCollisionGeometrySphere> pathfinding_spheres;
		TagReflexive<ModelCollisionGeometryNode> nodes;
	};
	static_assert(sizeof(ModelCollisionGeometry) == 664);

}

#endif


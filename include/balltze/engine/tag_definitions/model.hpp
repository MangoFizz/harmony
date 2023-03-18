// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__ENGINE__TAG_DEFINITION__MODEL_HPP
#define BALLTZE_API__ENGINE__TAG_DEFINITION__MODEL_HPP

#include "../../memory.hpp"
#include "../data_types.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::Engine::TagDefinitions { 
	struct ModelRegionPermutationFlags {
		std::uint32_t cannot_be_chosen_randomly : 1;
	};
	static_assert(sizeof(ModelRegionPermutationFlags) == sizeof(std::uint32_t));

	struct ModelGeometryPartFlags {
		std::uint32_t stripped_internal : 1;
		std::uint32_t zoner : 1;
	};
	static_assert(sizeof(ModelGeometryPartFlags) == sizeof(std::uint32_t));

	struct ModelFlags {
		std::uint32_t blend_shared_normals : 1;
		std::uint32_t parts_have_local_nodes : 1;
		std::uint32_t ignore_skinning : 1;
	};
	static_assert(sizeof(ModelFlags) == sizeof(std::uint32_t));

	struct ModelMarkerInstance {
		std::uint8_t region_index;
		std::uint8_t permutation_index;
		std::uint8_t node_index;
		PADDING(1);
		Point3D translation;
		Quaternion rotation;
	};
	static_assert(sizeof(ModelMarkerInstance) == 32);

	struct ModelMarker {
		TagString name;
		std::int16_t magic_identifier;
		PADDING(2);
		PADDING(16);
		TagReflexive<ModelMarkerInstance> instances;
	};
	static_assert(sizeof(ModelMarker) == 64);

	struct ModelNode {
		TagString name;
		Index next_sibling_node_index;
		Index first_child_node_index;
		Index parent_node_index;
		PADDING(2);
		Point3D default_translation;
		Quaternion default_rotation;
		float node_distance_from_parent;
		PADDING(32);
		float scale;
		Matrix rotation;
		Point3D translation;
	};
	static_assert(sizeof(ModelNode) == 156);

	struct ModelRegionPermutationMarker {
		TagString name;
		Index node_index;
		PADDING(2);
		Quaternion rotation;
		Point3D translation;
		PADDING(16);
	};
	static_assert(sizeof(ModelRegionPermutationMarker) == 80);

	struct ModelRegionPermutation {
		TagString name;
		ModelRegionPermutationFlags flags;
		std::uint16_t permutation_number;
		PADDING(2);
		PADDING(24);
		Index super_low;
		Index low;
		Index medium;
		Index high;
		Index super_high;
		PADDING(2);
		TagReflexive<ModelRegionPermutationMarker> markers;
	};
	static_assert(sizeof(ModelRegionPermutation) == 88);

	struct ModelRegion {
		TagString name;
		PADDING(32);
		TagReflexive<ModelRegionPermutation> permutations;
	};
	static_assert(sizeof(ModelRegion) == 76);

	struct ModelVertexUncompressed {
		Point3D position;
		Vector3D normal;
		Vector3D binormal;
		Vector3D tangent;
		Point2D texture_coords;
		Index node0_index;
		Index node1_index;
		float node0_weight;
		float node1_weight;
	};
	static_assert(sizeof(ModelVertexUncompressed) == 68);

	struct ModelVertexCompressed {
		Point3D position;
		std::uint32_t normal;
		std::uint32_t binormal;
		std::uint32_t tangent;
		std::int16_t texture_coordinate_u;
		std::int16_t texture_coordinate_v;
		std::int8_t node0_index;
		std::int8_t node1_index;
		std::uint16_t node0_weight;
	};
	static_assert(sizeof(ModelVertexCompressed) == 32);

	struct ModelTriangle {
		Index vertex0_index;
		Index vertex1_index;
		Index vertex2_index;
	};
	static_assert(sizeof(ModelTriangle) == 6);

	struct ModelGeometryPart {
		ModelGeometryPartFlags flags;
		Index shader_index;
		std::uint8_t prev_filthy_part_index;
		std::uint8_t next_filthy_part_index;
		Index centroid_primary_node;
		Index centroid_secondary_node;
		Fraction centroid_primary_weight;
		Fraction centroid_secondary_weight;
		Point3D centroid;
		TagReflexive<ModelVertexUncompressed> uncompressed_vertices;
		TagReflexive<ModelVertexCompressed> compressed_vertices;
		TagReflexive<ModelTriangle> triangles;
		std::uint32_t do_not_crash_the_game;
		std::uint32_t triangle_count;
		std::uint32_t triangle_offset;
		std::uint32_t triangle_offset_2;
		VertexType vertex_type;
		PADDING(2);
		std::uint32_t vertex_count;
		PADDING(4);
		std::byte *vertex_pointer;
		std::uint32_t vertex_offset;
	};
	static_assert(sizeof(ModelGeometryPart) == 104);

	struct ModelGeometry {
		IsUnusedFlag flags;
		PADDING(32);
		TagReflexive<ModelGeometryPart> parts;
	};
	static_assert(sizeof(ModelGeometry) == 48);

	struct ModelShaderReference {
		TagDependency shader;
		Index permutation;
		PADDING(2);
		PADDING(12);
	};
	static_assert(sizeof(ModelShaderReference) == 32);

	struct Model {
		ModelFlags flags;
		std::int32_t node_list_checksum;
		float super_high_detail_cutoff;
		float high_detail_cutoff;
		float medium_detail_cutoff;
		float low_detail_cutoff;
		float super_low_detail_cutoff;
		std::uint16_t super_low_detail_node_count;
		std::uint16_t low_detail_node_count;
		std::uint16_t medium_detail_node_count;
		std::uint16_t high_detail_node_count;
		std::uint16_t super_high_detail_node_count;
		PADDING(2);
		PADDING(8);
		float base_map_u_scale;
		float base_map_v_scale;
		PADDING(116);
		TagReflexive<ModelMarker> markers;
		TagReflexive<ModelNode> nodes;
		TagReflexive<ModelRegion> regions;
		TagReflexive<ModelGeometry> geometries;
		TagReflexive<ModelShaderReference> shaders;
	};
	static_assert(sizeof(Model) == 232);

}

#endif


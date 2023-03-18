// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__SCENARIO_STRUCTURE_BSP_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__SCENARIO_STRUCTURE_BSP_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct ScenarioStructureBSPMaterialFlags {
		std::uint16_t coplanar : 1;
		std::uint16_t fog_plane : 1;
	};
	static_assert(sizeof(ScenarioStructureBSPMaterialFlags) == sizeof(std::uint16_t));

	struct ScenarioStructureBSPClusterPortalFlags {
		std::uint32_t ai_can_simply_not_hear_through_all_this_amazing_stuff_darn_it : 1;
	};
	static_assert(sizeof(ScenarioStructureBSPClusterPortalFlags) == sizeof(std::uint32_t));

	struct ScenarioStructureBSPCollisionMaterial {
		TagDependency shader;
		PADDING(2);
		Memory::BigEndian<MaterialType> material;
	};
	static_assert(sizeof(ScenarioStructureBSPCollisionMaterial) == 20);

	struct ScenarioStructureBSPNode {
		Memory::BigEndian<std::uint16_t> node_stuff[3];
	};
	static_assert(sizeof(ScenarioStructureBSPNode) == 6);

	struct ScenarioStructureBSPLeaf {
		Memory::BigEndian<std::uint16_t> vertices[3];
		PADDING(2);
		Index cluster;
		Memory::BigEndian<std::int16_t> surface_reference_count;
		Memory::BigEndian<std::int32_t> surface_references;
	};
	static_assert(sizeof(ScenarioStructureBSPLeaf) == 16);

	struct ScenarioStructureBSPSurfaceReference {
		Memory::BigEndian<std::int32_t> surface;
		Memory::BigEndian<std::int32_t> node;
	};
	static_assert(sizeof(ScenarioStructureBSPSurfaceReference) == 8);

	struct ScenarioStructureBSPSurface {
		Index vertex0_index;
		Index vertex1_index;
		Index vertex2_index;
	};
	static_assert(sizeof(ScenarioStructureBSPSurface) == 6);

	struct ScenarioStructureBSPMaterialUncompressedRenderedVertex {
		Point3D position;
		Vector3D normal;
		Vector3D binormal;
		Vector3D tangent;
		Point2D texture_coords;
	};
	static_assert(sizeof(ScenarioStructureBSPMaterialUncompressedRenderedVertex) == 56);

	struct ScenarioStructureBSPMaterialCompressedRenderedVertex {
		Point3D position;
		Memory::BigEndian<std::uint32_t> normal;
		Memory::BigEndian<std::uint32_t> binormal;
		Memory::BigEndian<std::uint32_t> tangent;
		Point2D texture_coords;
	};
	static_assert(sizeof(ScenarioStructureBSPMaterialCompressedRenderedVertex) == 32);

	struct ScenarioStructureBSPMaterialUncompressedLightmapVertex {
		Vector3D normal;
		Point2D texture_coords;
	};
	static_assert(sizeof(ScenarioStructureBSPMaterialUncompressedLightmapVertex) == 20);

	struct ScenarioStructureBSPMaterialCompressedLightmapVertex {
		Memory::BigEndian<std::uint32_t> normal;
		Memory::BigEndian<std::int16_t> texture_coordinate_x;
		Memory::BigEndian<std::int16_t> texture_coordinate_y;
	};
	static_assert(sizeof(ScenarioStructureBSPMaterialCompressedLightmapVertex) == 8);

	struct ScenarioStructureBSPMaterial {
		TagDependency shader;
		Index shader_permutation;
		Memory::BigEndian<ScenarioStructureBSPMaterialFlags> flags;
		Memory::BigEndian<std::int32_t> surfaces;
		Memory::BigEndian<std::int32_t> surface_count;
		Point3D centroid;
		ColorRGB ambient_color;
		Memory::BigEndian<std::int16_t> distant_light_count;
		PADDING(2);
		ColorRGB distant_light_0_color;
		Vector3D distant_light_0_direction;
		ColorRGB distant_light_1_color;
		Vector3D distant_light_1_direction;
		PADDING(12);
		ColorARGB reflection_tint;
		Vector3D shadow_vector;
		ColorRGB shadow_color;
		Plane3D plane;
		Index breakable_surface;
		PADDING(2);
		Memory::BigEndian<VertexType> rendered_vertices_type;
		PADDING(2);
		Memory::BigEndian<std::uint32_t> rendered_vertices_count;
		Memory::BigEndian<std::uint32_t> rendered_vertices_offset;
		PADDING(4);
		std::byte *rendered_vertices_index_pointer;
		Memory::BigEndian<VertexType> lightmap_vertices_type;
		PADDING(2);
		Memory::BigEndian<std::uint32_t> lightmap_vertices_count;
		Memory::BigEndian<std::uint32_t> lightmap_vertices_offset;
		PADDING(4);
		std::byte *lightmap_vertices_index_pointer;
		TagDataOffset uncompressed_vertices;
		TagDataOffset compressed_vertices;
	};
	static_assert(sizeof(ScenarioStructureBSPMaterial) == 256);

	struct ScenarioStructureBSPLightmap {
		Index bitmap;
		PADDING(2);
		PADDING(16);
		TagReflexive<ScenarioStructureBSPMaterial> materials;
	};
	static_assert(sizeof(ScenarioStructureBSPLightmap) == 32);

	struct ScenarioStructureBSPLensFlare {
		TagDependency lens;
	};
	static_assert(sizeof(ScenarioStructureBSPLensFlare) == 16);

	struct ScenarioStructureBSPLensFlareMarker {
		Point3D position;
		Memory::BigEndian<std::int8_t> direction_i_component;
		Memory::BigEndian<std::int8_t> direction_j_component;
		Memory::BigEndian<std::int8_t> direction_k_component;
		Memory::BigEndian<std::int8_t> lens_flare_index;
	};
	static_assert(sizeof(ScenarioStructureBSPLensFlareMarker) == 16);

	struct ScenarioStructureBSPSubclusterSurfaceIndex {
		Memory::BigEndian<std::int32_t> index;
	};
	static_assert(sizeof(ScenarioStructureBSPSubclusterSurfaceIndex) == 4);

	struct ScenarioStructureBSPSubcluster {
		Memory::BigEndian<float> world_bounds_x[2];
		Memory::BigEndian<float> world_bounds_y[2];
		Memory::BigEndian<float> world_bounds_z[2];
		TagReflexive<ScenarioStructureBSPSubclusterSurfaceIndex> surface_indices;
	};
	static_assert(sizeof(ScenarioStructureBSPSubcluster) == 36);

	struct ScenarioStructureBSPClusterSurfaceIndex {
		Memory::BigEndian<std::int32_t> index;
	};
	static_assert(sizeof(ScenarioStructureBSPClusterSurfaceIndex) == 4);

	struct ScenarioStructureBSPMirrorVertex {
		Point3D point;
	};
	static_assert(sizeof(ScenarioStructureBSPMirrorVertex) == 12);

	struct ScenarioStructureBSPMirror {
		Plane3D plane;
		PADDING(20);
		TagDependency shader;
		TagReflexive<ScenarioStructureBSPMirrorVertex> vertices;
	};
	static_assert(sizeof(ScenarioStructureBSPMirror) == 64);

	struct ScenarioStructureBSPClusterPortalIndex {
		Index portal;
	};
	static_assert(sizeof(ScenarioStructureBSPClusterPortalIndex) == 2);

	struct ScenarioStructureBSPCluster {
		Index sky;
		Index fog;
		Index background_sound;
		Index sound_environment;
		Index weather;
		Index transition_structure_bsp;
		Index first_decal_index;
		Memory::BigEndian<std::uint16_t> decal_count;
		PADDING(24);
		TagReflexive<PredictedResource> predicted_resources;
		TagReflexive<ScenarioStructureBSPSubcluster> subclusters;
		Index first_lens_flare_marker_index;
		Memory::BigEndian<std::int16_t> lens_flare_marker_count;
		TagReflexive<ScenarioStructureBSPClusterSurfaceIndex> surface_indices;
		TagReflexive<ScenarioStructureBSPMirror> mirrors;
		TagReflexive<ScenarioStructureBSPClusterPortalIndex> portals;
	};
	static_assert(sizeof(ScenarioStructureBSPCluster) == 104);

	struct ScenarioStructureBSPClusterPortalVertex {
		Point3D point;
	};
	static_assert(sizeof(ScenarioStructureBSPClusterPortalVertex) == 12);

	struct ScenarioStructureBSPClusterPortal {
		Index front_cluster;
		Index back_cluster;
		Memory::BigEndian<std::int32_t> plane_index;
		Point3D centroid;
		Memory::BigEndian<float> bounding_radius;
		Memory::BigEndian<ScenarioStructureBSPClusterPortalFlags> flags;
		PADDING(24);
		TagReflexive<ScenarioStructureBSPClusterPortalVertex> vertices;
	};
	static_assert(sizeof(ScenarioStructureBSPClusterPortal) == 64);

	struct ScenarioStructureBSPBreakableSurface {
		Point3D centroid;
		Memory::BigEndian<float> radius;
		Memory::BigEndian<std::int32_t> collision_surface_index;
		PADDING(28);
	};
	static_assert(sizeof(ScenarioStructureBSPBreakableSurface) == 48);

	struct ScenarioStructureBSPFogPlaneVertex {
		Point3D point;
	};
	static_assert(sizeof(ScenarioStructureBSPFogPlaneVertex) == 12);

	struct ScenarioStructureBSPFogPlane {
		Index front_region;
		Memory::BigEndian<MaterialType> material_type;
		Plane3D plane;
		TagReflexive<ScenarioStructureBSPFogPlaneVertex> vertices;
	};
	static_assert(sizeof(ScenarioStructureBSPFogPlane) == 32);

	struct ScenarioStructureBSPFogRegion {
		PADDING(36);
		Index fog;
		Index weather_palette;
	};
	static_assert(sizeof(ScenarioStructureBSPFogRegion) == 40);

	struct ScenarioStructureBSPFogPalette {
		TagString name;
		TagDependency fog;
		PADDING(4);
		TagString fog_scale_function;
		PADDING(52);
	};
	static_assert(sizeof(ScenarioStructureBSPFogPalette) == 136);

	struct ScenarioStructureBSPWeatherPalette {
		TagString name;
		TagDependency particle_system;
		PADDING(4);
		TagString particle_system_scale_function;
		PADDING(44);
		TagDependency wind;
		Vector3D wind_direction;
		Memory::BigEndian<float> wind_magnitude;
		PADDING(4);
		TagString wind_scale_function;
		PADDING(44);
	};
	static_assert(sizeof(ScenarioStructureBSPWeatherPalette) == 240);

	struct ScenarioStructureBSPWeatherPolyhedronPlane {
		Plane3D plane;
	};
	static_assert(sizeof(ScenarioStructureBSPWeatherPolyhedronPlane) == 16);

	struct ScenarioStructureBSPWeatherPolyhedron {
		Point3D bounding_sphere_center;
		Memory::BigEndian<float> bounding_sphere_radius;
		PADDING(4);
		TagReflexive<ScenarioStructureBSPWeatherPolyhedronPlane> planes;
	};
	static_assert(sizeof(ScenarioStructureBSPWeatherPolyhedron) == 32);

	struct ScenarioStructureBSPPathfindingSurface {
		Memory::BigEndian<std::int8_t> data;
	};
	static_assert(sizeof(ScenarioStructureBSPPathfindingSurface) == 1);

	struct ScenarioStructureBSPPathfindingEdge {
		Memory::BigEndian<std::int8_t> midpoint;
	};
	static_assert(sizeof(ScenarioStructureBSPPathfindingEdge) == 1);

	struct ScenarioStructureBSPBackgroundSoundPalette {
		TagString name;
		TagDependency background_sound;
		PADDING(4);
		TagString scale_function;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioStructureBSPBackgroundSoundPalette) == 116);

	struct ScenarioStructureBSPSoundEnvironmentPalette {
		TagString name;
		TagDependency sound_environment;
		PADDING(32);
	};
	static_assert(sizeof(ScenarioStructureBSPSoundEnvironmentPalette) == 80);

	struct ScenarioStructureBSPMarker {
		TagString name;
		Quaternion rotation;
		Point3D position;
	};
	static_assert(sizeof(ScenarioStructureBSPMarker) == 60);

	struct ScenarioStructureBSPGlobalDetailObjectCell {
		Memory::BigEndian<std::int16_t> cell_x;
		Memory::BigEndian<std::int16_t> cell_y;
		Memory::BigEndian<std::int16_t> cell_z;
		Memory::BigEndian<std::int16_t> offset_z;
		Memory::BigEndian<std::int32_t> valid_layers_flags;
		Memory::BigEndian<std::int32_t> start_index;
		Memory::BigEndian<std::int32_t> count_index;
		PADDING(12);
	};
	static_assert(sizeof(ScenarioStructureBSPGlobalDetailObjectCell) == 32);

	struct ScenarioStructureBSPGlobalDetailObject {
		Memory::BigEndian<std::int8_t> position_x;
		Memory::BigEndian<std::int8_t> position_y;
		Memory::BigEndian<std::int8_t> position_z;
		Memory::BigEndian<std::int8_t> data;
		Memory::BigEndian<std::int16_t> color;
	};
	static_assert(sizeof(ScenarioStructureBSPGlobalDetailObject) == 6);

	struct ScenarioStructureBSPGlobalDetailObjectCount {
		Memory::BigEndian<std::int16_t> count;
	};
	static_assert(sizeof(ScenarioStructureBSPGlobalDetailObjectCount) == 2);

	struct ScenarioStructureBSPGlobalZReferenceVector {
		Memory::BigEndian<float> z_reference_i;
		Memory::BigEndian<float> z_reference_j;
		Memory::BigEndian<float> z_reference_k;
		Memory::BigEndian<float> z_reference_l;
	};
	static_assert(sizeof(ScenarioStructureBSPGlobalZReferenceVector) == 16);

	struct ScenarioStructureBSPDetailObjectData {
		TagReflexive<ScenarioStructureBSPGlobalDetailObjectCell> cells;
		TagReflexive<ScenarioStructureBSPGlobalDetailObject> instances;
		TagReflexive<ScenarioStructureBSPGlobalDetailObjectCount> counts;
		TagReflexive<ScenarioStructureBSPGlobalZReferenceVector> z_reference_vectors;
		Memory::BigEndian<std::uint8_t> bullshit;
		PADDING(3);
		PADDING(12);
	};
	static_assert(sizeof(ScenarioStructureBSPDetailObjectData) == 64);

	struct ScenarioStructureBSPRuntimeDecal {
		Point3D position;
		Index decal_type;
		Memory::BigEndian<std::int8_t> yaw;
		Memory::BigEndian<std::int8_t> pitch;
	};
	static_assert(sizeof(ScenarioStructureBSPRuntimeDecal) == 16);

	struct ScenarioStructureBSPMapLeafFaceVertex {
		Point2D vertex;
	};
	static_assert(sizeof(ScenarioStructureBSPMapLeafFaceVertex) == 8);

	struct ScenarioStructureBSPMapLeafFace {
		Memory::BigEndian<std::int32_t> node_index;
		TagReflexive<ScenarioStructureBSPMapLeafFaceVertex> vertices;
	};
	static_assert(sizeof(ScenarioStructureBSPMapLeafFace) == 16);

	struct ScenarioStructureBSPMapLeafPortalIndex {
		Memory::BigEndian<std::int32_t> portal_index;
	};
	static_assert(sizeof(ScenarioStructureBSPMapLeafPortalIndex) == 4);

	struct ScenarioStructureBSPGlobalMapLeaf {
		TagReflexive<ScenarioStructureBSPMapLeafFace> faces;
		TagReflexive<ScenarioStructureBSPMapLeafPortalIndex> portal_indices;
	};
	static_assert(sizeof(ScenarioStructureBSPGlobalMapLeaf) == 24);

	struct ScenarioStructureBSPLeafPortalVertex {
		Point3D point;
	};
	static_assert(sizeof(ScenarioStructureBSPLeafPortalVertex) == 12);

	struct ScenarioStructureBSPGlobalLeafPortal {
		Memory::BigEndian<std::int32_t> plane_index;
		Memory::BigEndian<std::int32_t> back_leaf_index;
		Memory::BigEndian<std::int32_t> front_leaf_index;
		TagReflexive<ScenarioStructureBSPLeafPortalVertex> vertices;
	};
	static_assert(sizeof(ScenarioStructureBSPGlobalLeafPortal) == 24);

	struct ScenarioStructureBsp {
		TagDependency lightmaps_bitmap;
		Memory::BigEndian<float> vehicle_floor;
		Memory::BigEndian<float> vehicle_ceiling;
		PADDING(20);
		ColorRGB default_ambient_color;
		PADDING(4);
		ColorRGB default_distant_light_0_color;
		Vector3D default_distant_light_0_direction;
		ColorRGB default_distant_light_1_color;
		Vector3D default_distant_light_1_direction;
		PADDING(12);
		ColorARGB default_reflection_tint;
		Vector3D default_shadow_vector;
		ColorRGB default_shadow_color;
		PADDING(4);
		TagReflexive<ScenarioStructureBSPCollisionMaterial> collision_materials;
		TagReflexive<ModelCollisionGeometryBSP> collision_bsp;
		TagReflexive<ScenarioStructureBSPNode> nodes;
		Memory::BigEndian<float> world_bounds_x[2];
		Memory::BigEndian<float> world_bounds_y[2];
		Memory::BigEndian<float> world_bounds_z[2];
		TagReflexive<ScenarioStructureBSPLeaf> leaves;
		TagReflexive<ScenarioStructureBSPSurfaceReference> leaf_surfaces;
		TagReflexive<ScenarioStructureBSPSurface> surfaces;
		TagReflexive<ScenarioStructureBSPLightmap> lightmaps;
		PADDING(12);
		TagReflexive<ScenarioStructureBSPLensFlare> lens_flares;
		TagReflexive<ScenarioStructureBSPLensFlareMarker> lens_flare_markers;
		TagReflexive<ScenarioStructureBSPCluster> clusters;
		TagDataOffset cluster_data;
		TagReflexive<ScenarioStructureBSPClusterPortal> cluster_portals;
		PADDING(12);
		TagReflexive<ScenarioStructureBSPBreakableSurface> breakable_surfaces;
		TagReflexive<ScenarioStructureBSPFogPlane> fog_planes;
		TagReflexive<ScenarioStructureBSPFogRegion> fog_regions;
		TagReflexive<ScenarioStructureBSPFogPalette> fog_palette;
		PADDING(24);
		TagReflexive<ScenarioStructureBSPWeatherPalette> weather_palette;
		TagReflexive<ScenarioStructureBSPWeatherPolyhedron> weather_polyhedra;
		PADDING(24);
		TagReflexive<ScenarioStructureBSPPathfindingSurface> pathfinding_surfaces;
		TagReflexive<ScenarioStructureBSPPathfindingEdge> pathfinding_edges;
		TagReflexive<ScenarioStructureBSPBackgroundSoundPalette> background_sound_palette;
		TagReflexive<ScenarioStructureBSPSoundEnvironmentPalette> sound_environment_palette;
		TagDataOffset sound_pas_data;
		PADDING(24);
		TagReflexive<ScenarioStructureBSPMarker> markers;
		TagReflexive<ScenarioStructureBSPDetailObjectData> detail_objects;
		TagReflexive<ScenarioStructureBSPRuntimeDecal> runtime_decals;
		PADDING(8);
		PADDING(4);
		TagReflexive<ScenarioStructureBSPGlobalMapLeaf> leaf_map_leaves;
		TagReflexive<ScenarioStructureBSPGlobalLeafPortal> leaf_map_portals;
	};
	static_assert(sizeof(ScenarioStructureBsp) == 648);

	struct ScenarioStructureBSPCompiledHeader {
		std::byte *pointer;
		Memory::BigEndian<std::uint32_t> lightmap_material_count;
		std::byte *rendered_vertices;
		Memory::BigEndian<std::uint32_t> lightmap_material_count_again;
		std::byte *lightmap_vertices;
		TagFourCC signature;
	};
	static_assert(sizeof(ScenarioStructureBSPCompiledHeader) == 24);

	struct ScenarioStructureBSPCompiledHeaderCEA {
		std::byte *pointer;
		Memory::BigEndian<std::uint32_t> lightmap_vertex_size;
		Memory::BigEndian<std::uint32_t> lightmap_vertices;
		PADDING(8);
		TagFourCC signature;
	};
	static_assert(sizeof(ScenarioStructureBSPCompiledHeaderCEA) == 24);

}

#endif


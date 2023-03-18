// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__GBXMODEL_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__GBXMODEL_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"
#include "model.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct GBXModelGeometryPart : public ModelGeometryPart {
		PADDING(1);
		PADDING(1);
		PADDING(1);
		Memory::BigEndian<std::uint8_t> local_node_count;
		Memory::BigEndian<std::uint8_t> local_node_indices[22];
		PADDING(2);
	};
	static_assert(sizeof(GBXModelGeometryPart) == 132);

	struct GBXModelGeometry {
		Memory::BigEndian<IsUnusedFlag> flags;
		PADDING(32);
		TagReflexive<GBXModelGeometryPart> parts;
	};
	static_assert(sizeof(GBXModelGeometry) == 48);

	struct Gbxmodel {
		Memory::BigEndian<ModelFlags> flags;
		Memory::BigEndian<std::int32_t> node_list_checksum;
		Memory::BigEndian<float> super_high_detail_cutoff;
		Memory::BigEndian<float> high_detail_cutoff;
		Memory::BigEndian<float> medium_detail_cutoff;
		Memory::BigEndian<float> low_detail_cutoff;
		Memory::BigEndian<float> super_low_detail_cutoff;
		Memory::BigEndian<std::uint16_t> super_low_detail_node_count;
		Memory::BigEndian<std::uint16_t> low_detail_node_count;
		Memory::BigEndian<std::uint16_t> medium_detail_node_count;
		Memory::BigEndian<std::uint16_t> high_detail_node_count;
		Memory::BigEndian<std::uint16_t> super_high_detail_node_count;
		PADDING(2);
		PADDING(8);
		Memory::BigEndian<float> base_map_u_scale;
		Memory::BigEndian<float> base_map_v_scale;
		PADDING(116);
		TagReflexive<ModelMarker> markers;
		TagReflexive<ModelNode> nodes;
		TagReflexive<ModelRegion> regions;
		TagReflexive<GBXModelGeometry> geometries;
		TagReflexive<ModelShaderReference> shaders;
	};
	static_assert(sizeof(Gbxmodel) == 232);

}

#endif


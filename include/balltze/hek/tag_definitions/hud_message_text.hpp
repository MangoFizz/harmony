// SPDX-License-Identifier: GPL-3.0-only
// This file is auto-generated. DO NOT EDIT!

#ifndef BALLTZE_API__HEK__TAG_DEFINITION__HUD_MESSAGE_TEXT_HPP
#define BALLTZE_API__HEK__TAG_DEFINITION__HUD_MESSAGE_TEXT_HPP

#include "../../memory.hpp"
#include "../tag_file.hpp"
#include "enum.hpp"
#include "bitfield.hpp"

namespace Balltze::HEK::TagDefinitions { 
	struct HUDMessageTextElement {
		Memory::BigEndian<std::int8_t> type;
		Memory::BigEndian<std::uint8_t> data;
	};
	static_assert(sizeof(HUDMessageTextElement) == 2);

	struct HUDMessageTextMessage {
		TagString name;
		Index start_index_into_text_blob;
		Index start_index_of_message_block;
		Memory::BigEndian<std::uint8_t> panel_count;
		PADDING(3);
		PADDING(24);
	};
	static_assert(sizeof(HUDMessageTextMessage) == 64);

	struct HudMessageText {
		TagDataOffset text_data;
		TagReflexive<HUDMessageTextElement> message_elements;
		TagReflexive<HUDMessageTextMessage> messages;
		PADDING(84);
	};
	static_assert(sizeof(HudMessageText) == 128);

}

#endif


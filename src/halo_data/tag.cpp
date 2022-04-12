// SPDX-License-Identifier: GPL-3.0-only

#include "tag.hpp"
#include "game_engine.hpp"
#include <optional>

namespace Harmony::HaloData {
    std::byte *get_tag_data_address() noexcept {
        static std::optional<std::byte *> address;
        if(!address.has_value()) {
            switch(game_engine()) {
                case GameEngine::GAME_ENGINE_DEMO:
                    address = reinterpret_cast<std::byte *>(0x4BF10000);
                default:
                    address = reinterpret_cast<std::byte *>(0x40440000);
            }
        }
        return address.value();
    }

    Tag *get_tag(TagID tag_id) noexcept {
        if(tag_id.is_null()) {
            return nullptr;
        }

        auto &tag_data_header = get_tag_data_header();
        auto *tag = tag_data_header.tag_array + tag_id.index.index;
        auto tag_count = tag_data_header.tag_count;

        if(tag_id.index.index <= tag_count) {
            return tag;
        }

        return nullptr;
    }

    Tag *get_tag(std::size_t tag_index) noexcept {
        if(tag_index == 0xFFFFFFFF) {
            return nullptr;
        }

        auto &tag_data_header = get_tag_data_header();
        auto *tag = tag_data_header.tag_array + tag_index;
        auto tag_count = tag_data_header.tag_count;

        if(tag_index <= tag_count) {
            return tag;
        }

        return nullptr;
    }

    Tag *get_tag(std::string path, std::uint32_t tag_class) noexcept {
        auto tag_id = get_tag_id(path.c_str(), tag_class);
        return get_tag(tag_id);
    }
}

// SPDX-License-Identifier: GPL-3.0-only

#include <map>
#include <optional>
#include "widget_render.hpp"

namespace Harmony::Menu {
    std::optional<float> cursor_scale;

    static void on_map_load() {
        cursor_scale = std::nullopt;
    }

    void set_cursor_scale(float scale) noexcept {
        cursor_scale = scale;
    }

    extern "C" void menu_rescale_widget_render_area(HaloData::WidgetRenderArea &rect, HaloData::WidgetInstance *widget) noexcept {
        auto apply_scale = [&rect](float scale) {
            rect.top_right.x = rect.top_left.x + (rect.top_right.x - rect.top_left.x) * scale;
            rect.bottom_right.x = rect.bottom_left.x + (rect.bottom_right.x - rect.bottom_left.x) * scale;
            rect.bottom_right.y = rect.top_right.y + (rect.bottom_right.y - rect.top_right.y) * scale;
            rect.bottom_left.y = rect.top_left.y + (rect.bottom_left.y - rect.top_left.y) * scale;
        };

        if(cursor_scale.has_value()) {
            float width = rect.top_right.x - rect.top_left.x;
            float height = rect.bottom_left.y - rect.top_left.y;

            if(widget == nullptr && width == 32 && height == 32) {
                apply_scale(cursor_scale.value());
            }
        }
    }
}

// SPDX-License-Identifier: GPL-3.0-only

#include "helpers.hpp"

namespace Harmony::Lua {
    std::uint32_t get_widget_id(HaloData::WidgetInstance *widget) noexcept {
        auto &widget_globals = HaloData::WidgetGlobals::get();
        auto *root_widget = widget_globals.root_widget_instance;

        WidgetID widget_id;

        auto &widget_header = widget->get_header();
        widget_id.widget_index = widget_header.index;

        if(widget == root_widget) {
            widget_id.parent_widget_index = widget_header.index;
        }
        else {
            auto *parent_widget = widget->parent_widget;
            auto &parent_widget_header = parent_widget->get_header();
            widget_id.parent_widget_index = parent_widget_header.index;
        }

        return widget_id.id;
    }

    HaloData::WidgetInstance *get_widget_from_id(WidgetID widget_id) noexcept {
        auto &widget_globals = HaloData::WidgetGlobals::get();
        auto *root_widget = widget_globals.root_widget_instance;

        auto *widget = HaloData::get_widget(widget_id.widget_index);
        if(widget) {
            if(widget->parent_widget) {
                auto &parent_widget_header = widget->parent_widget->get_header();
                if(widget_id.parent_widget_index == parent_widget_header.index) {
                    return widget;
                }
            }
            else if(widget == root_widget) {
                auto &widget_header = widget->get_header();
                if(widget_id.parent_widget_index == widget_header.index) {
                    return widget;
                }
            } 
        }
        return nullptr;
    }
}

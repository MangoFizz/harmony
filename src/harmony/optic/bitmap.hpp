// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__OPTIC__BITMAP_HPP
#define HARMONY__OPTIC__BITMAP_HPP

#include <balltze/engine/tag.hpp>
#include "animation.hpp"

namespace Harmony::Optic {
    using BitmapTag = Balltze::Engine::TagDefinitions::Bitmap;

    struct BitmapRenderScale {
        float width;
        float height;
    };

    struct BitmapRenderState {
        std::size_t sprite_index;
        Balltze::Engine::Point2D position;
        BitmapRenderScale scale;
        Balltze::Engine::ColorARGB color_mask;
    };

    class Bitmap {
    private:
        BitmapTag *m_bitmap;
        std::size_t m_sequence_index = 0;
        
        Balltze::Engine::ColorARGB m_color_mask = {255, 255, 255, 255};

    public:
        BitmapTag const *bitmap_tag() const;
        std::size_t sequence_index() const;
        Balltze::Engine::ColorARGB color_mask() const;
        Bitmap(BitmapTag *bitmap, std::size_t sequence_index, Balltze::Engine::ColorARGB color_mask = {255, 255, 255, 255});
    };

    class BitmapRender {
    private:
        Bitmap const *m_bitmap;
        BitmapRenderState m_state;
        AnimationSequence m_animation;

    public:
        void draw();
        BitmapRender(Bitmap const &bitmap, const AnimationSequence &sequence);
    };
}

#endif

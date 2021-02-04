// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_RENDER_GROUP_HPP
#define HARMONY_OPTIC_RENDER_GROUP_HPP

#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <chrono>
#include <cstdint>
#include "../math/geometry.hpp"
#include "sprite.hpp"
#include "animation.hpp"

namespace Harmony::Optic {
    class Render {
    public:
        /**
         * Play an animation
         * @param anim  The animation
         */
        void play_animation(Animation anim) noexcept;

        /**
         * Play an animation. This overload sets custom values on the animation.
         * @param anim              The animation
         * @param transformation    Render state transformation
         * @param duration          Duration in milliseconds
        */
        void play_animation(Animation anim, Animation::StateTransform transformation, long duration) noexcept;

        /**
         * Get the render sprite
         */
        Sprite *get_sprite() noexcept;

        /**
         * Get sprite state
         */
        Sprite::State &get_state() noexcept;

        /**
         * Get active animations
         */
        std::vector<Animation> &get_active_animations() noexcept;

        /**
         * Get sprite timelife
         */
        long get_timelife() const noexcept;

        /**
         * Constructor for Render
         * @param sprite    The sprite that will be rendered
         * @param state     Initial state for sprite
         */
        Render(Sprite *sprite, Sprite::State state) noexcept;

    private:
        /** The sprite itself */
        Sprite *sprite;

        /** Current state of the sprite */
        Sprite::State sprite_state;

        /** Active animations */
        std::vector<Animation> active_animations;

        /** Render start time */
        std::chrono::steady_clock::time_point timestamp;
    };

    class RenderGroup {
    public:
        enum Align {
            ALIGN_LEFT,
            ALIGN_RIGHT,
            ALIGN_CENTER
        };

        /**
         * Get queue position
         */
        Math::Point2D get_position() const noexcept;

        /**
         * Get opacity
         */
        std::uint8_t get_opacity() const noexcept;

        /**
         * Get rotation angle
         */
        float get_rotation() const noexcept;

        /**
         * Get queue align
         */
        Align get_align() const noexcept;

        /**
         * Get sprite default state
         */
        Sprite::State get_sprite_initial_state() noexcept;

        /**
         * Get render duration
         */
        long get_render_duration() const noexcept;

        /**
         * Set render duration
         * @param duration  The duration of the renders in milliseconds
         */
        void set_render_duration(long duration) noexcept;

        /**
         * Get fade in animation
         */
        Animation get_fade_in_anim() const noexcept;

        /**
         * Set fade-in animation
         * @param anim      The animation itself
         */
        void set_fade_in_anim(Animation anim) noexcept;

        /**
         * Get fade out animation
         */
        Animation get_fade_out_anim() const noexcept;

        /**
         * Set fade-out animation
         * @param anim      The animation itself
         */
        void set_fade_out_anim(Animation anim) noexcept;

        /**
         * Get stack slide animation
         */
        Animation &get_slide_anim() noexcept;

        /**
         * Set slide animation
         * @param anim      The animation itself
         */
        void set_slide_anim(Animation anim) noexcept;

        /**
         * Get maximum number of renders
         */
        std::size_t get_maximum_renders() const noexcept;

        /**
         * Get renders
         */
        std::deque<Render> &get_renders() noexcept;

        /**
         * Get sprites queue
         */
        std::queue<Sprite *> const &get_sprites_queue() const noexcept;

        /**
         * Push a sprite to the render queue
         * @param sprite    The sprite that will be rendered
         */
        void enqueue_sprite(Sprite *sprite) noexcept;

        /**
         * Render a sprite from queue
         */
        Render &render_sprite_from_queue() noexcept;

        /**
         * Pop a render from render deque
         */
        void pop_render() noexcept;

        /**
         * Get if is a temp group
         */
        bool single_render() noexcept;

        /**
         * Constructor for RenderGroup
         * @param position
         * @param opacity
         * @param rotation
         * @param align
         */
        RenderGroup(Math::Point2D position, std::uint8_t opacity, float rotation, Align align, long render_duration, std::size_t maximum_renders = 0, bool single_render = false) noexcept;

        /**
         * Void constructor
         */
        RenderGroup() {}

    private:
        /** Position of the render */
        Math::Point2D position;

        /** Opacity of the renders */
        std::uint8_t opacity;

        /** Rotation of the queue in degrees */
        float rotation;

        /** Queue align */
        Align align;

        /** Render duration in ms */
        long render_duration;

        /** Fade in animation */
        Animation fade_in_anim;

        /** Fade out animation */
        Animation fade_out_anim;

        /** Slide animation */
        Animation slide_anim;

        /** Maximum active renders */
        std::size_t max_renders = 0;

        /** Renders */
        std::deque<Render> renders;

        /** Render queue */
        std::queue<Sprite *> queue;

        /**
         * If this is set, the group will be removed after the render timelife ends
         * @todo Find a better way to do this
         */
        bool single_render_group = false;
    };
}

#endif

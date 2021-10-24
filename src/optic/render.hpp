// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_RENDER_HPP
#define HARMONY_OPTIC_RENDER_HPP

#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <chrono>
#include <cstdint>
#include "../math/geometry.hpp"
#include "sprite.hpp"
#include "animation.hpp"
#include "sound.hpp"

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

    class RenderQueue {
    friend class Handler;
    public:
        /**
         * Get queue name
         */
        std::string get_name() const noexcept;

        /**
         * Set queue name
         * @param name  New name for queue
         */
        void set_name(std::string name) noexcept;

        /**
         * Get sprite default state
         */
        Sprite::State get_sprite_initial_state() noexcept;

        /**
         * Get sprites rotation
         */
        float get_rotation() const noexcept;

        /**
         * Get maximum number of renders
         */
        std::size_t get_maximum_renders() const noexcept;

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
         * Get renders
         */
        std::deque<Render> const &get_renders() noexcept;

        /** 
         * Clear enqueued sprites and active renders
         */
        void clear() noexcept;

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
         * Get if is a temp queue
         */
        bool temporal() noexcept;

        /**
         * Constructor for render queue
         * @param name                      Name of the queue
         * @param initial_render_state      Initial state for rendered sprites
         * @param rotation                  Rotation of sprites in degrees
         * @param maximum_renders           Number of simultaneous renderings
         * @param render_duration           Duration of the renders
         * @param temporal                  If true, the queue will be removed after last render timelife ends
         */
        RenderQueue(std::string name, Sprite::State initial_render_state, float rotation, std::size_t maximum_renders, long render_duration, bool temporal = false) noexcept;

        /**
         * Void constructor
         */
        RenderQueue() {}

    private:
        /** Name of the queue */
        std::string name;

        /** Initial state for sprites */
        Sprite::State initial_render_state;

        /** Queue align */
        float rotation;

        /** Maximum active renders */
        std::size_t max_renders;

        /** Render duration in ms */
        long render_duration;

        /** Fade in animation */
        Animation fade_in_anim;

        /** Fade out animation */
        Animation fade_out_anim;

        /** Slide animation */
        Animation slide_anim;

        /** Renders */
        std::deque<Render> renders;

        /** Sprites queue */
        std::queue<Sprite *> sprites_queue;

        /** If this is set, the queue will be removed after last render timelife ends */
        bool temporal_flag;

        /**
         * Render a sprite from queue
         */
        Render &render_sprite_from_queue() noexcept;

        /**
         * Pop a render from render deque
         */
        void pop_render() noexcept;
    };
}

#endif

// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_ANIMATION_HPP
#define HARMONY_OPTIC_ANIMATION_HPP

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <chrono>
#include "../math/geometry.hpp"
#include "sprite.hpp"

namespace Harmony::Optic {
    class Animation {
    public:
        /** Animation frame type */
        using Frame = float;

        struct StateTransform {
            Math::Point2D position;
            int opacity;
            Math::Angle rotation;

            StateTransform() {
                position = {0.0f, 0.0f};
                opacity = 0;
                rotation = 0;
            }
        };

        enum Trigger {
            TRIGGER_FADE_IN,
            TRIGGER_FADE_OUT,
            TRIGGER_SLIDE,
            TRIGGER_NONE,
            TRIGGER_INVALID
        };

        /**
         * @todo Add scale to targets
         */
        enum Target {
            TARGET_POSITION_X,
            TARGET_POSITION_Y,
            TARGET_ROTATION,
            TARGET_OPACITY,
            TARGET_INVALID
        };

        /**
         * Get the duration of the animation
         */
        long get_duration() const noexcept;

        /**
         * Set duration of the animation
         * @param new_value     New duration in milliseconds
         */
        void set_duration(long new_value) noexcept;

        /**
         * Get render state transform
         */
        StateTransform get_transform() const noexcept;

        /**
         * Set render state transform
         * @param new_value     New transform for render state
         */
        void set_transform(StateTransform new_value) noexcept;

        /**
         * Add target
         * @param target    Target to apply animation
         * @param curve     The quadratic bezier used to generate the target frames
         */
        void add_target(Target target, Math::QuadraticBezier curve) noexcept;

        /**
         * Play the animation
         */
        void play() noexcept;

        /**
         * Stop the animation
         */
        void stop() noexcept;

        /**
         * Get if the animation is currently playing
         */
        bool is_playing() const noexcept;

        /**
         * Apply the current state of the animation transform to render state
         * @param state     Reference to render state
         */
        void apply_transform(Sprite::State &state) noexcept;

        /**
         * Get the time left of the animation
         * @return  Time in milliseconds
         */
        long get_time_left() noexcept;

        /**
         * Get animation tag
         */
        const char *get_tag() const noexcept;

        /**
         * Set animation tag
         * @param tag   New tag for animation
         */
        void set_tag(const char *new_tag) noexcept;

        /**
         * Constructor for animation
         * @param transformation    Transformation for render state
         * @param duration          Duration of the animation in milliseconds
         */
        Animation(StateTransform transformation, long duration) noexcept;

        /**
         * Void constructor for animation
         */
        Animation() {}

        /**
         * Destructor for animation
         */
        ~Animation() noexcept;

        /**
         * Equals operator for std::find function
         */
        inline bool operator==(const Animation& anim) {
            return this->tag == anim.get_tag();
        }

        /**
         * Get a trigger from a given string
         * @param trigger_name  Name of the desired trigger
         * @return              The trigger itself
         */
        static Trigger get_trigger_from_string(const char *trigger_name) noexcept;

        /**
         * Get a target from a given string
         * @param target_name   Name of the desired target
         * @return              The target itself
         */
        static Target get_target_from_string(const char *target_name) noexcept;

        /**
         * Generic curves
         */
        static Math::QuadraticBezier flat() noexcept;
        static Math::QuadraticBezier linear() noexcept;
        static Math::QuadraticBezier ease_in() noexcept;
        static Math::QuadraticBezier ease_out() noexcept;
        static Math::QuadraticBezier ease_in_out() noexcept;

    private:
        /** Curves of the animation */
        std::map<Target, Math::QuadraticBezier> curves;

        /** Animation is playing */
        bool playing = false;

        /** Transformation of the render state */
        StateTransform render_state_transform;

        /** Duration in milliseconds */
        long duration = 0;

        /** Animation start time */
        std::chrono::steady_clock::time_point start_time;

        /** Tag or ID of the animation. This is useful when we need a way to identify this animation. */
        std::string tag;

        /**
         * Set up default animation
         */
        void set_up_default_animation() noexcept;
    };
}

#endif

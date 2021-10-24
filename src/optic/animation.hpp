// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_ANIMATION_HPP
#define HARMONY_OPTIC_ANIMATION_HPP

#include <string>
#include <map>
#include <chrono>
#include "../math/geometry.hpp"
#include "sprite.hpp"

namespace Harmony::Optic {
    class Animation {
    public:
        struct StateTransform {
            Math::Point2D position;
            Sprite::Scale scale;
            int opacity;
            float rotation;

            StateTransform() {
                position = {0.0f, 0.0f};
                scale = {0.0f, 0.0f};
                opacity = 0;
                rotation = 0;
            }
        };

        /**
         * @todo Move this enum to Render
         */
        enum RenderProperty {
            RENDER_PROPERTY_POSITION_X,
            RENDER_PROPERTY_POSITION_Y,
            RENDER_PROPERTY_ROTATION,
            RENDER_PROPERTY_OPACITY,
            RENDER_PROPERTY_SCALE_X,
            RENDER_PROPERTY_SCALE_Y,
            RENDER_PROPERTY_INVALID
        };

        /**
         * Get animation name
         */
        std::string get_name() const noexcept;

        /**
         * Set animation name
         * @param name  New name for animation
         */
        void set_name(std::string name) noexcept;

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
         * Set an animation curve for a property
         * @param property      Render property
         * @param curve         The quadratic bezier used to generate the property frames
         */
        void set_property_curve(RenderProperty property, Math::QuadraticBezier curve) noexcept;

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
         * Constructor for animation
         * @param name              Name of the animation
         * @param transformation    Transformation for render state
         * @param duration          Duration of the animation in milliseconds
         */
        Animation(std::string name, StateTransform transformation, long duration) noexcept;

        /**
         * Constructor for animation with default transformation
         * @param name              Name of the animation
         * @param duration          Duration of the animation in milliseconds
         */
        Animation(std::string name, long duration) noexcept;

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
            return this->name == anim.get_name();
        }

        /**
         * Get a property from a given string
         * @param property_name     Name of the desired property
         * @return                  The property itself
         */
        static RenderProperty get_render_property_from_string(const char *property_name) noexcept;

        /**
         * Generic curves
         */
        static Math::QuadraticBezier flat() noexcept;
        static Math::QuadraticBezier linear() noexcept;
        static Math::QuadraticBezier ease_in() noexcept;
        static Math::QuadraticBezier ease_out() noexcept;
        static Math::QuadraticBezier ease_in_out() noexcept;

    private:
        /** Name of the animation */
        std::string name;

        /** Curves of the animation */
        std::map<RenderProperty, Math::QuadraticBezier> curves;

        /** Animation is playing */
        bool playing = false;

        /** Transformation of the render state */
        StateTransform render_state_transform;

        /** Duration in milliseconds */
        long duration = 0;

        /** Animation start time */
        std::chrono::steady_clock::time_point start_time;

        /**
         * Set up default animation
         */
        void set_up_default_animation() noexcept;
    };
}

#endif

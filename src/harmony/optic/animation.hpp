// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY__OPTIC__ANIMATION_HPP
#define HARMONY__OPTIC__ANIMATION_HPP

#include <string>
#include <map>
#include <chrono>
#include <optional>
#include <balltze/math.hpp>
#include <balltze/engine/core.hpp>
#include "bitmap.hpp"

namespace Harmony::Optic {
    using BezierCurve = Balltze::Math::QuadraticBezier;

    struct AnimationProgress {
        Engine::Point2D position;
        Sprite::Scale scale;
        int opacity;
        float rotation;

        AnimationProgress() {
            position = {0.0f, 0.0f};
            scale = {0.0f, 0.0f};
            opacity = 0;
            rotation = 0;
        }
    };

    enum AnimationProperty {
        ANIMATION_PROPERTY_POSITION_X,
        ANIMATION_PROPERTY_POSITION_Y,
        ANIMATION_PROPERTY_ROTATION,
        ANIMATION_PROPERTY_OPACITY,
        ANIMATION_PROPERTY_SCALE_X,
        ANIMATION_PROPERTY_SCALE_Y
    };

    class AnimationSequence {
    private:
        struct PropertyTransition {
            /** Duration in milliseconds */
            long duration;
            
            /** The curve used to generate the property frames */
            BezierCurve curve;
        };

        /** Animation curves */
        std::map<AnimationProperty, std::vector<PropertyTransition>> m_properties_sequences;

        /** Animation is playing */
        bool m_playing = false;

        /** Animation progress */
        AnimationProgress m_progress;

        /** Animation start time */
        std::chrono::steady_clock::time_point m_start_timestamp;

        /** Animation duration buffer */
        std::optional<long> m_max_duration_buffer;

    public:
        /**
         * Get the duration of the whole animation (in milliseconds)
         */
        long duration() noexcept;

        /**
         * Get render state transform
         */
        AnimationProgress progress() const noexcept;

        /**
         * Set a property of the animation
         * @param property      Animation property
         * @param curve         The quadratic bezier used to generate the property frames
         * @param duration      Duration of the animation for this property in milliseconds
         */
        void add_property_curve(AnimationProperty property, BezierCurve curve, long duration) noexcept;

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
        bool playing() const noexcept;

        /**
         * Apply the current state of the animation transform to a render state
         * @param state     Reference to render state
         */
        void apply_progress(Sprite::State &state) noexcept;

        /**
         * Get the time left of the animation
         * @return  Time in milliseconds
         */
        long get_time_left() noexcept;

        /**
         * Default constructor for animation
         */
        Animation() = default;

        /**
         * Destructor for animation
         */
        ~Animation() noexcept;
    };

    /**
     * Get a property from a given string
     * @param property_name     Name of the desired property
     * @return                  The property itself
     */
    AnimationProperty property_from_string(const char *property_name);

    /**
     * Generic curves for animations
     */
    BezierCurve static_curve() noexcept;
    BezierCurve flat_curve() noexcept;
    BezierCurve linear_curve() noexcept;
    BezierCurve ease_in_curve() noexcept;
    BezierCurve ease_out_curve() noexcept;
    BezierCurve ease_in_out_curve() noexcept;
}

#endif

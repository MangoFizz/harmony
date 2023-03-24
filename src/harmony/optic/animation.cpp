// SPDX-License-Identifier: GPL-3.0-only

#include "animation.hpp"

namespace Harmony::Optic {
    long Animation::duration() noexcept {
        if(!m_max_duration_buffer) {
            long max_duration = 0;
            for(auto const &[property, data] : m_properties) {
                if(data.duration > max_duration) {
                    max_duration = data.duration;
                }
            }
            m_max_duration_buffer = max_duration;
        }
        return *m_max_duration_buffer;
    }

    AnimationProgress Animation::progress() const noexcept {
        return m_progress;
    }

    void Animation::set_property(AnimationProperty property, BezierCurve curve, long duration) noexcept {
        m_properties[property] = {duration, curve};
    }

    void Animation::play() noexcept {
        if(!m_playing && duration() > 0) {
            m_start_timestamp = std::chrono::steady_clock::now();
            m_playing = true;
        }
    }

    void Animation::stop() noexcept {
        m_playing = false;
    }

    bool Animation::playing() const noexcept {
        return m_playing;
    }

    void Animation::apply_progress(Sprite::State &state) noexcept {
        auto now = std::chrono::steady_clock::now();
        long timelife = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start_timestamp).count();

        auto get_curve_point = [&timelife](auto data) -> float {
            float t = static_cast<float>(timelife) / data.duration;
            if(t > 1) {
               t = 1;
            }
            return data.curve.get_point(t).y;
        };
        
        for(auto &[property, data] : m_properties) {
            switch(property) {
                case ANIMATION_PROPERTY_POSITION_X: {
                    float t = static_cast<float>(timelife) / data.duration;
                    state.position.x += this->m_progress.position.x * get_curve_point(data);
                    break;
                }
                case ANIMATION_PROPERTY_POSITION_Y: {
                    float t = static_cast<float>(timelife) / data.duration;
                    state.position.y += this->m_progress.position.y * get_curve_point(data);
                    break;
                }
                case ANIMATION_PROPERTY_OPACITY: {
                    float t = static_cast<float>(timelife) / data.duration;
                    state.color.alpha += this->m_progress.opacity * get_curve_point(data);
                    break;
                }
                case ANIMATION_PROPERTY_ROTATION: {
                    float t = static_cast<float>(timelife) / data.duration;
                    state.rotation += m_progress.rotation * get_curve_point(data);
                    break;
                }
                case ANIMATION_PROPERTY_SCALE_X: {
                    float t = static_cast<float>(timelife) / data.duration;
                    state.scale.x += m_progress.scale.x * get_curve_point(data);
                    if(state.scale.x < 0) {
                        state.scale.x = 0;
                    }
                    break;
                }
                case ANIMATION_PROPERTY_SCALE_Y: {
                    float t = static_cast<float>(timelife) / data.duration;
                    state.scale.y += m_progress.scale.y * get_curve_point(data);
                    if(state.scale.y < 0) {
                        state.scale.y = 0;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    long Animation::get_time_left() noexcept {
        if(!m_playing) {
            return 0;
        }
        auto now = std::chrono::steady_clock::now();
        auto timelife = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start_timestamp).count();
        long timeleft = duration() - timelife;
        if(timeleft < 0) {
            timeleft = 0;
        }
        return timeleft;
    }

    Math::QuadraticBezier Animation::flat() noexcept {
        return Math::QuadraticBezier({0.0f, 0.0f}, {0.0f, 0.0f});
    }

    Math::QuadraticBezier Animation::linear() noexcept {
        return Math::QuadraticBezier({0.0f, 0.0f}, {1.0f, 1.0f});
    }

    Math::QuadraticBezier Animation::ease_in() noexcept {
        return Math::QuadraticBezier({0.4f, 0.0f}, {1.0f, 1.0f});
    }

    Math::QuadraticBezier Animation::ease_out() noexcept {
        return Math::QuadraticBezier({0.0f, 0.0f}, {0.6f, 1.0f});
    }

    Math::QuadraticBezier Animation::ease_in_out() noexcept {
        return Math::QuadraticBezier({0.4f, 0.0f}, {0.6f, 1.0f});
    }

    AnimationProperty property_from_string(const char *property_name) {
        std::string target_str = property_name;
        if(target_str == "position x") {
            return ANIMATION_PROPERTY_POSITION_X;
        }
        else if(target_str == "position y") {
            return ANIMATION_PROPERTY_POSITION_Y;
        }
        else if(target_str == "rotation") {
            return ANIMATION_PROPERTY_ROTATION;
        }
        else if(target_str == "opacity") {
            return ANIMATION_PROPERTY_OPACITY;
        }
        else if(target_str == "scale x") {
            return ANIMATION_PROPERTY_SCALE_X;
        }
        else if(target_str == "scale y") {
            return ANIMATION_PROPERTY_SCALE_Y;
        }
        else {
            throw std::runtime_error("Invalid animation property name");
        }
    }
}

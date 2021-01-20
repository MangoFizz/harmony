// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_SPRITE_HPP
#define HARMONY_OPTIC_SPRITE_HPP

#include <filesystem>
#include "../math/color.hpp"
#include "../math/geometry.hpp"
#include <d3dx9.h>
#include <d3dx9tex.h>

namespace Harmony::Optic {
    class Sprite {
    public:
        struct State {
            Math::Point2D position;
            Math::ColorARGB color;
            Math::Angle rotation;

            State() {
                position = {0.0f, 0.0f};
                color = {255, 255, 255, 255};
                rotation = 0;
            }
        };

        /**
         * Get sprite width
         */
        int get_width() const noexcept;

        /**
         * Get sprite height
         */
        int get_height() const noexcept;

        /**
         * Load sprite into device
         * @param device    Direct3D 9 device
         */
        void load(LPDIRECT3DDEVICE9 device) noexcept;

        /**
         * Release sprite
         */
        void unload() noexcept;

        /**
         * Draw sprite
         * @param position          Posion of the render
         * @param color_modifier    Color modifier
         */
        void draw(Math::Point2D position, Math::ColorARGB color_modifier) const noexcept;

        /**
         * Default constructor for sprite
         * @param texture   Path of the texture
         * @param size      Texture dimentions
         */
        Sprite(const char *texture, int width, int height) noexcept;

        /**
         * Default constructor
         */
        Sprite() {}

        /**
         * Default destructor for sprite
         */
        ~Sprite() noexcept;

    private:
        /** Path of texture sprite */
        std::filesystem::path texture_path;

        /** Sprite width */
        int width = 0;

        /** Sprite height */
        int height = 0;

        /** D3D9 texture of sprite */
        LPDIRECT3DTEXTURE9 texture;

        /** The sprite itself */
        LPD3DXSPRITE sprite;

        /** Is the sprite loaded? */
        bool loaded = false;
    };
}

#endif

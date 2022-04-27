// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_OPTIC_SPRITE_HPP
#define HARMONY_OPTIC_SPRITE_HPP

#include <filesystem>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include "../math/color.hpp"
#include "../math/geometry.hpp"
#include "sound.hpp"

namespace Harmony::Optic {

    class Sprite {
    public:
        struct Scale {
            float x;
            float y;
        };

        struct State {
            Math::Point2D position;
            Scale scale;
            Math::ColorARGB color;
            float rotation;
            std::size_t current_frame;

            State() {
                position = {0.0f, 0.0f};
                scale = {1.0f, 1.0f};
                color = {255, 255, 255, 255};
                rotation = 0;
                current_frame = 0;
            }
        };

        struct Offset {
            int x;
            int y;
        };

        /**
         * Get sprite name
         */
        std::string get_name() const noexcept;

        /**
         * Set sprite name
         * @param name  New name for sprite
         */
        void set_name(std::string name) noexcept;

        /**
         * Get the number of frames of sprite
         */
        std::size_t get_frame_count() const noexcept;

        /**
         * Get sprite width
         */
        int get_width() const noexcept;

        /**
         * Get sprite height
         */
        int get_height() const noexcept;

        /**
         * Get frames per second
         */
        std::size_t get_frames_per_second() const noexcept;

        /**
         * Load sprite into device
         * @param device    Direct3D 9 device
         */
        void load(LPDIRECT3DDEVICE9 device);

        /**
         * Release sprite
         */
        void unload() noexcept;

        /**
         * Draw sprite
         * @param sprite_state  State of sprite
         */
        void draw(State const &sprite_state) const noexcept;

        /**
         * Default constructor for sprite
         * @param texture   Texture path
         * @param width     Width of sprite frames
         * @param height    Height of sprite frames
         * @exception       If texture file does not exists
         */
        Sprite(std::string texture, int width, int height);

        /**
         * Default constructor for sprite
         * @param texture               Texture path
         * @param sheet_rows            Number of rows in the sheet
         * @param sheet_columns         Number of columns in the sheet
         * @param sheet_frames          Number of frames in the sheet
         * @param frames_per_second     Amount of frames per second
         * @param frame_width           Width of the sprite
         * @param frame_height          Height of the sprite
         * @exception                   If texture file does not exists
         */
        Sprite(std::string texture, std::size_t sheet_rows, std::size_t sheet_columns, std::size_t sheet_frames, std::size_t frames_per_second, int frame_width, int frame_height);

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

        /** Sprite texture width */
        int texture_width;

        /** Sprite texture height */
        int texture_height;

        /** Frame width */
        int frame_width;

        /** Frame height */
        int frame_height;

        /** Number of frames */
        std::size_t frame_count = 1;

        /** Frames per second */
        std::size_t fps = 1;

        /** Frames offsets */
        std::vector<RECT> frames_offets;

        /** D3D9 texture of sprite */
        LPDIRECT3DTEXTURE9 texture;

        /** The sprite itself */
        LPD3DXSPRITE sprite;

        /** Is the sprite loaded? */
        bool loaded_flag = false;
    };
}

#endif

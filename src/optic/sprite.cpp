// SPDX-License-Identifier: GPL-3.0-only

#include <d3dx9math.h>
#include "../messaging/exception.hpp"
#include "exception.hpp"
#include "sprite.hpp"

namespace Harmony::Optic {
    std::size_t Sprite::get_frame_count() const noexcept {
        return this->frame_count;
    }

    int Sprite::get_width() const noexcept {
        return this->frame_width;
    }

    int Sprite::get_height() const noexcept {
        return this->frame_height;
    }

    std::size_t Sprite::get_frames_per_second() const noexcept {
        return this->fps;
    }

    void Sprite::load(LPDIRECT3DDEVICE9 device) {
        if(this->loaded_flag) {
            return;
        }

        int width = this->texture_width;
        int height = this->texture_height;
        int mip_levels = 0;
        int color_key = 0;

        if(D3DXCreateTextureFromFileExW(device, this->texture_path.c_str(), width, height, mip_levels, 0, 
                                        D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT_NONPOW2,
                                        color_key, NULL, NULL, &this->texture) != D3D_OK) {
            throw ExceptionBox("Failed to create texture.");
        }

        if(D3DXCreateSprite(device, &this->sprite) != D3D_OK) {
            throw ExceptionBox("Failed to create sprite.");
        }

        this->loaded_flag = true;
    }
    
    void Sprite::unload() noexcept {
        if(!this->loaded_flag) {
            return;
        }

        this->sprite->Release();
        this->texture->Release();

        this->loaded_flag = false;
    }

    void Sprite::draw(Sprite::State const &state) const noexcept {
        if(this->loaded_flag) {
            D3DXVECTOR3 position;
            position.x = state.position.x;
            position.y = state.position.y;
            position.z = 0;

            D3DXVECTOR2 scale_center;
            scale_center.x = state.position.x;
            scale_center.y = state.position.y;

            D3DXVECTOR2 scale;
            scale.x = state.scale.x;
            scale.y = state.scale.y;

            D3DXVECTOR2 rotation_center;
            rotation_center.x = state.position.x + this->frame_width / 2;
            rotation_center.y = state.position.y + this->frame_height / 2;

            auto &rotation = state.rotation;

            auto &color = state.color;

            D3DXMATRIX new_transform;
            D3DXMatrixTransformation2D(&new_transform, &scale_center, 0.0f, &scale, &rotation_center, rotation, NULL);

            // Update transform
            this->sprite->SetTransform(&new_transform);

            // Texture region to draw
            const RECT *frame_offset = nullptr;
            if(this->frame_count > 1) {
                frame_offset = &this->frames_offets[state.current_frame];
            }
            
            this->sprite->Begin(D3DXSPRITE_ALPHABLEND);
            this->sprite->Draw(this->texture, frame_offset, NULL, &position, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
            this->sprite->End();
        }
    }

    Sprite::Sprite(std::string texture, int width, int height) {
        if(!std::filesystem::exists(texture)) {
            throw Exception("Texture file '" + texture + "' does not exists!");
        }

        this->texture_path = texture;
        this->texture_width = width;
        this->texture_height = height;
        this->frame_width = width;
        this->frame_height = height;
    }

    Sprite::Sprite(std::string texture, std::size_t sheet_rows, std::size_t sheet_columns, std::size_t sheet_frames, std::size_t frames_per_second, int frame_width, int frame_height) {
        if(!std::filesystem::exists(texture)) {
            throw Exception("Texture file '" + texture + "' does not exists!");
        }

        this->texture_path = texture;
        this->texture_width = frame_width * sheet_columns;
        this->texture_height = frame_height * sheet_rows;
        this->frame_width = frame_width;
        this->frame_height = frame_height;
        this->frame_count = sheet_frames;
        this->fps = frames_per_second;

        for(std::size_t frame = 0, row = 0, column = 0; frame < sheet_frames; frame++) {
            int offset_x = 1 + column * frame_width;
            int offset_y = 1 + row * frame_height;
            this->frames_offets.push_back({offset_x, offset_y, offset_x + this->frame_width, offset_y + this->frame_height});
            
            column++;
            if(column == sheet_columns) {
                column = 0;
                row++;
            }
        }
    }

    Sprite::~Sprite() noexcept {
        this->unload();
    }
}

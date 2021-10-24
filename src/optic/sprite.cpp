// SPDX-License-Identifier: GPL-3.0-only

#include <d3dx9math.h>
#include "../messaging/exception.hpp"
#include "exception.hpp"
#include "sprite.hpp"

namespace Harmony::Optic {
    std::string Sprite::get_name() const noexcept {
        return this->name;
    }

    void Sprite::set_name(std::string name) noexcept {
        this->name = name;
    }

    int Sprite::get_width() const noexcept {
        return this->width;
    }

    int Sprite::get_height() const noexcept {
        return this->height;
    }

    void Sprite::load(LPDIRECT3DDEVICE9 device) {
        if(this->loaded_flag) {
            return;
        }

        auto file = this->texture_path.string();
        int width = this->width;
        int height = this->height;
        int mip_levels = 0;
        int color_key = 0;

        if(D3DXCreateTextureFromFileExA(device, file.c_str(), width, height, mip_levels, 0, 
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
            rotation_center.x = state.position.x + this->width / 2;
            rotation_center.y = state.position.y + this->height / 2;

            auto &rotation = state.rotation;

            auto &color = state.color;

            D3DXMATRIX new_transform;
            D3DXMatrixTransformation2D(&new_transform, &scale_center, 0.0f, &scale, &rotation_center, rotation, NULL);

            // Update transform
            this->sprite->SetTransform(&new_transform);
            
            this->sprite->Begin(D3DXSPRITE_ALPHABLEND);
            this->sprite->Draw(this->texture, NULL, NULL, &position, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
            this->sprite->End();
        }
    }

    Sprite::Sprite(std::string name, std::string texture, int width, int height) {
        if(!std::filesystem::exists(texture)) {
            throw Exception("Texture file for sprite '" + name + "' does not exists!");
        }

        this->name = name;
        this->texture_path = texture;
        this->width = width;
        this->height = height;
    }

    Sprite::~Sprite() noexcept {
        this->unload();
    }
}

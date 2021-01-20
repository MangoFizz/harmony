// SPDX-License-Identifier: GPL-3.0-only

#include "../messaging/console_output.hpp"
#include "../messaging/message_box.hpp"
#include "sprite.hpp"

namespace Harmony::Optic {
    int Sprite::get_width() const noexcept {
        return this->width;
    }

    int Sprite::get_height() const noexcept {
        return this->height;
    }

    void Sprite::load(LPDIRECT3DDEVICE9 device) noexcept {
        if(this->loaded) {
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
            message_box("Failed to create texture");
            std::terminate();
        }

        if(D3DXCreateSprite(device, &this->sprite) != D3D_OK) {
            message_box("Failed to create sprite");
            std::terminate();
        }

        this->loaded = true;
    }
    
    void Sprite::unload() noexcept {
        if(!this->loaded) {
            return;
        }

        this->sprite->Release();
        this->texture->Release();

        this->loaded = false;
    }

    void Sprite::draw(Math::Point2D offset, Math::ColorARGB color) const noexcept {
        if(this->loaded) {
            D3DXVECTOR3 position;
            position.x = offset.x;
            position.y = offset.y;
            position.z = 0;

            this->sprite->Begin(D3DXSPRITE_ALPHABLEND); 
            this->sprite->Draw(this->texture, NULL, NULL, &position, D3DCOLOR_RGBA(color.r, color.g, color.b, color.a));
            this->sprite->End();
        }
    }

    Sprite::Sprite(const char *texture, int width, int height) noexcept {
        if(!std::filesystem::exists(texture)) {
            message_box("Texture \"%s\" not found!", texture);
            std::terminate();
        }

        this->texture_path = texture;
        this->width = width;
        this->height = height;
    }

    Sprite::~Sprite() noexcept {
        this->unload();
    }
}

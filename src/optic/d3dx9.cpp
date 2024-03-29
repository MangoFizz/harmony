// SPDX-License-Identifier: GPL-3.0-only

#include <windows.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include "../messaging/message_box.hpp"

/** Call a function from another module */
#define CALLPROC(module, function, ...) reinterpret_cast<decltype(function) *>(GetProcAddress(module, #function))(__VA_ARGS__)

/** d3dx9_43 instance */
static HINSTANCE d3dx9_43;

static void load_d3dx9() noexcept {
    if(d3dx9_43) {
        return;
    }

    // Get system d3dx9_43.dll path
    char path[MAX_PATH];
    GetSystemDirectoryA(path, MAX_PATH);
    strcat(path, "\\d3dx9_43.dll");

    // Load it!
    d3dx9_43 = LoadLibraryA(path);

    // Check if d3dx9_43.dll was loaded successfully
    if(!d3dx9_43) {
        Harmony::message_box("Cannot load system d3dx9_43.dll");
        std::abort();
    }
}

HRESULT WINAPI D3DXCreateTextureFromFileExW(IDirect3DDevice9 *device, const wchar_t *srcfile, UINT width, UINT height, UINT miplevels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mipfilter, D3DCOLOR colorkey, D3DXIMAGE_INFO *srcinfo, PALETTEENTRY *palette, struct IDirect3DTexture9 **texture) {
    load_d3dx9();
    return CALLPROC(d3dx9_43, D3DXCreateTextureFromFileExW, device, srcfile, width, height, miplevels, usage, format, pool, filter, mipfilter, colorkey, srcinfo, palette, texture);
}

HRESULT WINAPI D3DXCreateSprite(struct IDirect3DDevice9 *device, struct ID3DXSprite **sprite) {
    load_d3dx9();
    return CALLPROC(d3dx9_43, D3DXCreateSprite, device, sprite);
}

D3DXMATRIX* WINAPI D3DXMatrixTransformation2D(D3DXMATRIX *pout, const D3DXVECTOR2 *pscalingcenter, FLOAT scalingrotation, const D3DXVECTOR2 *pscaling, const D3DXVECTOR2 *protationcenter, FLOAT rotation, const D3DXVECTOR2 *ptranslation) {
    load_d3dx9();
    return CALLPROC(d3dx9_43, D3DXMatrixTransformation2D, pout, pscalingcenter, scalingrotation, pscaling, protationcenter, rotation, ptranslation);
}

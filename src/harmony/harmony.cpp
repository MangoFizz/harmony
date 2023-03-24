// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>
#include <balltze/output.hpp>
#include <balltze/api.hpp>

BALLTZE_PLUGIN_API bool plugin_init() noexcept {
    std::cout << "Harmony initialized" << std::endl;
    return true;
}

BALLTZE_PLUGIN_API void plugin_start() noexcept {
    Balltze::console_printf("Harmony started from Balltze!");
}

WINAPI BOOL DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    return TRUE;
}

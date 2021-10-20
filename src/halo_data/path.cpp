// SPDX-License-Identifier: GPL-3.0-only

#include "../memory/signature.hpp"
#include "../harmony.hpp"
#include "path.hpp"

namespace Harmony::HaloData {
    using Path = std::filesystem::path;

    Path get_path() noexcept {
        static const char *path = nullptr;
        if(!path) {
            path = *reinterpret_cast<const char **>(Harmony::get().get_signature("halo_path").get_data());
        }
        return Path(path);
    }
}

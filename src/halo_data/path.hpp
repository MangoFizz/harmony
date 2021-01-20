// SPDX-License-Identifier: GPL-3.0-only

#ifndef CHIMERA_PATH_HPP
#define CHIMERA_PATH_HPP

#include <filesystem>

namespace Harmony::HaloData {
    /**
     * Get the Halo profile path
     * @return Halo profile path
     */
    std::filesystem::path get_path() noexcept;
}

#endif

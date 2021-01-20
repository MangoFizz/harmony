// SPDX-License-Identifier: GPL-3.0-only

#ifndef HARMONY_CLIENT_SIGNATURES_HPP
#define HARMONY_CLIENT_SIGNATURES_HPP

#include <vector>

namespace Harmony {
    class Signature;

    /**
     * Find all the signatures
     * @return  Vector with all the signatures
     */
    std::vector<Signature> find_client_signatures();
}

#endif

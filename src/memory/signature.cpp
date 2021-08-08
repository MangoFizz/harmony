// SPDX-License-Identifier: GPL-3.0-only

#include <cstring>
#include "codefinder.hpp"
#include "memory.hpp"
#include "signatures/client.hpp"
#include "signature.hpp"

namespace Harmony {
    using namespace Memory;

    const char *Signature::get_name() const noexcept {
        return this->name.c_str();
    }

    std::byte *Signature::get_data() const noexcept {
        return this->data;
    }

    void Signature::restore() noexcept {
        overwrite(this->data, this->original_data.data(), this->original_data.size());
    }

    Signature::Signature(const char *name, const short *signature, std::size_t lenght, std::uint16_t offset) {
        // Find it!
        auto *address = reinterpret_cast<std::byte *>(FindCode(GetModuleHandle(0), signature, lenght));

        if(address) {
            this->name = name;
            this->data = address + offset;
            this->original_data.insert(this->original_data.begin(), this->data, this->data + lenght - offset);
        }
        else {
            char message[256] = {};
            std::sprintf(message, "Could not find %s signature.", name);
            MessageBoxA(NULL, message, "Harmony: missing signature", MB_OK);
            std::terminate();
        }
    }

    std::vector<Signature> Signature::find_signatures() {
        return find_client_signatures();
    }
}
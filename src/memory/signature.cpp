// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>
#include <cstring>
#include "../messaging/message_box.hpp"
#include "codefinder.hpp"
#include "memory.hpp"
#include "signatures/client.hpp"
#include "signature.hpp"

namespace Harmony {
    using namespace Memory;

    std::string Signature::get_name() const noexcept {
        return this->name;
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
            std::cout << std::endl << "Could not find " << name << " signature." << std::endl;
            std::terminate();
        }
    }

    std::vector<Signature> Signature::find_signatures() {
        return find_client_signatures();
    }
}
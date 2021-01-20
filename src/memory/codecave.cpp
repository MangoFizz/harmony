// SPDX-License-Identifier: GPL-3.0-only

#include <memory>
#include "../messaging/message_box.hpp"
#include "memory.hpp"
#include "codecave.hpp"

namespace Harmony {
    void Codecave::write_function_call(std::size_t &offset, void *function, bool pushad) noexcept {
        if(pushad) {
            // pushfd
            this->data[offset + 0] = 0x9C;
            // pushad
            this->data[offset + 1] = 0x60;

            offset += 2;
        }

        // call
        this->data[offset + 0] = 0xE8;
        auto *call_offset = reinterpret_cast<std::uint32_t *>(&this->data[offset + 1]);
        *call_offset = reinterpret_cast<std::uint32_t>(function) - (reinterpret_cast<std::uint32_t>(call_offset) + 4);

        offset += 5;

        if(pushad) {
            // popad
            this->data[offset + 0] = 0x61;
            // popfd
            this->data[offset + 1] = 0x9D;

            offset += 2;
        }
    }

    void Codecave::copy_intruction(std::size_t &offset, void *instruction, std::size_t length) noexcept {
        overwrite(&this->data[offset], reinterpret_cast<std::uint8_t *>(instruction), length);
        offset += length;
    }

    void Codecave::write_skip_code_check(std::size_t &offset, std::uint8_t bytes) noexcept {
        // Check if the skip flag is set
        this->data[offset + 0] = 0x83;
        this->data[offset + 1] = 0x3D;
        auto skip_code_address = reinterpret_cast<std::uint32_t>(&this->skip_og_code);
        *reinterpret_cast<std::uint32_t *>(&this->data[offset + 2]) = skip_code_address;
        this->data[offset + 6] = true;

        // je
        this->data[offset + 7] = 0x74;
        this->data[offset + 8] = bytes;

        offset += 9;
    }

    void Codecave::write_exit(std::size_t &offset, void *address) noexcept {
        this->data[offset + 0] = 0xE9;
        auto *jmp_offset = reinterpret_cast<std::uint32_t *>(&this->data[offset + 1]);
        *jmp_offset = reinterpret_cast<std::uint32_t>(address) - (reinterpret_cast<std::uint32_t>(jmp_offset) + 4);

        offset += 5;
    }

    void Codecave::hook(void *address, std::size_t offset) noexcept {
        auto *ptr = reinterpret_cast<std::byte *>(address);
        overwrite(ptr, static_cast<std::uint8_t>(0xE9));
        overwrite(ptr + 1, reinterpret_cast<std::uint32_t>(&this->data[offset]) - reinterpret_cast<std::uint32_t>(ptr + 5));
    }

    void Codecave::write_basic_hook(void *function, void *address, bool pushad) noexcept {
        // Keep everything tracked
        std::size_t offset = this->data_size;

        this->write_function_call(offset, function, pushad);

        // Set skip code flag check
        this->write_skip_code_check(offset, 0);

        auto *instruction = static_cast<std::byte *>(address);
        std::size_t instruction_size;
        std::uint32_t instruction_end;

        switch(*reinterpret_cast<std::uint8_t *>(instruction)) {
            // call, jmp
            case 0xE8:
            case 0xE9: {
                instruction_size = 0x5;
                instruction_end = reinterpret_cast<std::uint32_t>(instruction + instruction_size);

                this->data[offset + 0] = *reinterpret_cast<char *>(instruction);
                auto original_offset = *reinterpret_cast<std::uint32_t *>(instruction + 1);
                auto *call_offset = reinterpret_cast<std::uint32_t *>(&this->data[offset + 1]);
                *call_offset = original_offset + (instruction_end - (reinterpret_cast<std::uint32_t>(call_offset) + 4));

                // Update exit jump offset
                this->data[offset - 1] = instruction_size;

                offset += 5;
            }
            break;

            default: {
                message_box("Unable to make a hook: unsupported instruction.");
                std::terminate();
            }
            break;
        }

        // Write codecave exit
        this->write_exit(offset, instruction + instruction_size);

        // Write jump to the hook
        this->hook(address, this->data_size);

        // Update hook data size
        this->data_size = offset;
    }

    Codecave::Codecave() noexcept {
        DWORD old_protection;

        // enable code execution on the hook memory
        VirtualProtect(this->data, sizeof(this->data), PAGE_EXECUTE_READWRITE, &old_protection);

        // Set NOPs
        for(std::size_t i = 0; i < sizeof(this->data); i++) {
            this->data[i] = 0x90;
        }

        // set the skip flag
        this->skip_og_code = false;

        this->data_size = 0;
    }
}
// SPDX-License-Identifier: GPL-3.0-only

#include <memory>
#include <windows.h>
#include "../messaging/message_box.hpp"
#include "memory.hpp"
#include "codecave.hpp"

namespace Harmony {
    void Codecave::set_access_protection(bool setting) noexcept {
        if(setting) {
            // enable code execution
            VirtualProtect(this->cave, this->size, PAGE_EXECUTE_READWRITE, &this->original_page_protection);
        }
        else {
            VirtualProtect(this->cave, this->size, this->original_page_protection, NULL);
        }
    }

    std::uint32_t Codecave::calculate_jmp_offset(const void *jmp, const void *destination) noexcept {
        auto offset = reinterpret_cast<std::uint32_t>(destination) - (reinterpret_cast<std::uint32_t>(jmp) + 5);
        return offset;
    }

    void Codecave::write_function_call(const void *function, bool pushad) noexcept {
        if(pushad) {
            this->insert(0x9C); // pushfd
            this->insert(0x60); // pushad
        }

        this->insert(0xE8); // call
        auto fn_offset = this->calculate_jmp_offset(reinterpret_cast<void *>(&this->cave[this->size - 1]), function);
        this->insert_address(fn_offset);

        if(pushad) {
            this->insert(0x61); // popad
            this->insert(0x9D); // popfd
        }
    }

    void Codecave::copy_instruction(const void *address, std::uint8_t &instruction_size) noexcept {
        auto *instruction_bytes = reinterpret_cast<const std::uint8_t *>(address);
        switch(instruction_bytes[0]) {
            // call rel32
            case 0xE8: 
            // jmp rel32
            case 0xE9: {
                this->insert(instruction_bytes[0]); // call or jmp

                // offset
                auto original_offset = *reinterpret_cast<const std::uint32_t *>(&instruction_bytes[1]);
                auto offset = original_offset + this->calculate_jmp_offset(&this->cave[this->size - 1], &instruction_bytes[5]);
                this->insert_address(offset);
                
                instruction_size = 5;
                
                break;
            }

            // mov r/m8, imm8
            case 0xC6: {
                this->insert(0xC6); // opcode

                // [esp + disp8], imm8
                if(instruction_bytes[1] == 0x44 && instruction_bytes[2] == 0x24) {
                    this->insert(&instruction_bytes[1], 4);
                    instruction_size = 5;
                }
                else {
                    message_box("Unsupported mov instruction.");
                    std::terminate();
                }
                break;
            }

            default: {
                message_box("Unable to build cave: unsupported instruction.");
                std::terminate();
            }
        }

        // Backup original code
        auto &original_code = this->original_instruction;
        for(std::size_t i = 0; i < instruction_size; i++) {
            original_code.push_back(static_cast<std::byte>(instruction_bytes[i]));
        }
    }

    void Codecave::write_cave_return() noexcept {
        // jmp
        this->insert(0xE9);

        // offset
        auto offset = this->calculate_jmp_offset(&this->cave[this->size - 1], this->instruction + this->original_instruction.size());
        this->insert_address(offset);
    }

    void Codecave::execute_original_code(bool setting) noexcept {
        this->execute_original_code_flag = setting;
    }

    void Codecave::write_basic_codecave(void *address, const void *function, bool pushad) noexcept {
        if(this->hooked) {
            return;
        }

        this->instruction = reinterpret_cast<std::byte *>(address);

        this->write_function_call(function, pushad);

        // cmp dword ptr [flag], 0
        this->insert(0x83);
        this->insert(0x3D);
        auto flag_address = reinterpret_cast<std::uint32_t>(&this->execute_original_code_flag);
        this->insert_address(flag_address);
        this->insert(0); // false

        // je instruction_size
        this->insert(0x74);
        this->insert(0x0);

        // Copy instruction code into cave
        std::uint8_t &instruction_size = *reinterpret_cast<std::uint8_t *>(&this->cave[this->size - 1]);
        this->copy_instruction(address, instruction_size);

        // Write codecave return
        this->write_cave_return();
    }

    void Codecave::hook() noexcept {
        if(this->hooked && this->size > 0) {
            return;
        }
        this->hooked = true;
        set_access_protection();
        overwrite(this->instruction, static_cast<std::byte>(0xE9));
        overwrite(this->instruction + 1, this->calculate_jmp_offset(this->instruction, this->cave));
    }

    void Codecave::release() noexcept {
        if(!this->hooked) {
            return;
        }
        overwrite(this->instruction, this->original_instruction.data(), this->original_instruction.size());
        set_access_protection(false);
        this->hooked = false;
    }

    Codecave::Codecave() noexcept {
        this->cave = reinterpret_cast<std::byte *>(malloc(32));
    }

    Codecave::~Codecave() noexcept {
        this->release();
        free(this->cave);
    }
}
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
    
    std::byte *Codecave::follow_jump(std::byte *jmp) noexcept {
        if(jmp[0] != static_cast<std::byte>(0xE8) && jmp[0] != static_cast<std::byte>(0xE9)) {
            message_box("Unable to follow jump. WHAT THE H*CK IS THIS!");
        }
        auto jmp_offset = *reinterpret_cast<std::uint32_t *>(jmp + 1);
        auto jmp_end = reinterpret_cast<std::uint32_t>(jmp + 5);
        auto *destination = reinterpret_cast<std::byte *>(jmp_offset + jmp_end);
        return destination;
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
        instruction_size = 0;
        auto *instruction = reinterpret_cast<const std::uint8_t *>(address);
        while(instruction_size < 5) {
            instruction += instruction_size;
            switch(instruction[0]) {
                // call rel32
                case 0xE8: 
                // jmp rel32
                case 0xE9: {
                    this->insert(instruction[0]); // call or jmp

                    // offset
                    auto original_offset = *reinterpret_cast<const std::uint32_t *>(&instruction[1]);
                    auto offset = original_offset + this->calculate_jmp_offset(&this->cave[this->size - 1], &instruction[5]);
                    this->insert_address(offset);
                    
                    instruction_size += 5;
                    break;
                }

                // mov r/m8, imm8
                case 0xC6: {
                    this->insert(0xC6);

                    // mov [esp + disp8], imm8
                    if(instruction[1] == 0x44 && instruction[2] == 0x24) {
                        this->insert(&instruction[1], 4);
                        instruction_size += 5;
                    }
                    else {
                        message_box("Unsupported mov instruction.");
                        std::terminate();
                    }
                    break;
                }

                // far call
                case 0xFF: {
                    this->insert(0xFF);

                    // call dword ptr [edx + disp32]
                    if(instruction[1] == 0x92) {
                        this->insert(0x92);
                        this->insert(&instruction[2], 4);

                        instruction_size += 6;
                        break;
                    }
                    // call dword ptr [edx + disp8]
                    else if(instruction[1] == 0x52) {
                        this->insert(0x52);
                        this->insert(instruction[2]);

                        instruction_size += 3;
                        break;
                    }
                    else {
                        message_box("Unsupported call instruction.");
                        std::terminate();
                    }
                }

                // test
                case 0x85: {
                    // test eax, eax (?)
                    if(instruction[1] == 0xC0) {
                        this->insert(0xC0);
                        instruction_size += 2;
                    }
                    else {
                        message_box("Unsupported test instruction.");
                        std::terminate();
                    }
                    break;
                }

                // nop
                case 0x90: {
                    this->insert(0x90);
                    instruction_size = 1;
                    break;
                }

                default: {
                    message_box("Unable to build cave: unsupported instruction. \nOpcode: 0x%.2X at 0x%.8X", instruction[0], instruction);
                    std::terminate();
                }
            }

            // Backup original instruction
            auto *instruction_bytes = reinterpret_cast<const std::byte *>(instruction);
            this->original_instruction.insert(this->original_instruction.end(), instruction_bytes, instruction_bytes + instruction_size);
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

    void Codecave::write_function_call(void *address, const void *function_before, const void *function_after, bool pushad) {
        if(this->hooked) {
            return;
        }

        this->instruction = reinterpret_cast<std::byte *>(address);

        // Write function call 1
        this->write_function_call(function_before, pushad);

        // Copy instruction code into cave
        std::uint8_t instruction_size = 0;
        this->copy_instruction(address, instruction_size);

        // Write function call 2
        this->write_function_call(function_after, pushad);

        // Write codecave return
        this->write_cave_return();
    }

    void Codecave::hack_chimera_override(void *address, const void *function, const void **cave_return) noexcept {
        if(this->hooked) {
            return;
        }

        this->instruction = reinterpret_cast<std::byte *>(address);

        // Backup original jmp instruction
        std::vector<std::byte> original_override_jmp;
        for(std::size_t i = 0; i < 5; i++) {
            original_override_jmp.push_back(this->instruction[i]);
        }
    
        this->insert(0xE9);
        this->insert_address(this->calculate_jmp_offset(&this->cave[this->size - 1], function));

        // Set override return
        *cave_return = &this->cave[this->size];

        // Get code from Chimera cave
        auto *chimera_cave = reinterpret_cast<std::byte *>(this->follow_jump(address));
        std::uint8_t intruction_size = 0;
        this->copy_instruction(reinterpret_cast<void *>(chimera_cave), intruction_size);
        this->copy_instruction(reinterpret_cast<void *>(chimera_cave + 5), intruction_size);

        // Save Chimera override jump
        this->original_instruction = original_override_jmp;
        
        // Return
        this->write_cave_return();
    }

    void Codecave::hook() noexcept {
        if(this->hooked && this->size > 0) {
            return;
        }
        this->hooked = true;
        set_access_protection();

        // Kill original code
        for(std::size_t i = 0; i < this->original_instruction.size(); i++) {
            overwrite(this->instruction + i, static_cast<std::byte>(0x90));
        }

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
;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.data
console_output_addr: .long 0

.text
console_output_sig: .string "console_out"

;# Make sure anything with a % sign doesn't get wrecked
console_output_format: .string "%s"

.globl _console_output_asm
_console_output_asm:
    pushfd
    pushad

    ;# Check if we know the address
    cmp dword ptr console_output_addr, 0
    jnz do_console_output

    ;# Get the address if not set
    lea eax, byte ptr console_output_sig
    push eax
    call _get_address_for_signature
    mov console_output_addr, eax
    pop eax

    do_console_output:
    ;# Set the variables
    ;# eax = pointer to color
    mov eax, [esp+0x28]
    lea edx, console_output_format
    push [esp+0x2C] ;# message
    push edx
    call dword ptr console_output_addr
    add esp, 8

    ;# Clean up
    popad
    popfd
    ret

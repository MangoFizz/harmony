;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.data
execute_console_command_function_address: .long 0

.text
execute_console_command_function_sig: .string "console_command_function"

.globl _call_console_command_events_asm
_call_console_command_events_asm:
    pushfd
    pushad

    ;# Look for function address
    cmp byte ptr execute_console_command_function_address, 0
    jnz found_signature
    lea eax, byte ptr execute_console_command_function_sig
    push eax
    call _get_address_for_signature
    add esp, 4
    mov execute_console_command_function_address, eax
    found_signature:
    
    mov eax, [esp + 0x28]
    push eax
    call _call_console_command_events
    add esp, 4

    test eax, eax
    jz copy_command_to_history

    popad
    popfd
    ret

    copy_command_to_history:
    popad
    popfd
    jmp dword ptr execute_console_command_function_address

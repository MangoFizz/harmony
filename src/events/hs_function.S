;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.data

get_hs_function_parameters_fn_address: .long 0
pop_hs_function_fn_address: .long 0
hs_functions_table_address: .long 0
hs_function_parameters_address: .long 0
got_function_parameters_flag: .byte 0

.text

get_hs_function_parameters_fn_sig: .string "hs_get_function_parameters_function"
pop_hs_function_fn_sig: .string "hs_pop_script_function"
hs_functions_table_sig: .string "hs_funtions_table"


get_hs_function_event_signatures:
    pushad
    pushfd

    ;# Look for signatures
    cmp dword ptr get_hs_function_parameters_fn_address, 0
    jne addresses_found

    ;# Script function parameters getter sig
    lea eax, get_hs_function_parameters_fn_sig
    push eax
    call _get_address_for_signature
    mov get_hs_function_parameters_fn_address, eax
    add esp, 4

    ;# Script functions table sig
    lea eax, hs_functions_table_sig
    push eax
    call _get_address_for_signature
    mov eax, [eax] ;# read table address
    mov hs_functions_table_address, eax
    add esp, 4

    ;# Pop script function address
    lea eax, pop_hs_function_fn_sig
    push eax
    call _get_address_for_signature
    mov pop_hs_function_fn_address, eax
    add esp, 4

    addresses_found:
    popfd
    popad
    ret


;# A script function-like that does nothing
fake_script_function:
    ;# Function data struct
    mov ebx, hs_functions_table_address
    movsx eax, word ptr [esp + 0x24]
    mov eax, dword ptr [eax * 4 + ebx]

    ;# Weird values
    push esi
    mov ecx, dword ptr [esp + 0x34]
    push ecx

    ;# Parameters types
    lea edx, dword ptr [eax + 0x1C]
    push edx

    ;# Parameters count
    movsx eax, word ptr [eax + 0x1A]
    push eax

    ;# More weird values
    mov esi, dword ptr [esp + 0x3C]
    push esi

    ;# Call the function override to make sure we only call the original function once
    call _get_hs_function_parameters_fn_override
    add esp, 16

    ;# Check if parameters address is valid
    test eax, eax
    je fake_script_function_return

    ;# Pop script function
    mov ecx, esi
    xor eax, eax
    pop esi
    jmp dword ptr pop_hs_function_fn_address

    fake_script_function_return:
    pop esi
    ret


;# Script function hook
.globl _hs_function_hook_fn
_hs_function_hook_fn:
    pushad
    pushfd

    ;# Get addresses
    call get_hs_function_event_signatures

    ;# Function data struct
    mov ebx, hs_functions_table_address
    movsx eax, word ptr [esp + 0x24]
    mov eax, dword ptr [eax * 4 + ebx]
    push eax ;# save this for later

    ;# Check if there are parameters to get
    cmp word ptr [eax + 0x1A], 0
    je hs_function_hook_fn_no_parameters

    ;# Weird values
    push esi
    mov ecx, dword ptr [esp + 0x34]
    push ecx

    ;# Parameters types
    lea edx, dword ptr [eax + 0x1C]
    push edx

    ;# Parameters count
    movsx eax, word ptr [eax + 0x1A]
    push eax

    ;# More weird values
    mov esi, dword ptr [esp + 0x3C]
    push esi

    ;# Get those parameters
    call dword ptr get_hs_function_parameters_fn_address
    add esp, 20

    ;# Save parameters address
    mov hs_function_parameters_address, eax
    mov byte ptr got_function_parameters_flag, 1
    mov edx, eax
    
    ;# Check if return value is null
    test edx, edx
    je hs_function_hook_fn_invalid_parameters_address
    jmp hs_function_hook_fn_call_events

    hs_function_hook_fn_no_parameters:
    ;# We have no parameters
    mov byte ptr got_function_parameters_flag, 0
    mov edx, 0

    ;# Check for duplicated script function call
    movsx eax, byte ptr [esp + 0x30]
    cmp al, 1
    jne hs_function_hook_fn_invalid_parameters_address
    
    hs_function_hook_fn_call_events:
    ;# Restore eax
    pop eax

    ;# Get script name from stack
    mov ebx, dword ptr [esp + 0x40]

    ;# Call our events
    push edx
    push eax
    push ebx
    call _on_hs_function
    add esp, 12
    cmp al, 0
    je hs_function_hook_fn_block    
    jmp hs_function_hook_fn_done

    hs_function_hook_fn_invalid_parameters_address:
    pop eax

    hs_function_hook_fn_done:
    popfd
    popad

    call dword ptr [edx + 0xC]
    add esp, 12
    jmp hs_function_hook_fn_jump_back

    hs_function_hook_fn_block:
    popfd
    popad

    call fake_script_function
    add esp, 12

    hs_function_hook_fn_jump_back:
    jmp dword ptr _hs_function_hook_fn_return


;# Script function parameters getter override
.globl _get_hs_function_parameters_fn_override
_get_hs_function_parameters_fn_override:
    ;# Check if we already got parameters from this script function
    cmp byte ptr got_function_parameters_flag, 1
    je block_script_function_parameters_getter

    ;# It's ok
    jmp dword ptr _get_hs_function_parameters_fn_return

    ;# If so, don't call the function again, just return the parameters address
    block_script_function_parameters_getter:
    mov eax, hs_function_parameters_address
    mov byte ptr got_function_parameters_flag, 0
    ret

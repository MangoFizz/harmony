;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.data

get_script_function_parameters_address: .long 0
script_functions_table: .long 0
got_parameters: .byte 0
parameters_address: .long 0

.text

get_script_function_parameters_sig: .string "hs_get_function_parameters_function"
script_functions_table_sig: .string "hs_funtions_table"

.globl _script_function
_script_function:
    pushad
    pushfd

    ;# Look for signatures
    cmp dword ptr get_script_function_parameters_address, 0
    jne addresses_found
    pushad

    ;# Script function parameters getter sig
    lea eax, get_script_function_parameters_sig
    push eax
    call _get_address_for_signature
    mov get_script_function_parameters_address, eax

    ;# Script functions table sig
    lea eax, script_functions_table_sig
    push eax
    call _get_address_for_signature
    mov eax, [eax] ;# read table address
    mov script_functions_table, eax

    add esp, 8
    popad
    addresses_found:

    ;# Function data struct
    mov ebx, script_functions_table
    movsx eax, word ptr [esp + 0x28]
    mov eax, dword ptr [eax * 4 + ebx]
    push eax ;# save this for later

    ;# Check if there are parameters to get
    cmp word ptr [eax + 0x1A], 0
    je no_parameters

    ;# Weird values
    push esi
    mov ecx, dword ptr [esp + 0x38]
    push ecx

    ;# Parameters types
    lea edx, dword ptr [eax + 0x1C]
    push edx

    ;# Parameters count
    movsx eax, word ptr [eax + 0x1A]
    push eax

    ;# More weird values
    mov esi, dword ptr [esp + 0x40]
    push esi

    ;# Get those parameters
    call dword ptr get_script_function_parameters_address
    add esp, 20

    ;# Save parameters address
    mov parameters_address, eax
    mov byte ptr got_parameters, 1
    mov edx, eax
    
    ;# Check if return value is null
    test edx, edx
    je invalid_parameters_address
    jmp call_events

    no_parameters:
    ;# We have no parameters
    mov byte ptr got_parameters, 0
    mov edx, 0
    
    call_events:
    ;# Restore eax
    pop eax

    ;# Get script name from stack
    mov ebx, dword ptr [esp + 0x44]

    ;# Call our events
    push edx
    push eax
    push ebx
    call _on_hs_function
    add esp, 12
    jmp done

    invalid_parameters_address:
    pop eax

    done:
    popfd
    popad
    ret

.globl _get_script_function_parameters_override
_get_script_function_parameters_override:
    ;# Check if we already got parameters from this script function
    cmp byte ptr got_parameters, 1
    je block_script_function_parameters_getter

    ;# It's ok
    jmp dword ptr _get_script_function_parameters_fn

    ;# If so, don't call the function again, just return the parameters address
    block_script_function_parameters_getter:
    mov eax, parameters_address
    mov byte ptr got_parameters, 0
    ret

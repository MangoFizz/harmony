;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.data
return_address: .long 0

.text

.globl _client_player_update_history_entry_write_fn_override
_client_player_update_history_entry_write_fn_override:
    ;# Save log level
    mov dword ptr _client_player_update_history_entry_level, eax

    ;# Save and remove return address
    mov eax, [esp]
    mov dword ptr return_address, eax
    add esp, 4

    ;# Format string and store it in our buffer
    lea eax, _client_player_update_history_entry_buffer
    push eax
    call _sprintf
    add esp, 4

    ;# Write it!
    call _write_client_player_update_log_entry

    ;# Restore everythig and call the original function
    mov eax, dword ptr [_client_player_update_history_entry_level]
    push dword ptr [return_address]
    jmp dword ptr _client_player_update_history_entry_write_fn

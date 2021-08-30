;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _menu_sound
_menu_sound:
    pushad
    pushfd

    ;# Catch weird calls
    cmp eax, 3
    ja return
    cmp eax, 0
    jl return

    ;# Look for a valid tag ID
    cmp esi, 0xFFFF
    jle return

    ;# Get pressed button tag id
    mov ebx, [esi]

    call_events:
    push eax ;# sound index
    push ebx
    call _on_menu_sound
    add esp, 8

    ;# Check allow flag
    cmp eax, 1
    je return

    ;# Block it !!
    popfd
    cmp eax, -1
    popad
    ret

    return:
    popfd
    popad
    ret

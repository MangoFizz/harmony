;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _menu_accept
_menu_accept:
    pushad
    pushfd

    ;# Check enter key
    cmp al, 0
    jne continue

    ;# Check enter event
    cmp byte ptr [esi + 4], 0
    jne continue

    ;# Run events
    push dword ptr [esp + 0x48] ;# UI widget tag ID
    call _on_menu_accept
    add esp, 4

    ;# Set allow flag
    popfd
    cmp al, 1
    popad
    ret
    
    ;# Get out, don't touch anything
    continue:
    popfd
    popad
    ret

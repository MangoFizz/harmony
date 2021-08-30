;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _menu_back_event
_menu_back_event:
    pushad
    pushfd

    ;# Check enter key
    mov eax, [eax]

    ;# Run events
    push eax
    call _on_menu_back
    add esp, 4

    popfd
    popad
    ret

;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _call_widget_list_tab_events_asm
_call_widget_list_tab_events_asm:
    pushad
    pushfd

    ;# Get pressed key
    mov ecx, [esp + 0x2C]
    xor eax, eax
    mov al, byte ptr [ecx + 4]

    ;# Get list widget
    mov edx, ebx

    ;# Run events
    push edx
    push eax
    call _call_widget_list_tab_events
    add esp, 8

    popfd
    popad
    ret

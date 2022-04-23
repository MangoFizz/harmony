;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _create_widget_return_hook_asm
_create_widget_return_hook_asm:
    pushad
    pushfd

    ;# Widgets tree upstream node
    mov edx, [esp + 0x34]

    ;# Check if we are on the root widget
    test edx, edx
    jnz do_not_call_events

    push eax ;# created widget
    call _call_widget_open_events
    add esp, 4

    do_not_call_events:
    popfd
    popad
    ret

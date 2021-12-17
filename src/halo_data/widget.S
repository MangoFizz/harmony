;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.data
menu_open_widget_addr: .long 0
menu_open_widget_push_history_addr: .long 0

.text
menu_open_widget_sig: .string "menu_open_widget_function"
menu_open_widget_push_history_sig: .string "menu_open_widget_push_history_function"

.globl _open_widget_asm
_open_widget_asm:
    pushfd
    pushad

    cmp dword ptr menu_open_widget_addr, 0
    jnz do_open_widget
    lea eax, byte ptr menu_open_widget_sig
    push eax
    call _get_address_for_signature
    mov menu_open_widget_addr, eax
    pop eax

    do_open_widget:
    mov eax, [esp + 0x28] ;# Tag ID of the widget
    push -1
    push -1
    push -1
    push 0
    push 0
    push eax
    push 0
    call dword ptr menu_open_widget_addr
    add esp, 28

    popad
    popfd

    ret

.globl _open_widget_push_history_asm
_open_widget_push_history_asm:
    pushfd
    pushad

    cmp dword ptr menu_open_widget_push_history_addr, 0
    jnz open
    lea eax, byte ptr menu_open_widget_push_history_sig
    push eax
    call _get_address_for_signature
    mov menu_open_widget_push_history_addr, eax
    pop eax

    open:
    mov eax, [esp + 0x28] ;# Current widget root instance
    mov edx, [esp + 0x2C] ;# New widget tag ID
    push edx
    push eax
    call dword ptr menu_open_widget_push_history_addr
    add esp, 8

    popad
    popfd

    ret

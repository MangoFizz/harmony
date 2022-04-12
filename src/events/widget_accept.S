;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _call_widget_accept_events_asm
_call_widget_accept_events_asm:
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
    call _call_widget_accept_events
    add esp, 4

    ;# Set allow flag
    ;# TODO: Make this less hacky
    popfd
    cmp al, 1
    popad
    ret
    
    ;# Get out, don't touch anything
    continue:
    popfd
    popad
    ret

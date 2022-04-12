;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _widescreen_element_reposition_menu
_widescreen_element_reposition_menu:
    push eax
    mov eax, [esp + 4]
    pushfd
    pushad
    push eax
    call _reposition_menu_element
    add esp, 4
    popad
    popfd
    pop eax
    jmp dword ptr _widescreen_element_position_menu_fn

.globl _widescreen_element_reposition_menu_text
_widescreen_element_reposition_menu_text:
    pushfd
    pushad
    push ecx
    call _reposition_menu_text_element
    add esp, 4
    popad
    popfd
    jmp dword ptr _widescreen_element_position_menu_text_fn

.globl _widescreen_element_reposition_menu_text_2
_widescreen_element_reposition_menu_text_2:
    pushfd
    pushad
    push ecx
    call _reposition_menu_text_element
    add esp, 4
    popad
    popfd
    jmp dword ptr _widescreen_element_position_menu_text_2_fn

.globl _widescreen_input_text
_widescreen_input_text:
    pushfd
    pushad
    mov dword ptr _widescreen_text_input_element, ecx
    call _reposition_menu_text_input
    popad
    popfd
    ret

.globl _widescreen_input_text_undo
_widescreen_input_text_undo:
    pushfd
    pushad
    call _unreposition_menu_text_input
    popad
    popfd
    ret

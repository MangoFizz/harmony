;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

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

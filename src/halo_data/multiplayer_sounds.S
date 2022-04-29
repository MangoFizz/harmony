;# SPDX-License-Identifier: GPL-3.0-only

.intel_syntax noprefix

.text

.globl _multiplayer_announcer_hook_asm
_multiplayer_announcer_hook_asm:
    pushad
    pushfd
   
   ;# hacks from HAC2
    mov eax, dword ptr [esp + 0xB8]
    cmp eax, 7
    jb block_it
    cmp eax, 18
    ja block_it
    cmp eax, 8
    je block_it
    cmp eax, 13
    je block_it

    jmp continue

    block_it:
    cmp byte ptr _skip_multiplayer_announcer, 0
    je continue
    popfd
    popad
    jmp dword ptr _multiplayer_announcer_fn_return

    continue:
    popfd
    popad
    jmp dword ptr _multiplayer_announcer_hook_return

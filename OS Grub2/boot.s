;/* ************************************************************************** */
;/*                                                                            */
;/*                                                        :::      ::::::::   */
;/*   boot.s                                             :+:      :+:    :+:   */
;/*                                                    +:+ +:+         +:+     */
;/*   By: B.N. Berrevoets <bert@berrevoets.net>      +#+  +:+       +#+        */
;/*                                                +#+#+#+#+#+   +#+           */
;/*   Created: 2020/10/17 00:33:14 by B.N. Berrev       #+#    #+#             */
;/*   Updated: 2020/10/17 00:33:15 by B.N. Berrev      ###   ########.fr       */
;/*                                                                            */
;/* ************************************************************************** */

global start
global multiboot_header
extern kmain
extern printf

STACK_SIZE equ 0x1000

section .multiboot
align 4
header_start:
    dd 0xe85250d6                                      ; magic number
    dd 0                                               ; protected mode code
    dd header_end - header_start                       ; header length
    dd -(0xe85250d6 + 0 + (header_end - header_start)) ; checksum

                                                       ; required end tag
    dw 0                                               ; type
    dw 0                                               ; flags
    dd 8                                               ; size
header_end:

section .bss
align 4
kernel_stack:
    resb STACK_SIZE

section .text
align 4
start:
    mov esp, kernel_stack + STACK_SIZE

    push 0
    popf

    push ebx
    push eax

    call kmain

    push halt_message   ; message
    push 2              ; label (INFO_PRINT)
    push 2              ; stream (BOTH_STREAM)
    call printf

loop:
    hlt
    jmp loop

halt_message:
    db "Halted.", 10, 0
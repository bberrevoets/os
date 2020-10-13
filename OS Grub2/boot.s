global start
global multiboot_header
extern kmain
; extern printf

STACK_SIZE equ 0x4000

section .multiboot
header_start:
    dd 0xe85250d6                ; magic number
    dd 0                         ; protected mode code
    dd header_end - header_start ; header length

                                 ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; required end tag
    dw 0                         ; type
    dw 0                         ; flags
    dd 8                         ; size
header_end:

section .bss
align 8
kernel_stack:
    resb STACK_SIZE

section .text
align 8
start:
    mov esp, kernel_stack + STACK_SIZE

    push 0
    popf

    push ebx
    push eax

    call kmain

loop:
    hlt
    jmp loop
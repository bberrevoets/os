[GLOBAL loader]                                   ; the entry symbol for ELF
[GLOBAL mboot]
[EXTERN kmain]

MAGIC_NUMBER        equ 0x1BADB002              ; define the magic number constant
ALIGN_MODULES       equ 0x00000001              ; tell GRUB to align modules
; calculate the checksum (all options + checksum should equal 0)
CHECKSUM            equ -(MAGIC_NUMBER + ALIGN_MODULES)

KERNEL_STACK_SIZE   equ 4096                    ; size of stack in bytes

section .multiboot                              ; start of the multiboot section
align 4                                         ; the code must be 4 byte align
mboot:
    dd MAGIC_NUMBER                             ; write the magic number
    dd ALIGN_MODULES                            ; write the align modules instruction
    dd CHECKSUM                                 ; write the checksum

section .bss                                    ; start of bss section
align 16                                        ; the code must be 16 byte aligned
kernel_stack:                                   ; label points to beginning of memory
    resb    KERNEL_STACK_SIZE                   ; reserve stak for kernel


section .text
align 4
loader:                                         ; the loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the
                                                ; stack (end of memory area)
    
    cli
    
    push ebx ; load multiboot info.
    call kmain

.loop:
    jmp .loop                                   ; loop forever
.end:

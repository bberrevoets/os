[GLOBAL loader]                                      ; the entry symbol for ELF
[GLOBAL multiboot_header]
[EXTERN kmain]

; How many bytes from the start of the file we search for the header.
MULTIBOOT_SEARCH equ 8192
MULTIBOOT_HEADER_ALIGN equ 4

; The magic field should contain this.
MULTIBOOT_HEADER_MAGIC equ 0x1BADB002

; This should be in eax
MULTIBOOT_BOOTLOADER_MAGIC equ 0x2BADB002

; Alignment of mutiboot modules
MULTIBOOT_MOD_ALIGN equ 0x00001000

; Alignment of the multiboot info structure
MULTIBOOT_INFO_ALIGN equ 0x00000004

; Flags set in the 'Flags' member of the multiboot header

; Align all boot modules on i386 page (4KB) boundaries
MULTIBOOT_PAGE_ALIGN equ 0x00000001

; Must pass memory information to OS.
MULTIBOOT_MEMORY_INFO equ 0x00000002

; Must pass video information to OS.
MULTIBOOT_VIDEO_MODE equ 0x00000004

; This flag indicates the use of the address fields in the header.
MULTIBOOT_AOUT_KLUDGE equ 0x00010000

; Flags to be set in the ’flags’ member of the multiboot info structure.

; is there basic lower/upper memory information?
MULTIBOOT_INFO_MEMORY equ 0x00000001
; is there a boot device set?
MULTIBOOT_INFO_BOOTDEV equ 0x00000002
; is the command-line defined?
MULTIBOOT_INFO_CMDLINE equ 0x00000004
; are there modules to do something with?
MULTIBOOT_INFO_MODS equ 0x00000008

; These next two are mutually exclusive

; is there a symbol table loaded?
MULTIBOOT_INFO_AOUT_SYMS equ 0x00000010
; is there an ELF section header table?
MULTIBOOT_INFO_ELF_SHDR equ 0X00000020

; is there a full memory map?
MULTIBOOT_INFO_MEM_MAP equ 0x00000040

; Is there drive info?
MULTIBOOT_INFO_DRIVE_INFO  equ 0x00000080

; Is there a config table?
MULTIBOOT_INFO_CONFIG_TABLE equ 0x00000100

; Is there a boot loader name?
MULTIBOOT_INFO_BOOT_LOADER_NAME equ 0x00000200

; Is there a APM table?
MULTIBOOT_INFO_APM_TABLE equ 0x00000400

; Is there video information?
MULTIBOOT_INFO_VBE_INFO equ 0x00000800
MULTIBOOT_INFO_FRAMEBUFFER_INFO equ 0x00001000

; Start
STACK_SIZE equ 0x4000
MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_VIDEO_MODE
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

section .multiboot                                   ; Start of multiboot section
align 4
multiboot_header:
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    dd 0    ; header_addr   if flags[16] is set
    dd 0    ; load_addr     if flags[16] is set
    dd 0    ; load_end_addr if flags[16] is set
    dd 0    ; bss_end_addr  if flags[16] is set
    dd 0    ; entry_addr    if flags[16] is set
    dd 0    ; mode_type     if flags[2] is set
    dd 640  ; width         if flags[2] is set
    dd 480  ; height        if flags[2] is set
    dd 0    ; depth         if flags[2] is set

section .bss
align 16
kernel_stack:
    resb STACK_SIZE

section .text
align 4
loader:
    mov esp, kernel_stack + STACK_SIZE               ; point esp to the start of the
                                                     ; stack (end of memory area)

    ; Reset EFLAGS
    push 0
    popf

    ; push the pointer to the multiboot information structure
    push ebx
    ; push the magic value
    push eax

    ; Now enter the C main function
    call kmain

    ; stop everything
    loop:
        hlt
        jmp loop
    
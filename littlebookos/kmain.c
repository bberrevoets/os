#include "minilib.h"
#include "descriptor_tables.h"
#include "multiboot.h"
#include "timer.h"
#include "keyboard.h"

void kmain(struct multiboot *mboot_ptr)
{
    // Initialize all the ISRs and sementation
    init_descriptor_tables();

    fb_init();
    sw_init();

    asm volatile("int $0x3");
    asm volatile("int $0x4");

    asm volatile("sti");
    init_timer(50);
    init_keyboard();
    
    if (mboot_ptr->mods_count > 0)
        printf(BOTH_STREAM, INFO_PRINT, "%d modules geladen.\n", mboot_ptr->mods_count);

    printf(SCREEN_STREAM, NONE_PRINT, "Hello, world!\n");

    for (;;);
}

#include "minilib.h"
#include "descriptor_tables.h"
#include "multiboot.h"

void kmain(struct multiboot *mboot_ptr)
{
    // Initialize all the ISRs and sementation
    init_descriptor_tables();

    fb_init();
    sw_init();

    if (mboot_ptr->mods_count > 0)
        printf(BOTH_STREAM, INFO_PRINT, "%d modules geladen.\n", mboot_ptr->mods_count);

    printf(BOTH_STREAM, NONE_PRINT, "Hello, world!\n");
    printf(BOTH_STREAM, NONE_PRINT, "Hello, world!\n");
    printf(BOTH_STREAM, NONE_PRINT, "Hello, world!\n");
    printf(BOTH_STREAM, NONE_PRINT, "Hello, world!\n");

    for (;;)
        ;
}

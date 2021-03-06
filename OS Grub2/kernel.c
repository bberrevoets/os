/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: B.N. Berrevoets <bert@berrevoets.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:33:53 by B.N. Berrev       #+#    #+#             */
/*   Updated: 2020/10/17 00:33:54 by B.N. Berrev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multiboot2.h"
#include "minilib.h"
#include "common.h"

void kmain(unsigned long magic, unsigned long addr)
{
    fb_init();
    sw_init();

    // Am i booted by a Multiboot compliant boot loader?
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        printf(SCREEN_STREAM, ERROR_PRINT, "Invalid magic number: 0x%x\n", (unsigned)magic);
        return;
    }
    else
    {
        printf(BOTH_STREAM, NONE_PRINT, "Booted by compliant loader!\n");
    }

    if (addr & 7)
    {
        printf(SCREEN_STREAM, ERROR_PRINT, "Unaligned mbi: 0x%x\n", addr);
        return;
    }
}
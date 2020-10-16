/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: B.N. Berrevoets <bert@berrevoets.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:34:15 by B.N. Berrev       #+#    #+#             */
/*   Updated: 2020/10/17 00:34:15 by B.N. Berrev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_MINILIB_H
#define INCLUDE_MINILIB_H

#include "framebuffer.h"
#include "serialwriter.h"

#define SERIAL_STREAM 0
#define SCREEN_STREAM 1
#define BOTH_STREAM 2

#define DEBUG_PRINT 0
#define ERROR_PRINT 1
#define INFO_PRINT 2
#define NONE_PRINT 3

void itoa(char *buf, int base, int d);
void *memcpy(void *dest, void *src, unsigned int size);
void *memset(void *dest, int ch, unsigned int size);
void printf(int stream, int label, const char *format, ...);

#endif
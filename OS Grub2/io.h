/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: B.N. Berrevoets <bert@berrevoets.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:33:48 by B.N. Berrev       #+#    #+#             */
/*   Updated: 2020/10/17 00:33:48 by B.N. Berrev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/** outb:
 *  Sends the given data to the given I/O port, Defined in io.s
 * 
 *  @param port The I/O port to send the data to
 *  @param data The data send to the I/O port
 */
void outb(unsigned short port, unsigned char data);

/** outw:
 *  Sends the given data to the given I/O port, Defined in io.s
 * 
 *  @param port The I/O port to send the data to
 *  @param data The data send to the I/O port
 */
void outw(unsigned short port, unsigned short data);

/** inb:
 *  Reads a byte from the I/O port, Defined in io.s
 * 
 *  @param port The I/O port to send the data to
 */
unsigned char inb(unsigned short port);

/** inw:
 *  Reads a word from the I/O port, Defined in io.s
 * 
 *  @param port The I/O port to send the data to
 */
unsigned short inw(unsigned short port);

#endif

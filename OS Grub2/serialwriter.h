/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialwriter.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: B.N. Berrevoets <bert@berrevoets.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:34:30 by B.N. Berrev       #+#    #+#             */
/*   Updated: 2020/10/17 00:34:31 by B.N. Berrev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_SERIALWRITER_H
#define INCLUDE_SERIALWRITER_H

#define PORT 0x3F8  // COM1

void sw_init(void);
void sw_put(char c);
void sw_write(char *c);
void sw_write_hex(unsigned int n);
void sw_write_dec(unsigned int n);

#endif

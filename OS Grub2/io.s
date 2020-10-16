;/* ************************************************************************** */
;/*                                                                            */
;/*                                                        :::      ::::::::   */
;/*   io.s                                               :+:      :+:    :+:   */
;/*                                                    +:+ +:+         +:+     */
;/*   By: B.N. Berrevoets <bert@berrevoets.net>      +#+  +:+       +#+        */
;/*                                                +#+#+#+#+#+   +#+           */
;/*   Created: 2020/10/17 00:33:14 by B.N. Berrev       #+#    #+#             */
;/*   Updated: 2020/10/17 00:33:15 by B.N. Berrev      ###   ########.fr       */
;/*                                                                            */
;/* ************************************************************************** */

global inb, outb, inw, outw 
section .text

inb: 
    xor eax, eax 
    mov dx, [esp + 4] 
    in al, dx 
    ret 
 
outb: 
    mov dx, [esp + 4] 
    mov al, [esp + 8] 
    out dx, al 
    ret 

inw: 
    xor eax, eax 
    mov dx, [esp + 4] 
    in ax, dx 
    ret 
 
outw: 
    mov dx, [esp + 4] 
    mov ax, [esp + 8] 
    out dx, ax  
    ret 
/*
 *  $Id: libnet_build_udp.c,v 1.1.1.1 2002/08/05 22:26:03 route Exp $
 *
 *  libnet
 *  libnet_build_udp.c - UDP packet assembler
 *
 *  Copyright (c) 1998 - 2002 Mike D. Schiffman <mike@infonexus.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#if (HAVE_CONFIG_H)
#include "../include/config.h"
#endif
#include "../include/libnet.h"

libnet_ptag_t
libnet_build_udp(u_short sp, u_short dp, u_short len, u_short sum,
            u_char *payload, u_long payload_s, libnet_t *l, libnet_ptag_t ptag)
{
    u_long n;
    u_short h;
    libnet_pblock_t *p;
    struct libnet_udp_hdr udp_hdr;

    if (l == NULL)
    { 
        return (-1);
    } 

    n = LIBNET_UDP_H + payload_s;               /* size of memory block */
    h = len;                                    /* header length (for cksum) */

    /*
     *  Find the existing protocol block if a ptag is specified, or create
     *  a new one.
     */
    p = libnet_pblock_probe(l, ptag, n, LIBNET_PBLOCK_UDP_H);
    if (p == NULL)
    {
        return (-1);
    }

    udp_hdr.uh_sport   = htons(sp);             /* source port */
    udp_hdr.uh_dport   = htons(dp);             /* destination port */
    udp_hdr.uh_ulen    = htons(h);              /* total length of UDP packet*/
    udp_hdr.uh_sum     = sum;                   /* checksum */

    n = libnet_pblock_append(l, p, (u_char *)&udp_hdr, LIBNET_UDP_H);
    if (n == -1)
    {
        goto bad;
    }
 
    if (payload && payload_s)
    {
        n = libnet_pblock_append(l, p, payload, payload_s);
        if (n == -1)
        {
            goto bad;
        }
    }
 
    if (sum == 0)
    {
        /*
         *  If checksum is zero, by default libnet will compute a checksum
         *  for the user.  The programmer can override this by calling
         *  libnet_toggle_checksum(l, ptag, 1);
         */
        libnet_pblock_setflags(p, LIBNET_PBLOCK_DO_CHECKSUM);
    }
    return (ptag ? ptag : libnet_pblock_update(l, p, h, LIBNET_PBLOCK_UDP_H));
bad:
    libnet_pblock_free(p);
    return (-1);
}

/* EOF */
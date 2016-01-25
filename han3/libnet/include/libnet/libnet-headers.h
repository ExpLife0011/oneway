/*
 *  $Id: libnet-headers.h,v 1.1.1.1 2002/08/05 22:26:04 route Exp $
 *
 *  libnet-headers.h - Network routine library headers header file
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

#ifndef __LIBNET_HEADERS_H
#define __LIBNET_HEADERS_H

#define LIBNET_802_1Q_H         0x12    /* 802.1Q header:       18 bytes */
#define LIBNET_802_2_H          0x03    /* 802.2 LLC header:     3 bytes */
#define LIBNET_802_2SNAP_H      0x08    /* 802.2 LLC/SNAP header:8 bytes */
#define LIBNET_802_3_H          0x0e    /* 802.3 header:        14 bytes */
#define LIBNET_ARP_H            0x08    /* ARP header w/o addrs: 8 bytes */
#define LIBNET_ARP_ETH_IP_H     0x1c    /* ARP w/ ETH and IP:   28 bytes */
#define LIBNET_CDP_H            0x08    /* CDP header base:      8 bytes */
#define LIBNET_DHCPV4_H         0xf0    /* DHCP v4 header:     240 bytes */
#define LIBNET_DNSV4_H          0x0c    /* DNS v4 header base:  12 bytes */
#define LIBNET_ETH_H            0x0e    /* Etherner header:     14 bytes */
#define LIBNET_ICMPV4_H         0x04    /* ICMP header base:     4 bytes */
#define LIBNET_ICMPV4_ECHO_H    0x08    /* ICMP_ECHO header:     8 bytes */
#define LIBNET_ICMPV4_MASK_H    0x0c    /* ICMP_MASK header:    12 bytes */
#define LIBNET_ICMPV4_UNREACH_H  0x08   /* ICMP_UNREACH header:  8 bytes */
#define LIBNET_ICMPV4_TIMXCEED_H 0x08   /* ICMP_TIMXCEED header: 8 bytes */
#define LIBNET_ICMPV4_REDIRECT_H 0x08   /* ICMP_REDIRECT header: 8 bytes */
#define LIBNET_ICMPV4_TS_H      0x14    /* ICMP_TIMESTAMP headr:20 bytes */
#define LIBNET_ICMPV6_H         0x08    /* ICMP6 header base:    8 bytes */
#define LIBNET_IGMP_H           0x08    /* IGMP header:          8 bytes */
#define LIBNET_IPV4_H           0x14    /* IPv4 header:         20 bytes */
#define LIBNET_IPV6_H           0x28    /* IPv6 header:         40 bytes */
#define LIBNET_IPSEC_ESP_HDR_H  0x0c    /* IPSEC ESP header:    12 bytes */
#define LIBNET_IPSEC_ESP_FTR_H  0x02    /* IPSEC ESP footer:     2 bytes */
#define LIBNET_IPSEC_AH_H       0x10    /* IPSEC AH header:     16 bytes */
#define LIBNET_ISL_H            0x1a    /* ISL header:          26 bytes */
#define LIBNET_OSPF_H           0x10    /* OSPF header:         16 bytes */
#define LIBNET_OSPF_HELLO_H     0x18    /* OSPF hello header:   24 bytes */
#define LIBNET_OSPF_DBD_H       0x08    /* OSPF DBD header:      8 bytes */
#define LIBNET_OSPF_LSR_H       0x0c    /* OSPF LSR header:     12 bytes */
#define LIBNET_OSPF_LSU_H       0x04    /* OSPF LSU header:      4 bytes */
#define LIBNET_OSPF_LSA_H       0x14    /* OSPF LSA header:     20 bytes */
#define LIBNET_OSPF_AUTH_H      0x08    /* OSPF AUTH header:     8 bytes */
#define LIBNET_OSPF_CKSUM       0x10    /* OSPF CKSUM header:   16 bytes */
#define LIBNET_OSPF_LS_RTR_H    0x10    /* OSPF LS RTR header:  16 bytes */
#define LIBNET_OSPF_LS_NET_H    0x08    /* OSPF LS NET header:   8 bytes */
#define LIBNET_OSPF_LS_SUM_H    0x0c    /* OSPF LS SUM header:  12 bytes */
#define LIBNET_OSPF_LS_AS_EXT_H 0x10    /* OSPF LS AS header:   16 bytes */
#define LIBNET_NTP_H            0x30    /* NTP header:          48 bytes */
#define LIBNET_RIP_H            0x18    /* RIP header base:     24 bytes */
#define LIBNET_STP_CONF_H       0x23    /* STP conf header:     35 bytes */
#define LIBNET_STP_TCN_H        0x04    /* STP tcn header:       4 bytes */
#define LIBNET_TCP_H            0x14    /* TCP header:          20 bytes */
#define LIBNET_UDP_H            0x08    /* UDP header:           8 bytes */
#define LIBNET_VRRP_H           0x08    /* VRRP header:          8 bytes */

/*
 *  IEEE 802.1Q VLAN header (ethervlan)
 *  Virtual Local Area Network
 *  static header size: 18 bytes
 */
struct libnet_802_1q_hdr
{
    u_char vlan_dhost[ETHER_ADDR_LEN];  /* destination ethernet address */
    u_char vlan_shost[ETHER_ADDR_LEN];  /* source ethernet address */
    u_short vlan_tpi;                   /* tag protocol ID */
    u_short vlan_priority_c_vid;        /* priority | VLAN ID */
#define LIBNET_802_1Q_PRIMASK   0x0007  /* priority mask */
#define LIBNET_802_1Q_CFIMASK   0x0001  /* CFI mask */
#define LIBNET_802_1Q_VIDMASK   0x0fff  /* vid mask */
    u_short vlan_len;                   /* len / type (802.3 / Ethernet II) */
};  


/*
 *  IEEE 802.2 LLC header
 *  Link Layer Control
 *  static header size: 3 bytes
 */
struct libnet_802_2_hdr
{
    u_char llc_dsap;            /* destination service access point */
    u_char llc_ssap;            /* source service access point */
#define LIBNET_SAP_STP          0x42
#define LIBNET_SAP_SNAP         0xaa
    u_char llc_control;         /* control field */
};


/*
 *  IEEE 802.2 LLC/SNAP header
 *  SubNetwork Attachment Point
 *  static header size: 8 bytes
 */
struct libnet_802_2snap_hdr
{
    u_char snap_dsap;           /* destination service access point */
    u_char snap_ssap;           /* destination service access point */
    u_char snap_control;        /* control field */
    u_char snap_oui[3];         /* OUI */
    u_short snap_type;          /* type */
};


/*
 *  802.3 header
 *  IEEE Ethernet
 *  Static header size: 14 bytes
 */
struct libnet_802_3_hdr
{
    u_char  _802_3_dhost[ETHER_ADDR_LEN];/* destination ethernet address */
    u_char  _802_3_shost[ETHER_ADDR_LEN];/* source ethernet address */
    u_short _802_3_len;                 /* packet type ID */
};


/* 
 *  ARP header
 *  Address Resolution Protocol
 *  Base header size: 8 bytes
 */
struct libnet_arp_hdr
{
    u_short ar_hrd;         /* format of hardware address */
#define ARPHRD_NETROM   0   /* from KA9Q: NET/ROM pseudo */
#define ARPHRD_ETHER    1   /* Ethernet 10Mbps */
#define ARPHRD_EETHER   2   /* Experimental Ethernet */
#define ARPHRD_AX25     3   /* AX.25 Level 2 */
#define ARPHRD_PRONET   4   /* PROnet token ring */
#define ARPHRD_CHAOS    5   /* Chaosnet */
#define ARPHRD_IEEE802  6   /* IEEE 802.2 Ethernet/TR/TB */
#define ARPHRD_ARCNET   7   /* ARCnet */
#define ARPHRD_APPLETLK 8   /* APPLEtalk */
#define ARPHRD_LANSTAR  9   /* Lanstar */
#define ARPHRD_DLCI     15  /* Frame Relay DLCI */
#define ARPHRD_ATM      19  /* ATM */
#define ARPHRD_METRICOM 23  /* Metricom STRIP (new IANA id) */
#define ARPHRD_IPSEC    31  /* IPsec tunnel */
    u_short ar_pro;         /* format of protocol address */
    u_char  ar_hln;         /* length of hardware address */
    u_char  ar_pln;         /* length of protocol addres */
    u_short ar_op;          /* operation type */
#define ARPOP_REQUEST    1  /* req to resolve address */
#define ARPOP_REPLY      2  /* resp to previous request */
#define ARPOP_REVREQUEST 3  /* req protocol address given hardware */
#define ARPOP_REVREPLY   4  /* resp giving protocol address */
#define ARPOP_INVREQUEST 8  /* req to identify peer */
#define ARPOP_INVREPLY   9  /* resp identifying peer */

    /* address information allocated dynamically */
};


/*
 *  CDP header
 *  Cisco Discovery Protocol
 *  Base header size: 8 bytes
 */

/*
 *  For checksum stuff -- IANA says 135-254 is "unassigned" as of 12.2001.
 *  Let's hope this one stays that way for a while!
 */
#define LIBNET_PROTO_CDP    200
struct libnet_cdp_hdr
{
    u_char cdp_version;     /* version (should always be 0x01) */
    u_char cdp_ttl;         /* time reciever should hold info in this packet */
    u_short cdp_sum;        /* checksum */
    u_short cdp_type;       /* type */
#define LIBNET_CDP_DEVID    0x1 /* device id */
#define LIBNET_CDP_ADDRESS  0x2 /* address */
#define LIBNET_CDP_PORTID   0x3 /* port id */
#define LIBNET_CDP_CAPABIL  0x4 /* capabilities */
#define LIBNET_CDP_VERSION  0x5 /* version */
#define LIBNET_CDP_PLATFORM 0x6 /* platform */
#define LIBNET_CDP_IPPREFIX 0x7 /* ip prefix */
    u_short cdp_len;        /* type + length + value */
    /* value information done dynamically */

/* CDP capabilities */
#define LIBNET_CDP_CAP_L3R  0x01/* performs level 3 routing */
#define LIBNET_CDP_CAP_L2B  0x02/* performs level 2 transparent bridging */
#define LIBNET_CDP_CAP_L2SRB 0x04/* performs level 2 sourceroute bridging */
#define LIBNET_CDP_CAP_L2S  0x08/* performs level 2 switching */
#define LIBNET_CDP_CAP_SR   0x10/* sends and recieves packets on a network */
#define LIBNET_CDP_CAP_NOI  0x20/* does not forward IGMP on non-router ports */
#define LIBNET_CDP_CAP_L1F  0x40/* provides level 1 functionality */
};


/*
 *  Used as an overlay for type/len/values
 */
struct libnet_cdp_value_hdr
{
    u_short cdp_type;
    u_short cdp_len;
};


/*
 *  DHCP header
 *  Dynamic Host Configuration Protocol
 *  Static header size: f0 bytes
 */
struct libnet_dhcpv4_hdr
{
    u_char dhcp_opcode;     /* opcode */
#define LIBNET_DHCP_REQUEST 0x1
#define LIBNET_DHCP_REPLY   0x2
    u_char dhcp_htype;      /* hardware address type */
    u_char dhcp_hlen;       /* hardware address length */
    u_char dhcp_hopcount;   /* used by proxy servers */
    u_long dhcp_xid;        /* transaction ID */
    u_short dhcp_secs;      /* number of seconds since trying to bootstrap */
    u_short dhcp_flags;     /* flags for DHCP, unused for BOOTP */
    u_long dhcp_cip;        /* client's IP */
    u_long dhcp_yip;        /* your IP */
    u_long dhcp_sip;        /* server's IP */
    u_long dhcp_gip;        /* gateway IP */
    u_char dhcp_chaddr[16]; /* client hardware address */
    u_char dhcp_sname[64];  /* server host name */
    u_char dhcp_file[128];  /* boot file name */
    u_long dhcp_magic;      /* BOOTP magic header */
#define DHCP_MAGIC                  0x63825363
#define LIBNET_BOOTP_MIN_LEN        0x12c
#define LIBNET_DHCP_PAD             0x00
#define LIBNET_DHCP_SUBNETMASK      0x01
#define LIBNET_DHCP_TIMEOFFSET      0x02
#define LIBNET_DHCP_ROUTER          0x03
#define LIBNET_DHCP_TIMESERVER      0x04
#define LIBNET_DHCP_NAMESERVER      0x05
#define LIBNET_DHCP_DNS             0x06
#define LIBNET_DHCP_LOGSERV         0x07
#define LIBNET_DHCP_COOKIESERV      0x08
#define LIBNET_DHCP_LPRSERV         0x09
#define LIBNET_DHCP_IMPSERV         0x0a
#define LIBNET_DHCP_RESSERV         0x0b
#define LIBNET_DHCP_HOSTNAME        0x0c
#define LIBNET_DHCP_BOOTFILESIZE    0x0d
#define LIBNET_DHCP_DUMPFILE        0x0e
#define LIBNET_DHCP_DOMAINNAME      0x0f
#define LIBNET_DHCP_SWAPSERV        0x10
#define LIBNET_DHCP_ROOTPATH        0x11
#define LIBNET_DHCP_EXTENPATH       0x12
#define LIBNET_DHCP_IPFORWARD       0x13
#define LIBNET_DHCP_SRCROUTE        0x14
#define LIBNET_DHCP_POLICYFILTER    0x15
#define LIBNET_DHCP_MAXASMSIZE      0x16
#define LIBNET_DHCP_IPTTL           0x17
#define LIBNET_DHCP_MTUTIMEOUT      0x18
#define LIBNET_DHCP_MTUTABLE        0x19
#define LIBNET_DHCP_MTUSIZE         0x1a
#define LIBNET_DHCP_LOCALSUBNETS    0x1b
#define LIBNET_DHCP_BROADCASTADDR   0x1c
#define LIBNET_DHCP_DOMASKDISCOV    0x1d
#define LIBNET_DHCP_MASKSUPPLY      0x1e
#define LIBNET_DHCP_DOROUTEDISC     0x1f
#define LIBNET_DHCP_ROUTERSOLICIT   0x20
#define LIBNET_DHCP_STATICROUTE     0x21
#define LIBNET_DHCP_TRAILERENCAP    0x22
#define LIBNET_DHCP_ARPTIMEOUT      0x23
#define LIBNET_DHCP_ETHERENCAP      0x24
#define LIBNET_DHCP_TCPTTL          0x25
#define LIBNET_DHCP_TCPKEEPALIVE    0x26
#define LIBNET_DHCP_TCPALIVEGARBAGE 0x27
#define LIBNET_DHCP_NISDOMAIN       0x28
#define LIBNET_DHCP_NISSERVERS      0x29
#define LIBNET_DHCP_NISTIMESERV     0x2a
#define LIBNET_DHCP_VENDSPECIFIC    0x2b
#define LIBNET_DHCP_NBNS            0x2c
#define LIBNET_DHCP_NBDD            0x2d
#define LIBNET_DHCP_NBTCPIP         0x2e
#define LIBNET_DHCP_NBTCPSCOPE      0x2f
#define LIBNET_DHCP_XFONT           0x30
#define LIBNET_DHCP_XDISPLAYMGR     0x31
#define LIBNET_DHCP_DISCOVERADDR    0x32
#define LIBNET_DHCP_LEASETIME       0x33
#define LIBNET_DHCP_OPTIONOVERLOAD  0x34
#define LIBNET_DHCP_MESSAGETYPE     0x35
#define LIBNET_DHCP_SERVIDENT       0x36
#define LIBNET_DHCP_PARAMREQUEST    0x37
#define LIBNET_DHCP_MESSAGE         0x38
#define LIBNET_DHCP_MAXMSGSIZE      0x39
#define LIBNET_DHCP_RENEWTIME       0x3a
#define LIBNET_DHCP_REBINDTIME      0x3b
#define LIBNET_DHCP_CLASSSID        0x3c
#define LIBNET_DHCP_CLIENTID        0x3d
#define LIBNET_DHCP_NISPLUSDOMAIN   0x40
#define LIBNET_DHCP_NISPLUSSERVERS  0x41
#define LIBNET_DHCP_MOBILEIPAGENT   0x44
#define LIBNET_DHCP_SMTPSERVER      0x45
#define LIBNET_DHCP_POP3SERVER      0x46
#define LIBNET_DHCP_NNTPSERVER      0x47
#define LIBNET_DHCP_WWWSERVER       0x48
#define LIBNET_DHCP_FINGERSERVER    0x49
#define LIBNET_DHCP_IRCSERVER       0x4a
#define LIBNET_DHCP_STSERVER        0x4b
#define LIBNET_DHCP_STDASERVER      0x4c
#define LIBNET_DHCP_END             0xff

#define LIBNET_DHCP_MSGDISCOVER     0x01
#define LIBNET_DHCP_MSGOFFER        0x02
#define LIBNET_DHCP_MSGREQUEST      0x03
#define LIBNET_DHCP_MSGDECLINE      0x04
#define LIBNET_DHCP_MSGACK          0x05
#define LIBNET_DHCP_MSGNACK         0x06
#define LIBNET_DHCP_MSGRELEASE      0x07
#define LIBNET_DHCP_MSGINFORM       0x08
};


/*
 *  Base DNSv4 header
 *  Domain Name System
 *  Base header size: 12 bytes
 */
struct libnet_dnsv4_hdr
{
    u_short id;             /* DNS packet ID */
    u_short flags;          /* DNS flags */
    u_short num_q;          /* Number of questions */
    u_short num_answ_rr;    /* Number of answer resource records */
    u_short num_auth_rr;    /* Number of authority resource records */
    u_short num_addi_rr;    /* Number of additional resource records */
};


/*
 *  Ethernet II header
 *  Static header size: 14 bytes
 */
struct libnet_ethernet_hdr
{
    u_char  ether_dhost[ETHER_ADDR_LEN];/* destination ethernet address */
    u_char  ether_shost[ETHER_ADDR_LEN];/* source ethernet address */
    u_short ether_type;                 /* protocol */
};

#define ETHERTYPE_PUP           0x0200  /* PUP protocol */
#define ETHERTYPE_IP            0x0800  /* IP protocol */
#define ETHERTYPE_ARP           0x0806  /* addr. resolution protocol */
#define ETHERTYPE_REVARP        0x8035  /* reverse addr. resolution protocol */
#define ETHERTYPE_VLAN          0x8100  /* IEEE 802.1Q VLAN tagging */
#define ETHERTYPE_LOOPBACK      0x9000  /* used to test interfaces */

struct libnet_ether_addr
{
    u_char  ether_addr_octet[6];        /* Ethernet address */
};


/*
 *  IPv4 header
 *  Internet Protocol, version 4
 *  Static header size: 20 bytes
 */
struct libnet_ipv4_hdr
{
#if (LIBNET_LIL_ENDIAN)
    unsigned ip_hl:4,       /* header length */
            ip_v:4;         /* version */
#endif
#if (LIBNET_BIG_ENDIAN)
    unsigned ip_v:4,        /* version */
           ip_hl:4;         /* header length */
#endif
    u_char ip_tos;          /* type of service */
#ifndef IPTOS_LOWDELAY
#define IPTOS_LOWDELAY      0x10
#endif
#ifndef IPTOS_THROUGHPUT
#define IPTOS_THROUGHPUT    0x08
#endif
#ifndef IPTOS_RELIABILITY
#define IPTOS_RELIABILITY   0x04
#endif
#ifndef IPTOS_LOWCOST
#define IPTOS_LOWCOST       0x02
#endif
    u_short ip_len;         /* total length */
    u_short ip_id;          /* identification */
    u_short ip_off;
#ifndef IP_RF
#define IP_RF 0x8000        /* reserved fragment flag */
#endif
#ifndef IP_DF
#define IP_DF 0x4000        /* dont fragment flag */
#endif
#ifndef IP_MF
#define IP_MF 0x2000        /* more fragments flag */
#endif 
#ifndef IP_OFFMASK
#define IP_OFFMASK 0x1fff   /* mask for fragmenting bits */
#endif
    u_char ip_ttl;          /* time to live */
    u_char ip_p;            /* protocol */
    u_short ip_sum;         /* checksum */
    struct in_addr ip_src, ip_dst; /* source and dest address */
};

/*
 *  IP options
 */
#ifndef IPOPT_EOL
#define IPOPT_EOL       0   /* end of option list */
#endif
#ifndef IPOPT_NOP
#define IPOPT_NOP       1   /* no operation */
#endif   
#ifndef IPOPT_RR
#define IPOPT_RR        7   /* record packet route */
#endif
#ifndef IPOPT_TS
#define IPOPT_TS        68  /* timestamp */
#endif
#ifndef IPOPT_SECURITY
#define IPOPT_SECURITY  130 /* provide s,c,h,tcc */   
#endif
#ifndef IPOPT_LSRR
#define IPOPT_LSRR      131 /* loose source route */
#endif
#ifndef IPOPT_SATID
#define IPOPT_SATID     136 /* satnet id */
#endif
#ifndef IPOPT_SSRR
#define IPOPT_SSRR      137 /* strict source route */
#endif

struct libnet_in6_addr
{
    union
    {
        u_char   __u6_addr8[16];
        u_short  __u6_addr16[8];
        u_long   __u6_addr32[4];
    } __u6_addr;            /* 128-bit IP6 address */
};
#define libnet_s6_addr __u6_addr.__u6_addr8
 

/*
 *  IPv6 header
 *  Internet Protocol, version 6
 *  Static header size: 40 bytes
 */
struct libnet_ipv6_hdr
{
    u_char ip_flags[4];     /* version, traffic class, flow label */
    u_short ip_len;         /* total length */
    u_char ip_nh;           /* next header */
    u_char ip_hl;           /* hop limit */
    struct libnet_in6_addr ip_src, ip_dst; /* source and dest address */

};

/*
 *  ICMP6 header
 *  Internet Control Message Protocol v6
 *  Base header size: 8 bytes
 */
#ifndef IPPROTO_ICMP6
#define IPPROTO_ICMP6   0x3a
#endif
struct libnet_icmpv6_hdr
{
    u_char icmp_type;       /* ICMP type */
#ifndef ICMP6_ECHO
#define ICMP6_ECHO          128
#endif
#ifndef ICMP6_ECHOREPLY
#define ICMP6_ECHOREPLY     129
#endif
#ifndef ICMP6_UNREACH
#define ICMP6_UNREACH       1
#endif
#ifndef ICMP6_PKTTOOBIG
#define ICMP6_PKTTOOBIG     2
#endif
#ifndef ICMP6_TIMXCEED
#define ICMP6_TIMXCEED      3
#endif
#ifndef ICMP6_PARAMPROB
#define ICMP6_PARAMPROB     4
#endif
    u_char icmp_code;       /* ICMP code */
    u_short icmp_sum;       /* ICMP Checksum */
    u_short id;             /* ICMP id */
    u_short seq;            /* ICMP sequence number */
};



/*
 *  ICMP header
 *  Internet Control Message Protocol
 *  Base header size: 4 bytes
 */
struct libnet_icmpv4_hdr
{
    u_char icmp_type;       /* ICMP type */
#ifndef     ICMP_ECHOREPLY
#define     ICMP_ECHOREPLY                  0
#endif
#ifndef     ICMP_UNREACH
#define     ICMP_UNREACH                    3
#endif
#ifndef     ICMP_SOURCEQUENCH
#define     ICMP_SOURCEQUENCH               4
#endif
#ifndef     ICMP_REDIRECT
#define     ICMP_REDIRECT                   5
#endif
#ifndef     ICMP_ECHO
#define     ICMP_ECHO                       8
#endif
#ifndef     ICMP_ROUTERADVERT
#define     ICMP_ROUTERADVERT               9
#endif
#ifndef     ICMP_ROUTERSOLICIT
#define     ICMP_ROUTERSOLICIT              10
#endif
#ifndef     ICMP_TIMXCEED
#define     ICMP_TIMXCEED                   11
#endif
#ifndef     ICMP_PARAMPROB
#define     ICMP_PARAMPROB                  12
#endif
#ifndef     ICMP_TSTAMP
#define     ICMP_TSTAMP                     13
#endif
#ifndef     ICMP_TSTAMPREPLY
#define     ICMP_TSTAMPREPLY                14
#endif
#ifndef     ICMP_IREQ
#define     ICMP_IREQ                       15
#endif
#ifndef     ICMP_IREQREPLY
#define     ICMP_IREQREPLY                  16
#endif
#ifndef     ICMP_MASKREQ
#define     ICMP_MASKREQ                    17
#endif
#ifndef     ICMP_MASKREPLY
#define     ICMP_MASKREPLY                  18
#endif
    u_char icmp_code;       /* ICMP code */
#ifndef     ICMP_UNREACH_NET
#define     ICMP_UNREACH_NET                0
#endif
#ifndef     ICMP_UNREACH_HOST
#define     ICMP_UNREACH_HOST               1
#endif
#ifndef     ICMP_UNREACH_PROTOCOL
#define     ICMP_UNREACH_PROTOCOL           2
#endif
#ifndef     ICMP_UNREACH_PORT
#define     ICMP_UNREACH_PORT               3
#endif
#ifndef     ICMP_UNREACH_NEEDFRAG
#define     ICMP_UNREACH_NEEDFRAG           4
#endif
#ifndef     ICMP_UNREACH_SRCFAIL
#define     ICMP_UNREACH_SRCFAIL            5
#endif
#ifndef     ICMP_UNREACH_NET_UNKNOWN
#define     ICMP_UNREACH_NET_UNKNOWN        6
#endif
#ifndef     ICMP_UNREACH_HOST_UNKNOWN
#define     ICMP_UNREACH_HOST_UNKNOWN       7
#endif
#ifndef     ICMP_UNREACH_ISOLATED
#define     ICMP_UNREACH_ISOLATED           8
#endif
#ifndef     ICMP_UNREACH_NET_PROHIB
#define     ICMP_UNREACH_NET_PROHIB         9
#endif
#ifndef     ICMP_UNREACH_HOST_PROHIB
#define     ICMP_UNREACH_HOST_PROHIB        10
#endif
#ifndef     ICMP_UNREACH_TOSNET
#define     ICMP_UNREACH_TOSNET             11
#endif
#ifndef     ICMP_UNREACH_TOSHOST
#define     ICMP_UNREACH_TOSHOST            12
#endif
#ifndef     ICMP_UNREACH_FILTER_PROHIB
#define     ICMP_UNREACH_FILTER_PROHIB      13
#endif
#ifndef     ICMP_UNREACH_HOST_PRECEDENCE
#define     ICMP_UNREACH_HOST_PRECEDENCE    14
#endif
#ifndef     ICMP_UNREACH_PRECEDENCE_CUTOFF
#define     ICMP_UNREACH_PRECEDENCE_CUTOFF  15
#endif
#ifndef     ICMP_REDIRECT_NET
#define     ICMP_REDIRECT_NET               0
#endif
#ifndef     ICMP_REDIRECT_HOST
#define     ICMP_REDIRECT_HOST              1
#endif
#ifndef     ICMP_REDIRECT_TOSNET
#define     ICMP_REDIRECT_TOSNET            2
#endif
#ifndef     ICMP_REDIRECT_TOSHOST
#define     ICMP_REDIRECT_TOSHOST           3
#endif
#ifndef     ICMP_TIMXCEED_INTRANS
#define     ICMP_TIMXCEED_INTRANS           0
#endif
#ifndef     ICMP_TIMXCEED_REASS
#define     ICMP_TIMXCEED_REASS             1
#endif
#ifndef     ICMP_PARAMPROB_OPTABSENT
#define     ICMP_PARAMPROB_OPTABSENT        1
#endif

    u_short icmp_sum;   /* ICMP Checksum */

    union
    {
        struct
        {
            u_short id; /* ICMP id */
            u_short seq;/* ICMP sequence number */
        } echo;

#undef icmp_id
#undef icmp_seq
#define icmp_id     hun.echo.id
#define icmp_seq    hun.echo.seq
 
        u_long gateway; /* gateway host */
        struct
        {
            u_short pad;/* padding */
            u_short mtu;/* MTU size */
        } frag;
    } hun;
    union
    {
        struct
        {
            n_time its_otime;
            n_time its_rtime;
            n_time its_ttime;
        } ts;
        struct
        {
            struct libnet_ipv4_hdr idi_ip;
            /* options and then 64 bits of data */
        } ip;
        u_long mask;
        char data[1];

#undef icmp_mask
#define icmp_mask    dun.mask
#undef icmp_data
#define icmp_data    dun.data

#undef icmp_otime
#define icmp_otime   dun.ts.its_otime
#undef icmp_rtime
#define icmp_rtime   dun.ts.its_rtime
#undef icmp_ttime
#define icmp_ttime   dun.ts.its_ttime
    }dun;
};


/*
 *  IGMP header
 *  Internet Group Message Protocol
 *  Static header size: 8 bytes
 */
struct libnet_igmp_hdr
{
    u_char igmp_type;       /* IGMP type */
#ifndef IGMP_MEMBERSHIP_QUERY
#define IGMP_MEMBERSHIP_QUERY           0x11    /* membership query */
#endif
#ifndef IGMP_V1_MEMBERSHIP_REPORT
#define IGMP_V1_MEMBERSHIP_REPORT       0x12    /* Ver. 1 membership report */
#endif
#ifndef IGMP_V2_MEMBERSHIP_REPORT
#define IGMP_V2_MEMBERSHIP_REPORT       0x16    /* Ver. 2 membership report */
#endif
#ifndef IGMP_LEAVE_GROUP
#define IGMP_LEAVE_GROUP                0x17    /* Leave-group message */
#endif
    u_char igmp_code;       /* IGMP code */
    u_short igmp_sum;       /* IGMP checksum */
    struct in_addr igmp_group;/* IGMP host IP */
};


/*
 *  IPSEC header
 *  Internet Protocol Security Protocol
 *  Encapsulating Security Payload Header Static header size: 12 bytes
 *  Encapsulating Security Payload Footer Base header size: 2 bytes
 *  Authentication Header Static Size: 16 bytes
 */
#ifndef IPPROTO_ESP
#define IPPROTO_ESP 50      /* not everyone's got this */
#endif
struct libnet_esp_hdr
{
   u_long esp_spi;          /* security parameter index */
   u_long esp_seq;          /* ESP sequence number */
   u_long esp_iv;           /* initialization vector */
};

struct libnet_esp_ftr
{
    u_char esp_pad_len;     /* padding length */
    u_char esp_nxt_hdr;     /* next header pointer */
    char *esp_auth;         /* authentication data */
};
 
#ifndef IPPROTO_AH
#define IPPROTO_AH 51       /* not everyone's got this */
#endif
struct libnet_ah_hdr
{
    u_char ah_nxt_hdr;      /* next header */
    u_char ah_len;          /* payload length */
    u_short ah_res;         /* reserved */
    u_long ah_spi;          /* security parameter index  */
    u_long ah_seq;          /* AH sequence number */
    u_long ah_auth;         /* authentication data */
};


/*
 *  ISL header
 *  Cisco Inter-Switch Link
 *  Static header size: 26 bytes
 */
/*
 *  For checksum stuff -- IANA says 135-254 is "unassigned" as of 12.2001.
 *  Let's hope this one stays that way for a while!
 */
#define LIBNET_PROTO_ISL    201
struct libnet_isl_hdr
{
    u_char isl_dhost[5];    /* destination address "01:00:0c:00:00" */
#if (LIBNET_LIL_ENDIAN)
    unsigned isl_type:4,    /* type of frame */
             isl_user:4;    /* user defined bits */
#endif
#if (LIBNET_BIG_ENDIAN)
    unsigned isl_user:4,    /* user defined bits */
             isl_type:4;    /* type of frame */
#endif
    u_char isl_shost[6];    /* source address */
    u_short isl_len;        /* total length of packet - 18 bytes */
    u_char isl_snap[6];     /* 0xaaaa03 + vendor code */
    u_short isl_vid;        /* 15 bit VLAN ID, 1 bit BPDU / CDP indicator */
    u_short isl_index;      /* port index */
    u_short isl_reserved;   /* used for FDDI and token ring */
    /* ethernet frame and 4 byte isl crc */
};

#ifndef IPPROTO_OSPF
#define IPPROTO_OSPF    89  /* not everyone's got this */
#endif
#define IPPROTO_OSPF_LSA    890     /* made this up.  Hope it's unused */
#define LIBNET_MODX         4102    /* used in LSA checksum */

/*
 *  Options used in multiple OSPF packets
 *  More info can be found in section A.2 of RFC 2328.
 */
#define LIBNET_OPT_EBIT  0x02 /* describes the way AS-external-LSAs are flooded */
#define LIBNET_OPT_MCBIT 0x04 /* whether or not IP multicast dgrams are fwdd */
#define LIBNET_OPT_NPBIT 0x08 /* describes handling of type-7 LSAs */
#define LIBNET_OPT_EABIT 0x10 /* rtr's willingness to send/recv EA-LSAs */
#define LIBNET_OPT_DCBIT 0x20 /* describes handling of demand circuits */


/*
 *  NTP header
 *  Network Time Protocol
 *  Static header size: 48 bytes
 */
struct libnet_ntp_hdr_l_fp  /* long floating point (64-bit) */
{
    u_long integer;         /* integer */
    u_long fraction;        /* fraction */
};

struct libnet_ntp_hdr_s_fp  /* short floating point (32-bit) */
{
    u_short integer;        /* integer */
    u_short fraction;       /* fraction */
};


struct libnet_ntp_hdr
{
    u_char ntp_li_vn_mode;              /* leap indicator, version, mode */
#define LIBNET_NTP_LI_NW    0x0         /* no warning */
#define LIBNET_NTP_LI_AS    0x1         /* last minute has 61 seconds */
#define LIBNET_NTP_LI_DS    0x2         /* last minute has 59 seconds */
#define LIBNET_NTP_LI_AC    0x3         /* alarm condition */

#define LIBNET_NTP_VN_2     0x2         /* version 2 */
#define LIBNET_NTP_VN_3     0x3         /* version 3 */
#define LIBNET_NTP_VN_4     0x4         /* version 4 */

#define LIBNET_NTP_MODE_R   0x0         /* reserved */
#define LIBNET_NTP_MODE_A   0x1         /* symmetric active */
#define LIBNET_NTP_MODE_P   0x2         /* symmetric passive */
#define LIBNET_NTP_MODE_C   0x3         /* client */
#define LIBNET_NTP_MODE_S   0x4         /* server */
#define LIBNET_NTP_MODE_B   0x5         /* broadcast */
#define LIBNET_NTP_MODE_RC  0x6         /* reserved for NTP control message */
#define LIBNET_NTP_MODE_RP  0x7         /* reserved for private use */
    u_char ntp_stratum;                 /* stratum */
#define LIBNET_NTP_STRATUM_UNAVAIL  0x0 /* unspecified or unavailable */
#define LIBNET_NTP_STRATUM_PRIMARY  0x1 /* primary reference (radio clock) */
                                        /* 2 - 15 is secondary */
                                        /* 16 - 255 is reserved */
    u_char ntp_poll;                    /* poll interval (should be 4 - 12) */
    u_char ntp_precision;               /* local clock precision */
    struct libnet_ntp_hdr_s_fp ntp_delay;       /* roundtrip delay */
    struct libnet_ntp_hdr_s_fp ntp_dispersion;  /* nominal error */
    u_long ntp_reference_id;                /* reference source id */
#define LIBNET_NTP_REF_LOCAL    0x4c4f434c  /* uncalibrated local clock */
#define LIBNET_NTP_REF_PPS      0x50505300  /* atomic / pulse-per-second clock */
#define LIBNET_NTP_REF_ACTS     0x41435453  /* NIST dialup modem */
#define LIBNET_NTP_REF_USNO     0x55534e4f  /* USNO modem service */
#define LIBNET_NTP_REF_PTB      0x50544200  /* PTB (German) modem service */ 
#define LIBNET_NTP_REF_TDF      0x54444600  /* Allouis (French) radio */
#define LIBNET_NTP_REF_DCF      0x44434600  /* Mainflingen (German) radio */
#define LIBNET_NTP_REF_MSF      0x4d534600  /* Rugby (UK) radio */
#define LIBNET_NTP_REF_WWV      0x57575600  /* Ft Collins (US) radio */
#define LIBNET_NTP_REF_WWVB     0x57575642  /* Boulder (US) radio */
#define LIBNET_NTP_REF_WWVH     0x57575648  /* Kaui Hawaii (US) radio */
#define LIBNET_NTP_REF_CHU      0x43485500  /* Ottaha (Canada) radio */
#define LIBNET_NTP_REF_LORC     0x4c4f5243  /* LORAN-C radionavigation */
#define LIBNET_NTP_REF_OMEG     0x4f4d4547  /* OMEGA radionavigation */
#define LIBNET_NTP_REF_GPS      0x47505300  /* global positioning system */
#define LIBNET_NTP_REF_GOES     0x474f4553  /* geostationary orbit env satellite */
    struct libnet_ntp_hdr_l_fp ntp_ref_ts;  /* reference timestamp */ 
    struct libnet_ntp_hdr_l_fp ntp_orig_ts; /* originate timestamp */
    struct libnet_ntp_hdr_l_fp ntp_rec_ts;  /* receive timestamp */
    struct libnet_ntp_hdr_l_fp ntp_xmt_ts;  /* transmit timestamp */
};


/*
 *  OSPFv2 header
 *  Open Shortest Path First
 *  Static header size: 16 bytes
 */
struct libnet_ospf_hdr
{
    u_char ospf_v;          /* version */
#define OSPFVERSION         2
    u_char ospf_type;       /* type */
#define  LIBNET_OSPF_UMD    0   /* UMd monitoring packet */
#define  LIBNET_OSPF_HELLO  1   /* HELLO packet */
#define  LIBNET_OSPF_DBD    2   /* dataBase description packet */
#define  LIBNET_OSPF_LSR    3   /* link state request packet */
#define  LIBNET_OSPF_LSU    4   /* link state Update Packet */
#define  LIBNET_OSPF_LSA    5   /* link state acknowledgement packet */
    u_short   ospf_len;     /* length */
    struct in_addr ospf_rtr_id; /* source router ID */
    struct in_addr ospf_area_id;/* roam ID */
    u_short ospf_cksum;         /* checksum */
    u_short ospf_auth_type;     /* authentication type */
#define LIBNET_OSPF_AUTH_NULL   0   /* null password */
#define LIBNET_OSPF_AUTH_SIMPLE 1   /* simple, plaintext, 8 char password */
#define LIBNET_OSPF_AUTH_MD5    2   /* MD5 */
};


/*
 *  OSPF authentication header
 *  Open Shortest Path First
 *  Static header size: 8 bytes
 */
struct libnet_auth_hdr
{
    u_short ospf_auth_null; /* NULL */
    u_char ospf_auth_keyid; /* authentication key ID */
    u_char ospf_auth_len;   /* auth data length */
    u_int ospf_auth_seq;    /* cryptographic sequence number */
};


/*
 *  OSPF hello header
 *  Open Shortest Path First
 *  Static header size: 28 bytes
 */
struct libnet_ospf_hello_hdr
{
    struct in_addr hello_nmask; /* netmask associated with the interface */
    u_short hello_intrvl;       /* num of seconds between routers last packet */
    u_char hello_opts;          /* Options for HELLO packets (look above) */
    u_char hello_rtr_pri;       /* router's priority (if 0, can't be backup) */
    u_int hello_dead_intvl;     /* # of secs a router is silent till deemed down */
    struct in_addr hello_des_rtr;   /* Designated router on the network */
    struct in_addr hello_bkup_rtr;  /* Backup router */
    struct in_addr hello_nbr;       /* neighbor router, memcpy more as needed */
};


/*
 *  Database Description header.
 */
struct libnet_dbd_hdr
{
    u_short dbd_mtu_len;    /* max length of IP dgram that this 'if' can use */
    u_char dbd_opts;        /* DBD packet options (from above) */
    u_char dbd_type;        /* type of exchange occurring */
#define LIBNET_DBD_IBI      0x01    /* init */
#define LIBNET_DBD_MBIT     0x02    /* more DBD packets are to come */
#define LIBNET_DBD_MSBIT    0x04    /* If 1, sender is the master in the exchange */
    u_int  dbd_seq;         /* DBD sequence number */
};


/*
 *  used for the LS type field in all LS* headers
 */
#define LIBNET_LS_TYPE_RTR      1   /* router-LSA */
#define LIBNET_LS_TYPE_NET      2   /* network-LSA */
#define LIBNET_LS_TYPE_IP       3   /* summary-LSA (IP Network) */
#define LIBNET_LS_TYPE_ASBR     4   /* summary-LSA (ASBR) */
#define LIBNET_LS_TYPE_ASEXT    5   /* AS-external-LSA */


/*
 *  Link State Request header
 */
struct libnet_lsr_hdr
{
    u_int lsr_type;             /* type of LS being requested */
    u_int lsr_lsid;             /* link state ID */
    struct in_addr lsr_adrtr;   /* advertising router (memcpy more as needed) */
};


/*
 *  Link State Update header
 */
struct libnet_lsu_hdr
{
    u_int lsu_num;              /* number of LSAs that will be broadcasted */
};


/*
 *  Link State Acknowledgement header.
 */
struct libnet_lsa_hdr
{
    u_short lsa_age;        /* time in seconds since the LSA was originated */
    u_char lsa_opts;        /* look above for OPTS_* */
    u_char lsa_type;        /* look below for LS_TYPE_* */
    u_int lsa_id;           /* link State ID */
    struct in_addr lsa_adv; /* router ID of Advertising router */
    u_int lsa_seq;          /* LSA sequence number to detect old/bad ones */
    u_short lsa_cksum;      /* "Fletcher Checksum" of all fields minus age */
    u_short lsa_len;        /* length in bytes including the 20 byte header */
};


/*
 *  Router LSA data format
 *
 *  Other stuff for TOS can be added for backward compatability, for this
 *  version, only OSPFv2 is being FULLY supported.
 */
struct libnet_rtr_lsa_hdr
{
    u_short rtr_flags;      /* set to help describe packet */
#define LIBNET_RTR_FLAGS_W  0x0100  /* W bit */
#define LIBNET_RTR_FLAGS_E  0x0200  /* E bit */
#define LIBNET_RTR_FLAGS_B  0x0400  /* B bit */
    u_short rtr_num;        /* number of links within that packet */
    u_int rtr_link_id;      /* describes link_data (look below) */
#define LIBNET_LINK_ID_NBR_ID   1   /* Neighbors router ID, also can be 4 */
#define LIBNET_LINK_ID_IP_DES   2   /* IP address of designated router */
#define LIBNET_LINK_ID_SUB      3   /* IP subnet number */
    u_int rtr_link_data;    /* Depending on link_id, info is here */
    u_char rtr_type;        /* Description of router link */
#define LIBNET_RTR_TYPE_PTP     1   /* Point-To-Point */
#define LIBNET_RTR_TYPE_TRANS   2   /* Connection to a "transit network" */
#define LIBNET_RTR_TYPE_STUB    3   /* Connectin to a "stub network" */
#define RTR_TYPE_VRTL   4   /* connects to a "virtual link" */
    u_char rtr_tos_num;     /* number of different TOS metrics for this link */
    u_short rtr_metric;     /* the "cost" of using this link */
};


/*
 *  Network LSA data format.
 */
struct libnet_net_lsa_hdr
{
    struct in_addr net_nmask;   /* Netmask for that network */
    u_int  net_rtr_id;          /* ID of router attached to that network */
};
 
 
/*
 *  Summary LSA data format.
 */
struct libnet_sum_lsa_hdr
{
    struct in_addr sum_nmask;   /* Netmask of destination IP address */
    u_int  sum_metric;          /* Same as in rtr_lsa (&0xfff to use last 24bit */
    u_int  sum_tos_metric;      /* first 8bits are TOS, 24bits are TOS Metric */
};
 
 
/*
 *  AS External LSA data format.
 *  & 0xfff logic operator for as_metric to get last 24bits.
 */
struct libnet_as_lsa_hdr
{
    struct in_addr as_nmask;    /* Netmask for advertised destination */
    u_int  as_metric;           /* May have to set E bit in first 8bits */
#define LIBNET_AS_E_BIT_ON 0x80000000  /* as_metric */
    struct in_addr as_fwd_addr; /* Forwarding address */
    u_int  as_rte_tag;          /* External route tag */
};


/*
 *  Base RIP header
 *  Routing Information Protocol
 *  Base header size: 24 bytes
 */
struct libnet_rip_hdr
{
    u_char rip_cmd;         /* RIP command */
#define RIPCMD_REQUEST   1  /* want info */
#define RIPCMD_RESPONSE  2  /* responding to request */
#define RIPCMD_TRACEON   3  /* turn tracing on */
#define RIPCMD_TRACEOFF  4  /* turn it off */
#define RIPCMD_POLL      5  /* like request, but anyone answers */
#define RIPCMD_POLLENTRY 6  /* like poll, but for entire entry */
#define RIPCMD_MAX       7  /* ? command */
    u_char rip_ver;         /* RIP version */
#define RIPVER_0         0
#define RIPVER_1         1
#define RIPVER_2         2
    u_short rip_rd;         /* Zero (v1) or Routing Domain (v2) */
    u_short rip_af;         /* Address family */
    u_short rip_rt;         /* Zero (v1) or Route Tag (v2) */
    u_long rip_addr;        /* IP address */
    u_long rip_mask;        /* Zero (v1) or Subnet Mask (v2) */
    u_long rip_next_hop;    /* Zero (v1) or Next hop IP address (v2) */
    u_long rip_metric;      /* Metric */
};


/*
 *  STP configuration header
 *  Spanning Tree Protocol
 *  Static header size: 35 bytes
 */
struct libnet_stp_conf_hdr
{
    u_short stp_id;         /* protocol id */
    u_char stp_version;     /* protocol version */
    u_char stp_bpdu_type;   /* bridge protocol data unit type */
    u_char stp_flags;       /* control flags */
    u_char stp_rootid[8];   /* root id */
    u_long stp_rootpc;      /* root path cost */
    u_char stp_bridgeid[8]; /* bridge id */
    u_short stp_portid;     /* port id */
    u_short stp_mage;       /* message age */
    u_short stp_maxage;     /* max age */
    u_short stp_hellot;     /* hello time */
    u_short stp_fdelay;     /* forward delay */
};


/*
 *  STP topology change notification header
 *  Spanning Tree Protocol
 *  Static header size: 4 bytes
 */
struct libnet_stp_tcn_hdr
{
    u_short stp_id;         /* protocol id */
    u_char stp_version;     /* protocol version */
    u_char stp_bpdu_type;   /* bridge protocol data unit type */
};


/*
 *  TCP header
 *  Transmission Control Protocol
 *  Static header size: 20 bytes
 */
struct libnet_tcp_hdr
{
    u_short th_sport;       /* source port */
    u_short th_dport;       /* destination port */
    u_long th_seq;          /* sequence number */
    u_long th_ack;          /* acknowledgement number */
#if (LIBNET_LIL_ENDIAN)
    unsigned th_x2:4,       /* (unused) */
           th_off:4;        /* data offset */
#endif
#if (LIBNET_BIG_ENDIAN)
    unsigned th_off:4,      /* data offset */
           th_x2:4;         /* (unused) */
#endif
    u_char  th_flags;       /* control flags */
#ifndef TH_FIN
#define TH_FIN    0x01      /* finished send data */
#endif
#ifndef TH_SYN
#define TH_SYN    0x02      /* synchronize sequence numbers */
#endif
#ifndef TH_RST
#define TH_RST    0x04      /* reset the connection */
#endif
#ifndef TH_PUSH
#define TH_PUSH   0x08      /* push data to the app layer */
#endif
#ifndef TH_ACK
#define TH_ACK    0x10      /* acknowledge */
#endif
#ifndef TH_URG
#define TH_URG    0x20      /* urgent! */
#endif
    u_short th_win;         /* window */
    u_short th_sum;         /* checksum */
    u_short th_urp;         /* urgent pointer */
};


/*
 *  UDP header
 *  User Data Protocol
 *  Static header size: 8 bytes
 */
struct libnet_udp_hdr
{
    u_short uh_sport;       /* soure port */
    u_short uh_dport;       /* destination port */
    u_short uh_ulen;        /* length */
    u_short uh_sum;         /* checksum */
};


/*
 *  VRRP header
 *  Virtual Router Redundancy Protocol
 *  Static header size: 8 bytes
 */
#ifndef IPPROTO_VRRP
#define IPPROTO_VRRP 112    /* not everyone's got this */
#endif
struct libnet_vrrp_hdr
{
#if (LIBNET_LIL_ENDIAN)
    unsigned vrrp_v:4,      /* protocol version */
           vrrp_t:4;        /* packet type */
#endif
#if (LIBNET_BIG_ENDIAN)
    unsigned vrrp_t:4,      /* packet type */
           vrrp_v:4;        /* protocol version */
#endif
#define LIBNET_VRRP_VERSION_01  0x1
#define LIBNET_VRRP_VERSION_02  0x2
#define LIBNET_VRRP_TYPE_ADVERT 0x1
    u_char vrrp_vrouter_id; /* virtual router id */
    u_char vrrp_priority;   /* priority */
    u_char vrrp_ip_count;   /* number of IP addresses */
    u_char vrrp_auth_type;  /* authorization type */
#define LIBNET_VRRP_AUTH_NONE   0x1
#define LIBNET_VRRP_AUTH_PASSWD 0x2
#define LIBNET_VRRP_AUTH_IPAH   0x3
    u_char vrrp_advert_int; /* advertisement interval */
    u_short vrrp_sum;       /* checksum */
    /* additional addresses */
    /* authentication info */
};

#endif  /* __LIBNET_HEADERS_H */

/* EOF */

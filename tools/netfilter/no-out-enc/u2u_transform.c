
/* ================================================================
  $Id: u2u_transform.c,v 1.8 2011/06/01 04:30:11 oneway Exp oneway $
  1. Decapsulates incoming UDP to TCP
  2. Encapsulates outgoing TCP to UDP 

In 1, incoming UDP has payload padding and encryption, except 
if the payload is PSH/ACK, no padding, only encryption. 
In 2, no padding/encryption yet. 

Iptables rules used: 

port=4000
/sbin/iptables -F
/sbin/iptables -I INPUT -p udp --dport $port -j NFQUEUE --queue-num 3
/sbin/iptables -I OUTPUT -p tcp -s 192.168.1.80 --sport $port -j NFQUEUE --queue-num 3
====================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <linux/types.h>
#include <linux/netfilter.h>		/* for NF_ACCEPT */
#include <arpa/inet.h>
#include <sys/socket.h>

#include <libnetfilter_queue/libnetfilter_queue.h>

#define __FAVOR_BSD
#include <netinet/udp.h>
#include <netinet/tcp.h>

/* global variables */
int stateful = 0;    // 1: transforms psh/ack after seeing ack in 
                     // 0: transforms psh/ack anyway 

int sock;   // for socket sending of UDP

unsigned char newpkt[4096];   // this is for transforms that expand 
                              // the size of the original packet. 
                              // Need a new buffer for that. 

struct pseudo_header {   //needed for checksum calculation
        unsigned long source_address;
        unsigned long dest_address;
        unsigned char placeholder;
        unsigned char protocol;
        unsigned short tcp_length;
        //char tcp[28];
        struct tcphdr tcp;
};   

struct upseudo_header {   //needed for checksum calculation
        unsigned long source_address;
        unsigned long dest_address;
        unsigned char placeholder;
        unsigned char protocol;
        unsigned short udp_length;
        //char tcp[28];
        struct udphdr udp;
};

//General Networking Functions
 unsigned short in_checksum( unsigned short *ptr, int nbytes) {
        register long sum;
        unsigned short oddbyte;
        register short answer;

        sum=0;
        while(nbytes>1) {
                sum+=*ptr++;
                nbytes-=2;
        }
        if(nbytes==1) {
                oddbyte=0;
                *((u_char*)&oddbyte)=*(u_char*)ptr;
                sum+=oddbyte;
        }

        sum = (sum>>16)+(sum & 0xffff);
        sum = sum + (sum>>16);
        answer=(short)~sum;

        return(answer);
}

void print_ip_pkt(unsigned char *data, unsigned int ip_len) { 
    int i; 

    printf("payload_len=%d \n", ip_len);
    // display packet data
    printf("%43s", " ");
    for (i = 0; i < ip_len; i++) {
        printf("%02x ", data[i]);
        switch ( (i+15)% 16 ) {
           case 0: printf("\n");  break;
           case 8: printf(" ");  break;
        }
    }
   fputc('\n', stdout);
   fputc('\n', stdout);
}

/* sends out a UDP via regular socket,  so hopefully 
   conntrack can fix it 
*/
unsigned int send_udp(unsigned char *newpkt, unsigned int pay_len) {
   int hdrlen; 
   struct sockaddr_in dst_addr;   // source and dst 
   struct ip *iph = (struct ip *) newpkt;
   struct tcphdr *tcph = (struct tcphdr *) ( newpkt + sizeof(struct ip) ) ;
   memset(&dst_addr, 0, sizeof(dst_addr)); 
   dst_addr.sin_family = AF_INET; 
   dst_addr.sin_addr.s_addr = iph->ip_dst.s_addr;
   dst_addr.sin_port = tcph->th_dport; 
   tcph->th_sport = htons(444); 
   hdrlen = sizeof(struct ip); 
#ifdef DEBUG
   if (pay_len-hdrlen >= 0) print_ip_pkt(newpkt+hdrlen, pay_len - hdrlen); 
#endif
   return sendto(sock, newpkt + hdrlen, pay_len - hdrlen, 0, 
                       (struct sockaddr *) &dst_addr, 
                       sizeof(dst_addr) ); 
}


/* remove UDP encapsulation */
/* no padding for PSH/ACK segments */
unsigned int transform_u2t(unsigned char *data, unsigned int ip_len) {
  unsigned char seudo[4096];
  unsigned char sip[256];
  unsigned char dip[256];
  int i, rndl, tcpl;
  struct pseudo_header phdr;
  struct ip *iph = (struct ip *) data;
  struct udphdr *udph = (struct udphdr *) ( data + sizeof(struct ip) ) ;
  struct tcphdr *tcph = (struct tcphdr *) ( data + sizeof(struct ip) +
                                                   sizeof(struct udphdr) );
  time_t rawt;
  char *tstr;
  unsigned key; 

  /* decrypting payload */ 
  tcpl = ip_len - sizeof(struct ip) - sizeof(struct udphdr); 
  key = ( ( ip_len * ip_len ) % 127 ) + 1; 
  tstr = (char *) tcph; 
  for (i=0; i<tcpl; i++) tstr[i] = tstr[i] ^ key;  

#ifdef DEBUG
      printf("\nTCP in UDP ack= %u\n", ntohl(tcph->th_ack)) ;
      printf("\ntcph->th_off= %u\n", tcph->th_off) ;
      printf("\ntcph->th_x2= %u\n", tcph->th_x2) ;
      printf("\niph->ip_len= %u\n", ntohs(iph->ip_len)) ;
      time ( &rawt );
      tstr = ctime( &rawt );
      for (i=4; i<strlen(tstr)-5; i++) putchar(tstr[i]);
      printf("TCP in UDP: %s:%d -> %s:%d\n",
             sip, ntohs(tcph->th_sport),
             dip, ntohs(tcph->th_dport) );
      printf("TCP in UDP flag in: %02x \n", tcph->th_flags); 
#endif
  tcph->th_sport = udph->uh_sport;
  tcph->th_dport = udph->uh_dport;
  // Get rid of UDP encap, ignore any TCP payload if not PSH/ACK
  if (tcph->th_flags != 0x18 ) tcpl = tcph->th_off * 4;  // header length only
  memcpy( (char *)udph, (char *)tcph, tcpl);
  tcph = (struct tcphdr *) udph;   // move up the tcp header pointer 

  iph->ip_p = 6; 
  iph->ip_len = htons( tcpl + sizeof(struct ip) );   // new packet length
  iph->ip_sum = 0; 
  iph->ip_sum = in_checksum((unsigned short*)iph, sizeof(struct ip)); 
  // Recalculate TCP checksum because IP header possibly changed due to NAT
  tcph->th_sum = 0;
  phdr.source_address =  iph->ip_src.s_addr;
  phdr.dest_address =  iph->ip_dst.s_addr;
  phdr.placeholder = 0;
  phdr.protocol = IPPROTO_TCP;
  phdr.tcp_length = htons( tcpl );
  memcpy(&phdr.tcp, (unsigned char *)tcph, sizeof(struct tcphdr) );
  memcpy(seudo, &phdr, sizeof(struct pseudo_header) );
  // append tcp option, payload
  memcpy(seudo + sizeof(struct pseudo_header),
         (unsigned char *)tcph+sizeof(struct tcphdr),
         tcpl - sizeof(struct tcphdr) );

  tcph->th_sum = in_checksum((unsigned short*)seudo,
       sizeof(struct pseudo_header) +          //pseudo-hdr + payload
       tcpl - sizeof(struct tcphdr) );

  return sizeof(struct ip) + tcpl; 
}


/* remove UDP encapsulation to a TCP segment */
unsigned int transform_t2u(unsigned char *data, unsigned int ip_len) { 
  unsigned char seudo[4096];
  unsigned char rndc[256];
  unsigned char sip[256]; 
  unsigned char dip[256]; 
  int i, rndl, tcpl, newl; 
  // craft typical win tcp options
  unsigned char opt[] = "\x02\x04\x04\xec\x01\x01\x04\x02"; 
  struct upseudo_header uphdr; 
  static unsigned long lastseq;   // save the seq # of the incoming ack 
  time_t rawt;
  char *tstr; 
  unsigned key;

  // point to the new data structure, newpkt. global var
  struct ip *iph = (struct ip *) newpkt;
  struct udphdr *udph = (struct udphdr *) ( newpkt + sizeof(struct ip) ) ;
  struct tcphdr *tcph = (struct tcphdr *) ( newpkt + sizeof(struct ip) +
                                                   sizeof(struct udphdr) );
  tcpl = ip_len - sizeof(struct ip); 
  newl = ip_len + sizeof(struct udphdr); 
  memcpy( (char *)iph, data, sizeof(struct ip) );
  memcpy( (char *)tcph, data + sizeof(struct ip), tcpl); 
  udph->uh_sport = tcph->th_sport; 
  udph->uh_dport = tcph->th_dport; 
  udph->uh_ulen = htons( sizeof(struct udphdr) + tcpl ); 
  udph->uh_sum  = 0;

  // padding and encryption 
      
#ifdef DEBUG
      time ( &rawt ); 
      tstr = ctime( &rawt );
      for (i=4; i<strlen(tstr)-5; i++) putchar(tstr[i]);
      printf("TCP: %s:%d -> %s:%d\n", 
             sip, ntohs(tcph->th_sport), 
             dip, ntohs(tcph->th_dport) );  
      printf("TCP flag in: %02x TCP flag out: %02x\n", tcph->th_flags, TH_SYN); 
#endif

      iph->ip_len = htons(newl);   // new packet length
      iph->ip_p = 17;       // UDP
      iph->ip_sum = 0; 
      iph->ip_sum = in_checksum((unsigned short*)iph, sizeof(struct ip)); 
       
  // Recalculate UDP checksum
  udph->uh_sum = 0;
  uphdr.source_address =  iph->ip_src.s_addr; 
  uphdr.dest_address =  iph->ip_dst.s_addr; 
  uphdr.placeholder = 0;
  uphdr.protocol = IPPROTO_UDP;
  uphdr.udp_length = htons( newl - sizeof(struct ip) );
  memcpy(&uphdr.udp, (unsigned char *)udph, sizeof(struct udphdr) );
  memcpy(seudo, &uphdr, sizeof(struct upseudo_header) ); 
  // append payload
  memcpy(seudo + sizeof(struct upseudo_header), 
         (unsigned char *)udph+sizeof(struct udphdr),
         newl-sizeof(struct ip) - sizeof(struct udphdr) ); 

  udph->uh_sum = in_checksum((unsigned short*)seudo,
       sizeof(struct upseudo_header) + newl         //pseudo-hdr + payload
       - sizeof(struct ip) - sizeof(struct udphdr) );

  return newl; 
}

/* returns packet id */
static u_int32_t display_pkt (struct nfq_data *tb)
{
	int id = 0;
	struct nfqnl_msg_packet_hdr *ph;
	struct nfqnl_msg_packet_hw *hwph;
	u_int32_t mark,ifi; 
	int ret, i;
	unsigned char *data;

	ph = nfq_get_msg_packet_hdr(tb);
	if (ph) {
		id = ntohl(ph->packet_id);
#ifdef DEBUG
		printf("hw_protocol=0x%04x hook=%u id=%u ",
			ntohs(ph->hw_protocol), ph->hook, id);
#endif
	}

#ifdef DEBUG
	hwph = nfq_get_packet_hw(tb);
	if (hwph) {
		int i, hlen = ntohs(hwph->hw_addrlen);

		printf("hw_src_addr=");
		for (i = 0; i < hlen-1; i++)
			printf("%02x:", hwph->hw_addr[i]);
		printf("%02x ", hwph->hw_addr[hlen-1]);
	}

	mark = nfq_get_nfmark(tb);
	if (mark)
		printf("mark=%u ", mark);

	ifi = nfq_get_indev(tb);
	if (ifi)
		printf("indev=%u ", ifi);

	ifi = nfq_get_outdev(tb);
	if (ifi)
		printf("outdev=%u ", ifi);
	ifi = nfq_get_physindev(tb);
	if (ifi)
		printf("physindev=%u ", ifi);

	ifi = nfq_get_physoutdev(tb);
	if (ifi)
		printf("physoutdev=%u ", ifi);

#endif
	ret = nfq_get_payload(tb, &data);
#ifdef DEBUG
	if (ret >= 0) print_ip_pkt(data, ret); 
#endif

	return id;
}
	

static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
	      struct nfq_data *nfa, void *data)
{
	unsigned char *payload;
	unsigned int pay_len, encl; 
        struct ip *iph, *iph2; 

	u_int32_t id = display_pkt(nfa);
	pay_len = nfq_get_payload(nfa, &payload);  

#ifdef DEBUG
	printf("entering callback\n");
	printf("Transformed packet\n");
        print_ip_pkt(payload, pay_len); 
#endif

        encl = sizeof(struct ip); 
        iph = (struct ip *) payload; 
        //-if ( iph->ip_p == 4 ) { // UDP encap'g TCP 
        //-  iph2 = (struct ip *) ( payload + encl ); 
        //-  if ( iph2->ip_p == 17 ) { // UDP encap'g TCP 
          if ( iph->ip_p == 17 ) { // UDP encap'g TCP 
#ifdef DEBUG
 	    //- printf("ipip enc UDP recieved, encl=%d\n", encl);
 	    printf("udp enc tcp receivved\n"); 
#endif
          //- pay_len = transform_u2t( (payload + encl), pay_len - encl ) 
          //-            + encl;  // return new len
           pay_len = transform_u2t( payload , pay_len);  
	   return nfq_set_verdict(qh, id, NF_ACCEPT, pay_len, payload);
         //-} else { 
	 //-  return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
         //- }
        } else {  // TCP 
        //  pay_len = transform_t2u(payload, pay_len);  // data in newpkt now 
       // send it back to kernel, so hopefully onntrack will take care of it
          if ( send_udp(payload, pay_len) < 0 )   
            fprintf(stderr, "socket sending udp failed ..."); 
                                                 
	  //return nfq_set_verdict(qh, id, NF_ACCEPT, pay_len, newpkt);
	  return nfq_set_verdict(qh, id, NF_DROP, 0, NULL); 
        }
}

int main(int argc, char **argv)
{
   struct sockaddr_in src_addr;   // source and dst

	struct nfq_handle *h;
	struct nfq_q_handle *qh;
	struct nfnl_handle *nh;
	int fd, qid;
	int rv;
	char buf[4096] __attribute__ ((aligned));

        if(argc != 3) {
          printf("Usage: %s -q n  \n", argv[0]);
          printf("       -q: queue id\n"); 
          exit(-1);
        }

       stateful = 0;  
       if ( strncmp (argv[1], "-q", 2) == 0 ) {
          qid = atoi(argv[2]);  
#ifdef DEBUG
	  printf("Queue %d started ...\n", qid);
#endif
       } else  {
	  printf("Wrong option. Exit ...\n");
          exit(-1);
       }

     /* Create the UDP socket */
       memset(&src_addr, 0, sizeof(src_addr));
       src_addr.sin_family = AF_INET;
       src_addr.sin_addr.s_addr = inet_addr("192.168.1.80"); 
       src_addr.sin_port = htons(4000); 
       
       if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
           fprintf(stderr, "failed to create socket");
           exit(1); 
       }
  
       if ( bind(sock, (struct sockaddr *)&src_addr, sizeof(src_addr)) < 0 ){ 
           fprintf(stderr, "failed to bind  socket");
           exit(1); 
       }

	printf("opening library handle\n");
	h = nfq_open();
	if (!h) {
		fprintf(stderr, "error during nfq_open()\n");
		exit(1);
	}

	printf("unbinding existing nf_queue handler for AF_INET (if any)\n");
	if (nfq_unbind_pf(h, AF_INET) < 0) {
		fprintf(stderr, "error during nfq_unbind_pf()\n");
		exit(1);
	}

	printf("binding nfnetlink_queue as nf_queue handler for AF_INET\n");
	if (nfq_bind_pf(h, AF_INET) < 0) {
		fprintf(stderr, "error during nfq_bind_pf()\n");
		exit(1);
	}

	printf("binding this socket to queue %d\n", qid);
	qh = nfq_create_queue(h,  qid, &cb, NULL);
	if (!qh) {
		fprintf(stderr, "error during nfq_create_queue()\n");
		exit(1);
	}

	printf("setting copy_packet mode\n");
	if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
		fprintf(stderr, "can't set packet_copy mode\n");
		exit(1);
	}

	fd = nfq_fd(h);

	while ((rv = recv(fd, buf, sizeof(buf), 0)) && rv >= 0) {
		printf("pkt received\n");
		nfq_handle_packet(h, buf, rv);
	}

	printf("unbinding from queue 0\n");
	nfq_destroy_queue(qh);

#ifdef INSANE
	/* normally, applications SHOULD NOT issue this command, since
	 * it detaches other programs/sockets from AF_INET, too ! */
	printf("unbinding from AF_INET\n");
	nfq_unbind_pf(h, AF_INET);
#endif

	printf("closing library handle\n");
	nfq_close(h);

	exit(0);
}

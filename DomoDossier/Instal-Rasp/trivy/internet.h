#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include "accesBDD.h"
#include <string.h>

#define PACKETSIZE  64

struct packet {
    struct icmphdr hdr;
    char msg[PACKETSIZE - sizeof (struct icmphdr)];
};

class internet {
    int pid;
    struct protoent *proto;
    struct packet pckt;
    struct sockaddr_in r_addr;
    struct hostent *hname;
    struct sockaddr_in addr_ping, *addr;
    int cnt;
    accesBDD* adbdd;

public:
    internet();
    unsigned short checksum(void*, int);
    int ping(const char*);
    int putFTP(string);
    void setAdBDD(accesBDD*);
};

#include "internet.h"

internet::internet() {
    pid = -1;
    proto = NULL;
    cnt = 1;
}

/**
 * 
 * @param ad
 */
void internet::setAdBDD(accesBDD* ad) {
    adbdd = ad;
}



/*--------------------------------------------------------------------*/
/*--- checksum - standard 1s complement checksum                   ---*/
/*--------------------------------------------------------------------*/
unsigned short internet::checksum(void *b, int len) {
    unsigned short *buf = (unsigned short*) b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*) buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

/*--------------------------------------------------------------------*/
/*--- ping - Create message and send it.                           ---*/
/*    return 0 is ping not Ok, return 1 is ping OK.                ---*/
/*--------------------------------------------------------------------*/
int internet::ping(const char *adress) {
    const int val = 255;
    int i, sd, lenS, loop;

    pid = getpid();
    proto = getprotobyname("ICMP");
    hname = gethostbyname(adress);
    bzero(&addr_ping, sizeof (addr_ping));
    addr_ping.sin_family = hname->h_addrtype;
    addr_ping.sin_port = 0;
    addr_ping.sin_addr.s_addr = *(long*) hname->h_addr;

    addr = &addr_ping;
    sd = socket(PF_INET, SOCK_RAW, proto->p_proto);
    if (sd < 0) {
        fprintf(stderr, "err socket");
        return 0;
    }
    if (setsockopt(sd, SOL_IP, IP_TTL, &val, sizeof (val)) != 0) {
        fprintf(stderr,"err Set TTL option");
        return 0;
    }
    if (fcntl(sd, F_SETFL, O_NONBLOCK) != 0) {
        fprintf(stderr,"err Request nonblocking I/O");
        return 0;
    }
    for (loop = 0; loop < 2; loop++) {
        lenS = sizeof (r_addr);

        if (recvfrom(sd, &pckt, sizeof (pckt), 0, (struct sockaddr*) &r_addr, (socklen_t*) & lenS) > 0) {
            return 1;
        }

        bzero(&pckt, sizeof (pckt));
        pckt.hdr.type = ICMP_ECHO;
        pckt.hdr.un.echo.id = pid;
        for (i = 0; i < (int)sizeof (pckt.msg) - 1; i++)
            pckt.msg[i] = i + '0';
        pckt.msg[i] = 0;
        pckt.hdr.un.echo.sequence = cnt++;
        pckt.hdr.checksum = checksum(&pckt, sizeof (pckt));
        if (sendto(sd, &pckt, sizeof (pckt), 0, (struct sockaddr*) addr, sizeof (*addr)) <= 0)
            fprintf(stderr,"err sendto");
        usleep(300000);
    }
    //puts("fin ping");
    return 0;
}

int internet::putFTP(string img) {
    char site[50];
    //const char *site1="192.168.0.254";
    //const char *site2="192.168.1.254";
    char command[250];
    //cout<<"ftp : "<<img<<endl;
    strcpy(site,"www.orange.fr");
    // curl -u gillesaucaigne@orange.fr:gilles21 -T "{esPing.cpp,route.txt}" ftp://perso-ftp.orange.fr/images/
    if (ping(site)) { // Il y a du réseau
        string stftp = "curl --user " + adbdd->getftplogin() + ':' + adbdd->getftpmdp() + " -T \"{" + img + "}\" " + adbdd->getftpadr() + " > 0\n";
        //cout<<stftp<<endl;
        strcpy(command, stftp.c_str());
        system(command);
        cout<<endl<<"Image envoyee sur Orange"<<endl;
        usleep(1000000);//1s
    } else
        fprintf(stderr, "Pas de réseau WAN");
}

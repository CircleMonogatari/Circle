#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>

int main(int argc, const char* argv[])
{
    int fd=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in serv;
    serv.sin_family=AF_INET;
    serv.sin_port=htons(9999);
    inet_pton(AF_INET,"0.0.0.0",&serv.sin_addr.s_addr);
    socklen_t slen=sizeof(serv);

    bind(fd,(struct sockaddr*)&serv,sizeof(serv));
  //  setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&flag,);
    
    struct ip_mreqn group;
    inet_pton(AF_INET,"239.0.0.10",group.
    inet_pton(AF_INET
            if_nametoindex("ech0");
    setsockopt(fd,IPPROTO_TP,TP_ADD_MEMBERSHIP,&group,sizeof(group));

    while(1)
    {
        char buf[1024]="老尚快!";
        sendto(fd,buf,sizeof(buf),MSG_EOR,(struct sockaddr*)&serv,slen);
    }

    return 0;
}

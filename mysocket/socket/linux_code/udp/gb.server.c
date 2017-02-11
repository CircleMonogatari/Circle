#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, const char* argv[])
{
    int fd=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in serv;
    serv.sin_family=AF_INET;
    serv.sin_port=htons(9999);
    serv.sin_addr.s_addr=htonl("192.168.41.255");
   // inet_pton(AF_INET,"0.0.0.0",&serv.sin_addr.s_addr);
    socklen_t slen=sizeof(serv);

   // bind(fd,(struct sockaddr*)&serv,sizeof(serv));
    setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&flag,);
    while(1)
    {
        char buf[1024]="老尚最快!";
        sendto(fd,buf,sizeof(buf),MSG_EOR,(struct sockaddr*)&serv,slen);
    }

    return 0;
}

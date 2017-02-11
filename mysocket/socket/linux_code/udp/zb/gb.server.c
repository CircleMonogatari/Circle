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
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    socklen_t slen=sizeof(serv);
    bind(fd,(struct sockaddr*)&serv,sizeof(serv));
  
    int flag=1;
    setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag));
    
    struct sockaddr_in cliend;
    socklen_t clen=sizeof(cliend);

    cliend.sin_port=htons(22);
    cliend.sin_family=AF_INET;

    inet_pton(AF_INET,"192.168.41.255",&cliend.sin_addr.s_addr);
    

    while(1)
    {
        char buf[1024*4]="老尚最快111!";
        sendto(fd,buf,sizeof(buf),MSG_EOR,(struct sockaddr*)&cliend,clen);
    }

    return 0;
}

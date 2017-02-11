#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    //创建套接字   ipv4协议   流式协议 udp
    int fd=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in sev;
    sev.sin_family=AF_INET;
    sev.sin_port=htons(9999);
    sev.sin_addr.s_addr=htonl(INADDR_ANY);

    //通信
    while(1)
    {
        char buf[1024]={0};
        char ipbuf[1024]={0};
        struct sockaddr_in client;
        socklen_t c_len=sizeof(client);
        int len=recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&client,&c_len);
        printf("client ip :%s ,port %d\n",
               inet_ntop(AF_INET,&client.sin_addr.s_addr,&ipbuf,sizeof(ipbuf)),
              client.sin_port
               );
        puts(buf);
            


    }
}

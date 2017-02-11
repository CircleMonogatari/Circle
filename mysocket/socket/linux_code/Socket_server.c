#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, const char* argv[])
{
    //监听套接字  ipv4 流协议 0是tcp协议
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    //设置绑定端口属性 server绑定   cliend链接
    struct sockaddr_in server_addr,cliend_addr;
    socklen_t cliend_len=sizeof(cliend_addr);

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(9999);//端口
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    //帮定端口 bind
 
    //new 端口复用
    int opt=1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&opt,sizeof(opt));
    //绑定   
    int ret=bind(lfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(ret==-1)
    {
        perror("bind error:");
        exit(1);
    }
    //监听
    ret=listen(lfd,32);
    if(ret==-1)
    {
        perror("listen error:");
        exit(1);
    }

    //while(1)
    // {
    int cld=accept(lfd,(struct sockaddr*)&cliend_addr,&cliend_len);
    //等待链

        if(cld==-1)
        {
            perror("error accept:");
        }
        char buf[10]={0};
        int n=0;
    while( (n=recv(cld,buf,sizeof(buf),0)))
    {    puts("--------------------------------------------");

        if(n==0)
        {
            puts("client exit");
            break;
        }
        else if(n==-1)
        {
            perror("recv error:");
            exit(1);
        }
        else if(n>0)
        {
            printf("buf=%d|%s",n,buf);
        }
        memset(buf,0,sizeof(buf));
    }    
    //通信
 

return 0;
}






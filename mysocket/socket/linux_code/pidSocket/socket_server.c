#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>

int  p_error(int n,char *buf)
{
    if(n==-1)
    {
    perror(buf);
    exit(1);
    }
    return n;
}

int main(int argc, const char* argv[])
{
    //设置监听套接字
    //绑定地址,设置绑定属性
    //开始监听
    //设置等待链接,如果有链接,那么就创建子进程,用于通信.
    int lfd,cfd;
    struct sockaddr_in serv_sock,cliend_sock;
    socklen_t cliend_len=sizeof(cliend_sock);

    //创建监听套接字  ipv4  默认tcp协议模式
    lfd=socket(AF_INET,SOCK_STREAM,0);

    //设置属性
    serv_sock.sin_addr.s_addr=htonl(0);
    serv_sock.sin_family=AF_INET;
    serv_sock.sin_port=htons(9999);
    
    //设置端口复用
    int opt=1;

    setsockopt(lfd,SOL_SOCKET,SO_REUSEADD,&opt,sizeof(opt));

    bind(lfd,(struct sockaddr*)&serv_sock,sizeof(serv_sock));
    listen(lfd,64);

    while(1)
    {
        pid_t pid;
        cfd= accept(lfd,(struct sockaddr*)&cliend_sock,&cliend_len);
        if(cfd==-1)
        {
            perror("accept error:");
            exit(1);
        }
        //创建子进程.
        pid=fork(); 
        if(pid==0)
        {
            close(cfd);    
        }
        else if(pid>0)
        {
            int n;
            char buf[1024]={0};

            while( 0!=(n=read(cfd,buf,sizeof(buf))))
            {
                write(STDOUT_FILENO,buf,sizeof(buf));
            }

            exit(1);
        }

        
        


    }
    return 0;
}

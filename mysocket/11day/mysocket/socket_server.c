#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include "wrap.h"

int main(int argc, const char* argv[])
{   
    //创建链接属性结构体,serv用于绑定接口,cliend用于接受对方的链接信息
    struct sockaddr_in  servaddr,cliaddr;
    socklen_t cliaddr_len;

    int listenfd,connfd;//第一个用于listen函数  第二个用于链接

    char buf[8192];
    char str[INET_ADDRSTRLEN];

    int i,n;

    pid_t pid;//用于创建进程

    struct sigaction newact;//用于信号捕捉
    newact.sa_handler=do_sigchild;//handler 表示捕捉到函数后要执行的动作
    newact.sa_flags=0;//flags 确定其他信号来了的时候的动作
    sigemptyset(&newact.sa_mask);//初始化mask表;
    sigaction(SIGCHLD,&newact,NULL);//x需要捕捉的信号,
    
    //监听
    listenfd=Socket(AF_INET,SOCK_STREAM,0);//创建一个监听套接字,ipv4,流模式,默认tcp协议

    //端口复用?喵喵喵
    int opt=1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,,sizeof(opt));

    //绑定接口
    bzero(&servaddr);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(9999);
        servaddr.sin_family=AF_INET;

        Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        Listen(listenfd,20);

        puts("statr Accepting connections");
        while(1)
        {
            cliaddr_len=sizeof(cliaddr);
            connfd=Accept(listenfd,(struct sockaddr*)&cliaddr,cliaddr_len);
            
            //如果有链接的话,那么就开始创建进程来处理
            
            pid=fork();
            if(pid==0)//子进程
            {
                Close(listenfd); //关闭监听套接字,节约
                while(1)
                {
                    n=Read(connfd,buf,sizeof(buf));
                    if(n==0)
                    {
                        puts("连接断开");
                        break;
                    }

                    printf("")
                }
            }
            else if(pid>0)//父进程
            {

                while(1);
            }




        }



    return 0;
}

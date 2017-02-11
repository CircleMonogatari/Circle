#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
int main(int argc, const char* argv[])
{
    //创建监听套接字
    int bfd=socket(AF_INET,SOCK_STREAM,0);

    //绑定接口
    struct sockaddr_in sdk;
    memset(&sdk,0,sizeof(sdk));
    sdk.sin_port=htons(9999);//链接的端口
    sdk.sin_addr.s_addr=htonl(INADDR_ANY);//ip 默认所有
    sdk.sin_family=AF_INET;
    int ret=bind(bfd,(struct sockaddr*)&sdk,sizeof(sdk));
    if(ret==-1)
    {
        perror("bind error:");
        exit(1);
    }
    //监听
    ret=listen(bfd,64);
    if(ret==-1)
    {
        perror("listen error:");
        exit(1);
    }


    //等待链接请求
    //每次有请求,就分出一个进程,来处理
    while(1)
    {
        struct sockaddr_in chile_addr;// 用来接收请求者的信息.
        socklen_t clien_addr_len;
        int cfd=accept(bfd,(struct sockaddr*)&chile_addr,&clien_addr_len);
        if(cfd==-1)
        {
            perror("error accept:");
            exit(1);
        }
        pid_t pid;//创建进程标识符

        pid=fork();
        if(pid>0)//父进程
        {
            close(cfd);//关闭cfd减少内存花销
            //回收子进程
         // / while(1)
          //  {
         //       waitpid(0,NULL,WEXITED);
           // }
        }
        else  if(pid==0)//子进程
        {
            //接收转发消息,由子进程来做
            while(1)
            {
                char buf[512];
                int len=read(cfd,buf,sizeof(buf));
                if(len==-1)
                {
                    perror("read error");
                    exit(1);
                }else if(len>0)
                {
                    printf("read = %s",buf);
                }
                else if(len==0)
                {
                    puts("链接断开");
                    break;
                }

            }
            close(cfd);
            close(bfd);

        }
    }
        return 0;
}

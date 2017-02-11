#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, const char* argv[])
{
    //创建套接字
    //1.监听 2.绑定  3.等待接入 4接入后就创建子进程 5然后关闭监听
    //6回收子进程==>a.信号屏蔽,b信号捕捉.c信号回调函数.
    //              ipv4类型     stream模式  0默认   为tcp协议
    int serv_fd=socket(AF_INET,SOCK_STREAM,0);
    
    //创建bind的参数
    struct sockaddr_in sdl,cdl;
    bzeor(&sdl,sizeof(sdl));//初始化
    sdl.sin_family=AF_INET;//模式
    sdl.sin_port=htons(9999)          //端口
    sdl.sin_addr.s_addr=htonl(INADDR_ANY);    //ip地址 默认开一个

    int res bind(serv_fd,(struct sockaddr*)&sdl,sizeof(sdl));
        if(res==-1)
        {
            perror("bind error:");
            exit(1);
        }

    //开始监听
    res=listen(serv_fd,3);
    if(res==-1)
    {
        perror("listen error:");
        exit(1);
    }

    //等待接受请求,如果接到请求就创建子进程
    socklen_t clien_len=sizeof(cdl);


    while(1)
    {
    int cfd=accept(serv_fd,(struct sockaddr*)&cdl,&clien_len);
    if(cfd==-1)
    {
        perror("accept error:")
            exit(1);
    }
    
    //创建zi进程
    pid_t pid=fork();
        if(pid==0)//==0就是子进程
        {
            
        }
        else if(pid>0)//大于0就是父进程
        {
            close(cfd);
            //回收进程
            waitpid()
        }
  

    


    
    }
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#define PORT 9527
#define __err "测试通过"
void if_err(int ret,char *err)
{
    if(ret==-1)
    {
        perror(err);
        exit(1);
    }
}

int main(int argc, const char* argv[])
{
#if debug
    puts("开始创建套接字");
#endif
    //创建监听套接字
    int cfd,sfd,ret;
    struct sockaddr_in serve;
    struct sockaddr_in clend;
    memset(&serve,0,sizeof(serve));
    memset(&clend,0,sizeof(clend));
    socklen_t clend_len=sizeof(clend);   
    
    sfd=socket(AF_INET,SOCK_STREAM,0);
    //绑定链接
#if debug
    puts(__err);
#endif
    serve.sin_addr.s_addr=htonl(INADDR_ANY);
    serve.sin_port=htons(PORT);
    serve.sin_family=AF_INET;
    ret= bind(sfd,(struct sockaddr*)&serve,sizeof(serve));
    if_err(ret,"bind");
    //设置最大监听数
    ret= listen(sfd,128);
    if_err(ret,"liste");
    //等待客户端发送请求
#if debug
    puts("等待链接");
#endif
    while(1)
    {
       cfd=accept(sfd,(struct sockaddr*)&clend,&clend_len);
       pid_t pid=fork();
        //while(1)
#if debug
       puts("链接成功,等待进程创建");
#endif
        if(pid==0)
        {   //dup2()
            //dup2()
#if debug
            puts("dup2");
            puts("execl");
#endif
                dup2(cfd,STDIN_FILENO);
                dup2(cfd,STDOUT_FILENO);

            //创建进程 execl调用xhttp
            execl("./myhttp","myhttp","/home/itheima/myhttp/dir",NULL);
    
        }
    else if(pid>0)
    {
        close(cfd);
    }
    }     
    return 0;
}

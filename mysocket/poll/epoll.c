#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/epoll.h>

#define SERV_PORT 9999

int main(int argc, const char* argv[])
{
    int lfd, cfd;
    struct sockaddr_in serv_addr, clien_addr;
    int serv_len, clien_len;

    // 创建套接字
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    // 初始化服务器 sockaddr_in 
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                   // 地址族 
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);    // 监听本机所有的IP
    serv_addr.sin_port = htons(SERV_PORT);            // 设置端口 
    serv_len = sizeof(serv_addr);
    // 绑定IP和端口
    bind(lfd, (struct sockaddr*)&serv_addr, serv_len);

    // 设置同时监听的最大个数
    listen(lfd, 36);
    printf("Start accept ......\n");



    //create opll node fd

    int epfd=epoll_create(2000);
    if(epfd==-1)
        {
            perror("error eprll_create:");
            exit(1);
        }

    //add tree fd
    
    struct epoll_event ev;
    ev.data.fd=lfd;
    ev.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);

    struct epoll_event allev[2000];

    while(1)
    {
        int ret=epoll_wait(epfd,allev,sizeof(allev)/sizeof(allev[0]),-1) ;
        if(ret==-1)
        {
            perror("error epoll_wait:");
            exit(1);
        }

        for(int i=0;i<ret;++i)
        {
            int fd=allev[i].data.fd;
            if(allev[i].events==EPOLLIN)
            {
                if(fd==lfd)
                {
                    clien_len=sizeof(clien_addr);
                    int cfd=accept(lfd,(struct sockaddr*)&clien_addr,&clien_len);
                    //add terr
                    struct epoll_event tmp;
                    tmp.data.fd=cfd;
                    tmp.events=EPOLLIN;
                    epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&tmp);
                }
                else
                {
                    char buf[1024]={0};
                    int len=recv(fd,buf,sizeof(buf),0);
                    if(len==-1)
                    {
                        perror("error recv:");
                        exit(1);
                    }
                    else if(len==0)
                    {
                        printf("close fd:");
                        epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
                        close(fd);
                    }
                    else
                    {
                        puts(buf);
						send(fd,"大兄弟收到了\n",sizeof("大兄弟收到了\n"),0);
                    }

                }
            }
        }


    }

    close(lfd);
    return 0;
}

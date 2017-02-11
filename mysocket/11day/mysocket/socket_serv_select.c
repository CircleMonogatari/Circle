#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/select.h>
//#include "wrap.h"

#define SERV_PORT 9111

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

    //
    int ret;
    int maxfd=lfd;//最大的文件操作集

    //创建读文件符集 和 临时用
    fd_set reads,temps;

    //初始化 并 添加  lfd
    FD_ZERO(&reads);
    FD_SET(lfd,&reads);

    while(1)
    {
        //在循环里做select,就需要用到临时的,所以把reads的值付给他
        temps=reads;
        //就开始select 监听的操作符,读合集,写合集,错误合集,时间属性 后边三个暂时默认
        ret=select(lfd,&temps,NULL,NULL,NULL);
        //开始做判断 来做相应的操作
        if(ret==-1)
        {
            perror("select error:");
            exit(1);
        }
        //判断是否有链接
        if(FD_ISSET(lfd,&temps))
        {
            //有的话就处理
            clien_len=sizeof(clien_addr);
            int cfd=accept(lfd,(struct sockaddr*)&clien_addr,&clien_len);
            //把这个文件操作符加入到检测合集
            FD_SET(cfd,&reads);
            //更新最大文件操作符
            maxfd = maxfd < cfd ? cfd:maxfd;
        }

            for(int i=lfd+1;i<=maxfd;++i)
        {
               
            if(FD_ISSET(i,&temps))
            {
                char buf[1024];
                int len=read(i,buf,sizeof(1024));
                if(len==-1)
                {
                    perror("read error:");
                    exit(1);
                }
                else if(len==0)
                {
                    puts("大兄弟断开连接");
                    FD_CLR(i,&reads);
                    close(i);
                    if(maxfd==i)
                    {
                        maxfd--;
                    }
                }
                else
                {
                    printf("read buf==%s",buf);
                    write(i,"大兄弟收到了\n",sizeof("大兄弟收到了\n")+1);
                }
            }

        }   
    }

    close(lfd);
    return 0;
}

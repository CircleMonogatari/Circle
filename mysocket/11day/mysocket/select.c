#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/select.h>

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

    // 最大文件描述符
    int maxfd = lfd;
    // 检测读操作的集合
    fd_set rdall, temp;
    // init
    FD_ZERO(&rdall);
    // 将监听的fd放到读集合， 内核帮助我们检测是否有连接请求
    FD_SET(lfd, &rdall);

    while(1)
    {
        temp = rdall;
        // 雇佣了一个秘书 select， 帮助我们检测对应的文件描述符是否有 变化
        int ret = select(maxfd+1, &temp, NULL, NULL, NULL);
        if(ret == -1)
        {
            perror("select error");
            exit(1);
        }

        // 接受连接请求
        if(FD_ISSET(lfd, &temp))
        {
            clien_len = sizeof(clien_addr);
            int cfd = accept(lfd, (struct sockaddr*)&clien_addr, &clien_len);

            // cfd 需要放到检测读的集合中
            FD_SET(cfd, &rdall);
            // 更新最大的文件描述符
            maxfd = maxfd < cfd ? cfd : maxfd;
        }

        // 如果有客户端给服务器发送数据
        for(int i=lfd+1; i<=maxfd; ++i)
        {
            // 判断文件描述符是否在读集合中
            if(FD_ISSET(i, &temp))
            {
                // 接收数据
                char buf[1024] = {0};
                int len = recv(i, buf, sizeof(buf), 0);
                if(len == -1)
                {
                    perror("recv error");
                    exit(1);
                }
                else if(len == 0)
                {
                    printf("客户端已经断开了连接。。。\n");
                    // 文件描述符从读集合中删除
                    FD_CLR(i, &rdall);
                    close(i);
                }
                else 
                {
                    printf("recv buf = %s\n", buf);
                    for(int j=0; j<len; ++j)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    write(STDOUT_FILENO, buf, len);
                    // 数据发送给客户端
                    send(i, buf, len, 0);
                }
            }
        }
    }

    close(lfd);
    return 0;
}

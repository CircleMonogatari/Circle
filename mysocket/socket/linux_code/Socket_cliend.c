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
    //创建套接字
    //设置连接属性
    //开始连接
    //通信
    if(argc<3)
    {
        puts("./a.out  ip   port  error:");
        exit(1);
    }

    int cld=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serv_sock;
    serv_sock.sin_family=AF_INET;
    puts("statr port");
  //media  puts(argv[2])
    int port_n=atoi(argv[2]);
   // puts("1");
    serv_sock.sin_port=htons(port_n);
    puts("statr ip");
    inet_pton(AF_INET,argv[1],&serv_sock.sin_addr.s_addr);

    connect(cld,(struct sockaddr*)&serv_sock,sizeof(serv_sock));

    char buf[10]={0};
 //   puts("go");
  //  read(STDIN_FILENO,buf,10);
   while((read(STDIN_FILENO,buf,sizeof(buf) )))
    //使用recv STDIN_FILENO 有问题
  //  while(recv(STDIN_FILENO,buf,sizeof(buf),MSG_WAITALL))
    {
        send(cld,buf,sizeof(buf),0);
       memset(buf,0,sizeof(buf));
    }

#if 0
    int clie_len;
    while(1){
        char buf[1024] = {0};
        printf("asdf\n");
        //gets(STDIN_FILENO, buf, sizeof(buf));
        clie_len = recv(STDIN_FILENO, buf, sizeof(buf), 0);
        printf("len = %d\n", clie_len);
        if(clie_len == -1){
            printf("--------client error---------\n");
            exit(1);
        }
        if(clie_len > 0){
            printf("--------\n");
            send(cld, buf, clie_len, 0);

        }
#endif

    return 0;
}

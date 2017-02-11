#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>


int main(int argc, const char* argv[])
{
 //1创建监听套接字
 int sfd=socket(AF_INET,SOCK_STREAM,0);
 //2setbind 属性
 struct sockaddr_in sodr;
 struct sockaddr_in clined;
 sodr.sin_port=ptons(9999);
 sodr.sin_addr.s_addr=ptonl()
 //设置监听
 //4端口复用
 //5开始等待链接
 //循环读取


    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myquit()
{
    puts("catch quit");
}

void mysigmask(int acg)
{
    printf("%d--抓到大兄弟了!\n",acg);
}
int main(int argc, const char* argv[])
{
    //创建结构体,用于sigaction的第二个参数;
    struct sigaction sct;
        sct.sa_flags=0;
     sigemptyset(&sct.sa_mask);//sct.sa_mask  在处理是需要屏蔽的信号合集
    
     sigaddset(&sct.sa_mask,SIGQUIT);
    sct.sa_handler=mysigmask;




   sigaction(SIGINT,&sct,NULL);
    signal(SIGQUIT,myquit);



    while(1);
    return 0;
}

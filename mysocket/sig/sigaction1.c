#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myfunc(int sig)
{
    printf("signal:%d------\n",sig);
    sleep(10);
    puts("catcr ED!!!");
}

int main()
{
   struct  sigaction sig;
   sig.sa_handler=myfunc;
  sigemptyset(&sig.sa_mask);//初始化sig表里边的mask表
    //把屏蔽信号加载进去
    sigaddset(&sig.sa_mask,SIGQUIT);
   sig.sa_flags=0; 
   sigaction(SIGINT,&sig,NULL);




    while(1);
    return 1;
}

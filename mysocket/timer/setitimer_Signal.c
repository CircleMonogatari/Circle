#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

void myfunc(int sig)
{
    puts("hello world");
}

int main(int argc, const char* argv[])
{
struct itimerval sti;
sti.it_value.tv_sec=1;
sti.it_value.tv_usec=0;
//定时器1秒
sti.it_interval.tv_usec=0;
sti.it_interval.tv_sec=1;
    
    //系统捕获信号

    signal(SIGALRM,myfunc);



    setitimer(ITIMER_REAL,&sti,NULL);

    while(1);
    return 0;
}

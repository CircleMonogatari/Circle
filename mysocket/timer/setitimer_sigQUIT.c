#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

void myquit(int sig)
{
    puts("catch dxd");
}

void myfunc(int sig)
{
       puts("hello world");
       sleep(5);
       puts("dxd");
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

    struct sigaction act;
    act.sa_flags=0;
    act.sa_handler=myfunc;
    sigemptyset(&act.sa_mask);

    sigaction(SIGALRM,&act,NULL);
    signal(SIGQUIT,myquit);

    setitimer(ITIMER_REAL,&sti,NULL);

    while(1);
    return 0;
}

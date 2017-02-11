#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h> 

void my_func()
{
    puts("catch dxd");
}


struct itimerval my_alarm(int val,int inserval)
{
    struct itimerval newtime,oldtime;
    newtime.it_value.tv_sec=val;
    newtime.it_value.tv_usec=0;
    newtime.it_interval.tv_sec=inserval;
    newtime.it_interval.tv_usec=0;

    int res=setitimer(ITIMER_REAL,&newtime,&oldtime);
        if(res==-1)
        {
            perror("setitimer error:");
            exit(1);
        }
        return oldtime;

}

int main(int argc, const char* argv[])
{
    signal(SIGALRM,my_func);
    my_alarm(2,1);
    while(1);

    
    return 0;
}

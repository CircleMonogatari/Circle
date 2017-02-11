#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

struct itimerval my_alarm(int sec)
{
    struct itimerval newtime,oldtime;
    newtime.it_interval.tv_sec=0;
    newtime.it_interval.tv_usec=0;  
    newtime.it_value.tv_usec=0;
    newtime.it_value.tv_sec=2;

    int res;
    //res=setitimer(ITIMER_REAL,newtime,&oldtime);
  res=  setitimer(ITIMER_REAL,&newtime,&oldtime);
    if(res==-1)
    {
        perror("setitimer error:");
        exit(1);
    }

    return oldtime;
}


int main(int argc, const char* argv[])
{
    my_alarm(1);
    for(int i=0;;i++)
    {
        printf("%d\n",i);
    }
    
    return 0;
}

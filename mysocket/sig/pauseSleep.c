#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

void catch(int sig)
{
    ;
}

int mysleep(int sec)
{
    struct sigaction sig,oldsig;
    sig.sa_flags=0;
    sig.sa_handler=catch;
    sigemptyset(&sig.sa_mask);
    int ret=sigaction(SIGALRM,&sig,&oldsig);
    if(ret==-1)
    {
        perror("sigactio error:");
        exit(1);
    }

     alarm(sec);//时钟,
    pause();//时间到了以后自动挂起
    
}


int main()
{
    

    while(1)
    {
        mysleep(3);
        printf("------\n");
    }
    return 1;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

void myfunc()
{
    ;
}


int main(int argc, const char* argv[])
{

    struct sigaction act;
    act.sa_flags=0;
    act.sa_handler=myfunc;
    sigemptyset(&act.sa_mask);
   // sigaddset(&act.sa_mask,SIGINT);

     sigaction(SIGINT,&act,NULL);



    pause();
    while(1)
    {
        puts("dxd");
        sleep(1);
    }
    return 0;
}

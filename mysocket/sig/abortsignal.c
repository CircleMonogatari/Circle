#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include<sys/time.h>
#include <sys/wait.h>

int main(int argc, const char* argv[])
{
    
    pid_t pid=fork();
    
    if(pid==0)
    {
        while(1)
        {
            puts("66");
   //media         struct itimerval newtime;
      //      newtime.it_value.tv_sec=5;
       //     newtime.it_interval.tv_sec=1;
        //    setitimer(ITIMER_REAL,&newtime,NULL);
            sleep(3);
            abort();
        }
    }
    else if(pid>0)
    {

        pid_t pidc=wait(NULL);
        printf("%d----kill",pidc);
        while(1);
    }

    return 0;
}

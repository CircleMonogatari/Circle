#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


int main(int argc, const char* argv[])
{
    pid_t pid=fork();

    if(pid==0)
    {
        puts("stat");
        alarm(5);
        sleep(4);
        int n=alarm(10);
        printf("%d\n",n);
    }
    else if(pid>0)
    {
        pid_t waip;
       int stat_loc;
      waip=  waitpid(0,&stat_loc,0);
        if(WIFSIGNALED(stat_loc))
        {
            puts("1 sig");
        }
        else if(WTERMSIG(stat_loc))
        {
            puts("sig 2");
        }
        else
        {
            puts("mmm");
        }
   
        printf("\n--%d--\n",waip);
    }


    return 0;
}

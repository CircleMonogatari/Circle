#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int main(int argc, const char* argv[])
{
     
    pid_t pid=fork();
   
    if(pid==0)
    {
        sleep(5);
        kill(getppid(),SIGKILL);
        while(1);

    }
    else if(pid>0)
    {
        while(1)
        {
            puts("000");
        }

    }
    
    
    
    
    
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include<sys/wait.h>

int main(int argc, const char* argv[])
{
    int p[2];
    //做一个虚拟管道
    pipe(p);
    int i=0;
    for(i=0;i<2;i++)
    {

       pid_t pid= fork();
       if(pid==0)
       {
           break;
       }
    }

    if(i==0)
    {
        close(p[0]);
        dup2(p[1],STDOUT_FILENO);
        execlp("ps","ps","aux",NULL);
        perror("0ps error");

        exit(1);
    }
    else if(i==1)
    {
close(p[1]);
dup2(p[0],STDIN_FILENO);
execlp("grep","grep","bash",NULL);

exit(1);
    }
    else if(i==2)
    {
        close(p[1]);
        close(p[0]);
        wait(NULL);
    }


    return 0;
}

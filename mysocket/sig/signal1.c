#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myint()
{
    puts("hhh");
}
void mytstp()
{
    puts("tstp");
}


int main(int argc, const char* argv[])
{
    sigset_t set;

    signal(SIGINT,myint);
    signal(SIGTSTP,mytstp);

    sigemptyset(&set);
   // sigaddset(&set,SIGINT);
    //sigaddset(&set,SIGTSTP);
    sigprocmask(SIG_BLOCK,&set,NULL);

    while(1)
    {
    }
    return 0;
}


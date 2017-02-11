#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int main(int argc, const char* argv[])
{
    sigset_t set,old;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    
    sigprocmask(SIG_BLOCK,&set,&old);

    puts("stat");
    sleep(5);
    puts("end");
    sigprocmask(SIG_SETMASK,&old,NULL);

    while(1);
        
    return 0;
}

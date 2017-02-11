#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

void mysig()
{
    sigset_t ss;
    sigpending(&ss);
    for(int i=1;i<32;i++)
    {
        if(sigismember(&ss,i)==1)
        {
            putchar('1');
        }else if(sigismember(&ss,i)==0)
        {
            putchar('0');
        }else if(sigismember(&ss,i)==-1)
        {
            perror("sigismember error:");
            exit(1);
        }
    }
    puts("-");
}

int main(int argc, const char* argv[])
{
    sigset_t myset , newmyset;
    sigemptyset(&myset);
    sigaddset(&myset,SIGINT);
    sigaddset(&myset,SIGQUIT);
    sigaddset(&myset,SIGTSTP);   
    sigprocmask(SIG_BLOCK,&myset,NULL);

    while(1)
    {
 sleep(1);
        mysig();
    }

    

    return 0;
}
